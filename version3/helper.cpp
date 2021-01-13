#include "helper.h"
#include <iostream>
#include <string>
#include <limits>
#include <random>
#include <chrono>
#include <fstream>
#include <vector>
using namespace std;

void Hex::Cell::setState(cellState s)
{
	state=s;
}
cellState Hex::Cell::getState()
{
	return state;
}
void Hex::fillBoardDot()
{
	Hex::Cell c;
	hexCells.reserve(26);
	for(int i=0 ; i<26 ; i++)
	{
		for(int j=0 ; j<26 ; j++)
		{
			c.setPosition(i+97);
			c.setRow(i);
			c.setState(cellState::empty);
			hexCells[i].push_back(c);
		}
	}
}
void Hex::displayBoard()
{
	int i,j,k;
	char letters=97;
	for(i=0 ; i<width ; i++)
		cout << "  " << letters++ ;

	for(i=0 ; i<width ; i++)
	{
		cout << endl << i+1;
		for(k=0 ; k<i ; k++)
			cout << "  ";
		for(j=0 ; j<height ; j++)
			cout << "  " << static_cast<char>(hexCells[i][j].getState());
	}
	cout << endl;
}
void Hex::Cell::setPosition(char p)
{
	position=p;
}
void Hex::Cell::setRow(int r)
{
	row=r;
}

int Hex::getWidth()
{
	return width;
}
int Hex::getHeight()
{
	return height;
}
void Hex::playGame()
{
	if(!loaded && !saved)
	{
		int boardSize, gameType;;

		/* Validity check until user enters a valid input */
		do // Asking the user for the board size
		{
			cout << "\nPlease select the board size by typing an integer from 6 to 26\n"
					<< "Board Size --> ";
			cin >> boardSize;
			cin.clear(); cin.ignore(256,'\n');
		}while(!testSize(boardSize));
		width=boardSize; height=boardSize;

		do //Asking the user for the game type
		{
			cout << "\n1)Two Player 2)User versus Computer\n";
			cout << "Please select the game type above by typing 1 or 2 --> ";
			cin >> gameType;
			cin.clear(); cin.ignore(256,'\n');
		}while(!testType(gameType));
		type=gameType;
		turn=1;
	}
	string input, str, filename;
	char moveLetter1, moveLetter2;
	int moveNumber1, moveNumber2;
	int pos,count=0;
	bool quit=false,flag=false;

	displayBoard();
	while(win == false && quit==false) // game continues until user wants to quit or one of the players wins
	{
		switch(type)
		{
			case 1: // user1-user2
				switch(turn)
				{
					case 1: // user1
						cout << "EXAMPLE MOVES: A 1, C 3 --- GO BACK TO MENU TYPING -1\n"
								"USER1-->";
						cin >> ws;
						getline(cin,input);

						if(input=="-1")
						{
							saveFile(to_string(gameNum+1));
							flag=false;
							quit=true;
						}
						else if(input.size()==3)
						{
							moveLetter2 = input[0];
							moveNumber2 = input[2] - '0';
							flag=checkMove(moveLetter2,moveNumber2);
							if(flag==true)
								play(moveNumber2-1, moveLetter2-'A');
						}
						else cerr << "INVALID MOVE PLEASE TRY AGAIN.\n";

						if(quit==false)
						{
							/* checks whether user1 won or not */
							for(int i=0 ; i<width ; i++)
							{
								if(endGame(i, 0)==true)
								{
									cout<<"\n****USER1 WON!****\n";
									win=true;
								}
							}
						}
						if(flag == true) displayBoard();
						break;

					case 2: // user2
						cout << "EXAMPLE MOVES: A 1, C 3 --- GO BACK TO MENU TYPING -1\n"
								"USER2-->";
						cin >> ws;
						getline(cin,input);

						if(input=="-1")
						{
							saveFile(to_string(gameNum+1));
							flag=false;
							quit=true;
						}
						else if(input.size()==3)
						{
							moveLetter2 = input[0];
							moveNumber2 = input[2] - '0';
							flag=checkMove(moveLetter2,moveNumber2);
							if(flag==true)
								play(moveNumber2-1, moveLetter2-'A');
						}
						else cerr << "INVALID MOVE PLEASE TRY AGAIN.\n";

						if(quit==false)
						{
							/* checks whether user2 won or not */
							for(int i=0 ; i<height ; i++)
							{
								if(endGame(0, i)==true)
								{
									cout<<"\n****USER2 WON!****\n";
									win=true;
								}
							}
						}
						if(flag == true) displayBoard();
						break;
				}
				break;

			case 2: // user-computer
				switch(turn)
				{
					case 1: // user
						cout << "EXAMPLE MOVES: A 1, C 3 --- GO BACK TO MENU TYPING -1 -->";
								"USER-->";
						cin >> ws;
						getline(cin,input);

						if(input=="-1")
						{
							saveFile(to_string(gameNum+1));
							flag=false;
							quit=true;
						}
						else if(input.size()==3)
						{
							moveLetter2 = input[0];
							moveNumber2 = input[2] - '0';
							flag=checkMove(moveLetter2,moveNumber2);
							if(flag==true)
								play(moveNumber2-1, moveLetter2-'A');
						}
						else cerr << "INVALID MOVE PLEASE TRY AGAIN.\n";

						if(flag==false)
						{
							/* checks whether user won or not */
							for(int i=0 ; i<width ; i++)
							{
								if(endGame(0, i)==true)
								{
									cout<<"\n****USER WON!****\n";
									win=true;
								}
							}
						}
						if(flag == true) displayBoard();
						break;

						case 2: // computer
						play();
						turn=1;

						/* checks whether computer won or not */
						for(int i=0 ; i<height ; i++)
						{
							if(endGame(i, 0)==true)
							{
								cout<<"\n****COMPUTER WON!****\n";
								win=true;
							}
						}
						displayBoard();
						break;
				}
				break;
		}

	}
}
bool Hex::testSize(int boardSize)
{
	if(boardSize<6 || boardSize>26)
	{
		cerr << "\nINVALID INPUT!\n";
		return false;
	}
	return true;
}
bool Hex::testType(int gameType)
{
	if(gameType!=1 && gameType!=2)
	{
		cerr << "\nINVALID INPUT!\n";
		return false;
	}
	return true;
}
void printMenu()
{
	cout << "\n**************\n"
			"   HEX GAME  \n"
			"**************\n";
	cout << "1 - Start a new game.\n"
			"2 - Continue to an active game.\n"
			"3 - Compare marked cells for 2 games.\n"
			"4 - Display number of marked cells in all games.\n"
			"5 - EXIT\n\n";
	cout << "CHOICE --> ";
}
bool Hex::checkMove(char moveLetter, int &moveNumber)
{
	char letters[12] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L'};

	/*
	   if input is invalid checkMove() returns false
	   it input is valid checkMove() returns true
	 */
	if(hexCells[moveNumber-1][moveLetter-'A'].getState() != (cellState::empty) || moveLetter<letters[0] || moveLetter>letters[width-1] || moveNumber<0 || moveNumber>width)
	{
		cerr << "INVALID MOVE PLEASE TRY AGAIN.\n";
		return false;
	}
	return true;
}
bool Hex::endGame(int i, int j)
{
	if((type==2 && turn==2) || (type==1 && turn==1))
	{
		if (i == width ) return true; // reaching the opposite side
		if ( i < 0 || j < 0 || i > width || j > width) return false; // invalid positions
		if ( hexCells[i][j].getState() != (cellState::user2)) return false;

		hexCells[i][j].setState(cellState::winUser2); // winning path is marked with capital X

		if (endGame(i,   j-1) == true ) return true; // WEST
		if (endGame(i,   j+1) == true ) return true; // EAST
		if (endGame(i-1, j)   == true ) return true; // NORTH-WEST
		if (endGame(i-1, j+1) == true ) return true; // NORTH-EAST
		if (endGame(i+1, j-1) == true ) return true; // SOUTH-WEST
		if (endGame(i+1, j)   == true ) return true; // SOUTH-EAST

		hexCells[i][j].setState(cellState::user2); // not winning path is unmarked
		return false;
	}
	else if((type==2 && turn==1) || (type==1 && turn==2))
	{
		if (j == width ) return true; // reaching the opposite side
		if ( i < 0 || j < 0 || i > width || j > width ) return false; // invalid positions
		if ( hexCells[i][j].getState() != (cellState::user1)) return false;

		hexCells[i][j].setState(cellState::winUser1); // winning path is marked with capital X

		if (endGame(i,   j-1) == true ) return true; // WEST
		if (endGame(i,   j+1) == true ) return true; // EAST
		if (endGame(i-1, j)   == true ) return true; // NORTH-WEST
		if (endGame(i-1, j+1) == true ) return true; // NORTH-EAST
		if (endGame(i+1, j-1) == true ) return true; // SOUTH-WEST
		if (endGame(i+1, j)   == true ) return true; // SOUTH-EAST

		hexCells[i][j].setState(cellState::user1); // not winning path is unmarked
		return false;
	}
}
void Hex::play(int row, int column)
{
	if(type==2)
	{
		hexCells[row][column].setState(cellState::user2);
		allMarked++;
		marked++;
		turn=2;
	}
	else if(type==1 && turn==1)
	{
		hexCells[row][column].setState(cellState::user1);
		allMarked++;
		marked++;
		turn=2;
	}
	else
	{
		hexCells[row][column].setState(cellState::user2);
		allMarked++;
		marked++;
		turn=1;
	}
}
void Hex::play()
{
	auto i=0,j=0;

	while(hexCells[i][j].getState() != cellState::empty)
	{
		i = randomNumberGenerator(width);
		j = randomNumberGenerator(height);
	}
	hexCells[i][j].setState(cellState::user1);
	allMarked++;
	cout << "\nCOMPUTER MOVE-->" << static_cast<char>(j+65) << " " << i+1 << endl;
}
int randomNumberGenerator(int boardSize)
{
	unsigned seed = (std::chrono::system_clock::now().time_since_epoch().count());
	default_random_engine generator(seed);
	uniform_int_distribution<int> distribution(0,boardSize-1);
	return distribution(generator);
}
void Hex::saveFile(string num)
{
	ofstream outStream;
	string filename;

	filename= num + ".txt";
	outStream.open(filename);

	if(outStream.fail()) cerr << "Output file opening failed.\n";
	else
	{
		outStream << width << endl << type << endl << turn << endl;

		for(int i=0 ; i<width ; i++)
		{
			for(int j=0 ; j<width ; j++) outStream << static_cast<char>(hexCells[i][j].getState());
			outStream <<endl;
		}
		cout << "\nGame saved into " << filename << endl;
		outStream.close();
		saved=true;
	}
}
void Hex::loadFile(string filename)
{
	ifstream inStream;
	char ch;

	inStream.open(filename);
	if(inStream.fail()) cerr << "Input file opening failed.\n";
	else
	{
		inStream >> width >> type >> turn;
		height=width;
		fillBoardDot();
		for(int i=0 ; i<width ; i++)
		{
			for(int j=0 ; j<height ; j++)
			{
				inStream >> ch;

				switch(ch)
				{
				 case '.':
					 hexCells[i][j].setState(cellState::empty);
					 break;
				 case 'x' :
					 hexCells[i][j].setState(cellState::user1);
					 break;
				 case 'o':
					 hexCells[i][j].setState(cellState::user2);
					 break;
				 case 'O':
					 hexCells[i][j].setState(cellState::winUser2);
					 break;
				 case 'X':
					 hexCells[i][j].setState(cellState::winUser1);
					 break;
				}
			}
		}
		loaded=true;
		cout << "\nGAME LOADED\n";
		inStream.close();
	}
}
void Hex::setGameNum(int num)
{
	gameNum=num;
}
int Hex::getGameNum()
{
	return gameNum;
}
Hex::Hex()
{
	Hex::Cell c;
	hexCells.reserve(26);
	for(int i=0 ; i<26 ; i++)
	{
		for(int j=0 ; j<26 ; j++)
		{
			c.setPosition(i+97);
			c.setRow(i);
			c.setState(cellState::empty);
			hexCells[i].push_back(c);
		}
	}
}
bool Hex::getWin()
{
	return win;
}
Hex::Hex(int w, int h)
{
	width=w;
	height=h;
}
inline int Hex::getMarked()
{
	return marked;
}
int Hex::getAllMarked()
{
	return allMarked;
}
bool Hex::compareMarked(Hex other)
{
	return(marked>other.getMarked());
}
