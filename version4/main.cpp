#include <iostream>
#include <string>
#include <limits>
#include <random>
#include <chrono>
#include <fstream>
#include <vector>
using namespace std;

enum class cellState {user1='x', user2='o', empty='.', winUser1='X', winUser2='O'};

class Hex
{
public:
	class Cell
	{
	public:
		Cell(){};
		explicit Cell(char pos, int rowValue, cellState st);
		cellState getState();
		void setState(cellState s);
		void setPosition(char p);
		char getPosition();
		void setRow(int r);
		int getRow();
		//Cell operator=(const Cell other);
	private:
		char position;
		int row;
		cellState state;
	};

	void readFile();
	void writeFile();
	int getWidth() const;
	int getHeight() const;
	void displayBoard() const;
	Cell play(); // computer play
	void play(int row, int column); // user play
	bool endGame(int i, int j);
	void playGame();
	int getMarked() const;
	void setGameNum(int num);
	int getGameNum() const;
	bool getWin() const;
	bool testSize(int boardSize) const;
	bool testType(int gameType)const;
	void fillBoardDot();
	bool checkMove(char moveLetter, int &moveNumber) const;
	void saveFile(const string num);
	void loadFile(const string filename);
	static int getAllMarked();
	static int getGames() ;
	bool operator==(Hex &other) const; //compare method
	int score() ;

	friend ostream & operator<<(ostream &out, const Hex &obj); // overloaded friend function for screen print and file output
	friend istream & operator>>(istream &in, Hex &obj); // // overloaded friend function for file input
	friend Hex & operator--(Hex &obj); // prefix UNDO operator
	friend Hex & operator--(Hex &obj, int); //postfix UNDO operator

	explicit Hex(int boardSize, int typeValue);
	Hex(){};


private:
	int width, height, type, turn,marked, gameNum, playNum;
	int score1, score2;
	bool loaded,saved, win;
	static int allMarked, games;
	Cell ** hexCells;
	int **allPlays;
};
int Hex::allMarked=0;
int Hex::games=0;
void printMenu();
int randomNumberGenerator(int boardSize);
int main()
{
	int choice, act, count=0,first,second;
	int marked;
	int num;
	Hex *game = new Hex[20];

	/* initial active games */
	game[0] = Hex(26, 1);
	game[0].loadFile("1.txt");
	game[1] = Hex(26, 1);
	game[1].loadFile("2.txt");
	game[2] = Hex(26, 1);
	game[2].loadFile("3.txt");
	game[3] = Hex(26, 1);
	game[3].loadFile("4.txt");
	game[4] = Hex(26, 1);
	game[4].loadFile("5.txt");
	game[5] = Hex(26, 1);
	game[5].loadFile("6.txt");
	do
	{
		printMenu();
		cin >> choice;
		cin.clear(); cin.ignore(256,'\n');
		switch(choice)
		{
			case 1:
				num=Hex::getGames();
				game[num].playGame();
				break;

			case 2:
				cout << "\nACTIVE GAMES\n";
				for(int i=0 ; i<Hex::getGames() ; i++)
				{
					if(game[i].getWin() ==false)
					{
						cout << "Game"<< i+1 << " ";
						count++;
					}
				}
				if(count==0) cout << "There is no active game!\n";
				else
				{
					cout<<"\nPlease select a game above by typing a game number(1,2,3 etc.)-->";
					cin >> act;
					game[act-1].playGame();
					count=0;
				}
				break;

			case 3:
				cout << "\nACTIVE GAMES\n";
				for(int i=0 ; i<Hex::getGames() ; i++)
				{
					if(game[i].getWin() ==false)
					{
						cout << "Game"<< i+1 << " ";
						count++;
					}
				}
				if(count<2) cout << "\nThere is no enough game to compare!\n";
				else
				{
					cout<<"\nPlease select two games above by typing game numbers(1 2, 1 3, 3 2 etc.)-->";
					cin >> first >> second;
					if(game[first-1] == game[second-1]) cout << "Game"<< first << " has more marked cells for the user\n";
					else
					{
						cout << "\nGame"<< first << "-->"<< game[first-1].getMarked();
						cout << "  Game"<< second << "-->"<< game[second-1].getMarked();
						cout << "\nGame"<< second << " has more marked cells for the user\n";
					}
					count=0;
				}

				break;
			case 4:
				cout << "\nNumber of marked cells in all the games is " << Hex::getAllMarked() <<endl;
				break;

			case 5:
				break;
			default :
				cout << "INVALID INPUT!\n";
		}

	}while(choice!=5); // program ends if user wants to exit
	return 0;
}
int Hex::score()
{
	return marked;
}
Hex::Cell::Cell(char pos, int rowValue, cellState st)
{
	position=pos;
	row=rowValue;
	state=st;
}
void Hex::Cell::setState(cellState s){state=s;}
cellState Hex::Cell::getState(){return state;}
void Hex::Cell::setPosition(char p){position=p;}
void Hex::Cell::setRow(int r){row=r;}
char Hex::Cell::getPosition(){return position;}
int Hex::Cell::getRow(){return row;}
int Hex::getMarked() const {return marked;}
bool Hex::operator==(Hex &other) const
{
	return(marked>other.getMarked());
}
ostream &operator<<(ostream &out, const Hex &obj)
{
	if(&out == &cout)
	{
		int i,j,k;
		char letters=97;
		for(i=0 ; i<obj.width ; i++)
			out << "  " << letters++ ;

		for(i=0 ; i<obj.width ; i++)
		{
			out << endl << i+1;
			for(k=0 ; k<i ; k++)
				out << "  ";
			for(j=0 ; j<obj.height ; j++)
				out << "  " << static_cast<char>(obj.hexCells[i][j].getState());
		}
		out << endl;
	}
	else
	{
		out << obj.width << endl << obj.type << endl << obj.turn << endl;

		for(int i=0 ; i<obj.width ; i++)
		{
			for(int j=0 ; j<obj.width ; j++) out << static_cast<char>(obj.hexCells[i][j].getState());
			out<<endl;
		}
	}
	return out;
}
istream & operator>>(istream &in, Hex &obj)
{
	char ch;
	in >> obj.width >> obj.type >> obj.turn;
	obj.height=obj.width;
	for(int i=0 ; i<obj.width ; i++)
	{
		for(int j=0 ; j<obj.height ; j++)
		{
			in >> ch;

			switch(ch)
			{
			 case '.':
				 obj.hexCells[i][j].setState(cellState::empty);
				 break;
			 case 'x' :
				 obj.hexCells[i][j].setState(cellState::user1);
				 obj.allPlays[obj.playNum][0]=i;
				 obj.allPlays[obj.playNum][1]=j;
				 obj.playNum++;
				 if(obj.type==2) obj.marked++;
				 break;
			 case 'o':
				 obj.hexCells[i][j].setState(cellState::user2);
				 obj.allPlays[obj.playNum][0]=i;
				 obj.allPlays[obj.playNum][1]=j;
				 obj.playNum++;
				 obj.marked++;
				 break;
			 case 'O':
				 obj.hexCells[i][j].setState(cellState::winUser2);
				 break;
			 case 'X':
				 obj.hexCells[i][j].setState(cellState::winUser1);
				 break;
			}
		}
	}
	return in;
}
Hex & operator--(Hex &obj) // prefix
{
	int i,j;
	i=obj.allPlays[obj.playNum-1][0];
	j=obj.allPlays[obj.playNum-1][1];
	obj.hexCells[i][j].setState(cellState::empty);
	obj.playNum--;
	return obj;
}
Hex & operator--(Hex &obj, int) // postfix
{
	Hex &temp = obj;
	int i,j;
	i=obj.allPlays[obj.playNum-1][0];
	j=obj.allPlays[obj.playNum-1][1];
	obj.hexCells[i][j].setState(cellState::empty);
	obj.playNum--;
	return temp;
}
void Hex::displayBoard() const
{
	cout << *this; // calling overloaded stream insertion operator to print 'this' object
}
int Hex::getWidth() const {return width;}
int Hex::getHeight() const {return height;}
void Hex::playGame()
{
	int boardSize, gameType;
	if(!loaded && !saved)
	{

		/* Validity check until user enters a valid input */
		do // Asking the user for the board size
		{
			cout << "\nPlease select the board size by typing an integer from 6 to 26\n"
					<< "Board Size --> ";
			cin >> boardSize;
			cin.clear(); cin.ignore(256,'\n');
		}while(!testSize(boardSize));

		do //Asking the user for the game type
		{
			cout << "\n1)Two Player 2)User versus Computer\n";
			cout << "Please select the game type above by typing 1 or 2 --> ";
			cin >> gameType;
			cin.clear(); cin.ignore(256,'\n');
		}while(!testType(gameType));
		*this = Hex(boardSize, gameType);
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
						cout << "EXAMPLE MOVES: A 1, C 3 --- GO BACK TO MENU TYPING -1 or UNDO LAST PLAY BY TYPING UNDO\n"
								"USER1-->";
						cin >> ws;
						getline(cin,input);

						if(input=="-1")
						{
							saveFile(to_string(gameNum+1));
							flag=false;
							quit=true;
						}
						else if(input=="UNDO")
						{
							--(*this);
							flag=true;
						}
						else if(input.size()==3)
						{
							moveLetter2 = input[0];
							moveNumber2 = input[2] - '0';
							flag=checkMove(moveLetter2,moveNumber2);
							if(flag==true)
								play(moveNumber2-1, moveLetter2-'A');
						}
						else if(input.size()==4)
						{
							moveLetter2 = input[0];
							moveNumber2 = (input[2] - '0')*10 +(input[3] - '0') ;
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
						cout << "EXAMPLE MOVES: A 1, C 3 --- GO BACK TO MENU TYPING -1 or UNDO LAST PLAY BY TYPING UNDO\n\n"
								"USER2-->";
						cin >> ws;
						getline(cin,input);

						if(input=="-1")
						{
							saveFile(to_string(gameNum+1));
							flag=false;
							quit=true;
						}
						else if(input=="UNDO")
						{
							--(*this);
							flag=true;
						}
						else if(input.size()==3)
						{
							moveLetter2 = input[0];
							moveNumber2 = input[2] - '0';
							flag=checkMove(moveLetter2,moveNumber2);
							if(flag==true)
								play(moveNumber2-1, moveLetter2-'A');
						}
						else if(input.size()==4)
						{
							moveLetter2 = input[0];
							moveNumber2 = (input[2] - '0')*10 +(input[3] - '0') ;
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
						cout << "EXAMPLE MOVES: A 1, C 3 --- GO BACK TO MENU TYPING -1 or UNDO LAST PLAY BY TYPING UNDO\n";
						cout << "User Score:" <<  score() << "\nUSER-->";
						cin >> ws;
						getline(cin,input);

						if(input=="-1")
						{
							saveFile(to_string(gameNum+1));
							flag=false;
							quit=true;
						}
						else if(input=="UNDO")
						{
							--(*this);
							flag=true;
						}
						else if(input.size()==3)
						{
							moveLetter2 = input[0];
							moveNumber2 = input[2] - '0';
							flag=checkMove(moveLetter2,moveNumber2);
							if(flag==true)
								play(moveNumber2-1, moveLetter2-'A');
						}
						else if(input.size()==4)
						{
							moveLetter2 = input[0];
							moveNumber2 = (input[2] - '0')*10 +(input[3] - '0') ;
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
bool Hex::testSize(int boardSize) const
{
	if(boardSize<6 || boardSize>26)
	{
		cerr << "\nINVALID INPUT!\n";
		return false;
	}
	return true;
}
bool Hex::testType(int gameType) const
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
bool Hex::checkMove(char moveLetter, int &moveNumber) const
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

		hexCells[i][j].setState(cellState::winUser2); // winning path is marked with capital O

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

		if (endGame(i,   j-1) == true ) // WEST
		{
			return true;
		}
		if (endGame(i,   j+1) == true ) // EAST
		{
			 return true;
		}
		if (endGame(i-1, j)   == true ) return true; // NORTH-WEST
		if (endGame(i-1, j+1) == true ) // NORTH-EAST
		{
			return true;
		}
		if (endGame(i+1, j-1) == true ) return true; // SOUTH-WEST
		if (endGame(i+1, j)   == true )  // SOUTH-EAST
		{
			return true;
		}

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
		allPlays[playNum][0]=row;
		allPlays[playNum][1]=column;
		playNum++;
	}
	else if(type==1 && turn==1)
	{
		hexCells[row][column].setState(cellState::user1);
		allMarked++;
		marked++;
		turn=2;
		allPlays[playNum][0]=row;
		allPlays[playNum][1]=column;
		playNum++;
	}
	else
	{
		hexCells[row][column].setState(cellState::user2);
		allMarked++;
		marked++;
		turn=1;
		allPlays[playNum][0]=row;
		allPlays[playNum][1]=column;
		playNum++;
	}
}
Hex::Cell Hex::play()
{
	auto i=0,j=0;
	while(hexCells[i][j].getState() != cellState::empty)
	{
		i = randomNumberGenerator(width);
		j = randomNumberGenerator(height);
	}
	hexCells[i][j].setState(cellState::user1);
	Cell c(static_cast<char>(i+97), j,cellState::user1);
	allMarked++;

	allPlays[playNum][0]=i;
	allPlays[playNum][1]=j;
	playNum++;
	cout << "\nCOMPUTER MOVE-->" << static_cast<char>(j+65) << " " << i+1 << endl;
	return c;
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
		outStream << *this;
		cout << "\nGame saved into " << filename << endl;
		saved=true;
		outStream.close();
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
		inStream >> *this;
		loaded=true;
		inStream.close();
	}
}
void Hex::setGameNum(int num)
{
	gameNum=Hex::games;
}
int Hex::getGameNum() const
{
	return gameNum;
}
Hex::Hex(int boardSize, int typeValue)
{
	hexCells = new Cell*[26];
	allPlays = new int*[26*26];
	if(hexCells == nullptr)
	{
		cerr << "Error: Insufficient memory.";
		return;
	}
	for(int i = 0; i < 26; i++) hexCells[i] = new Cell[26];
	for(int i = 0; i < 26; i++) allPlays[i] = new int[10];
	for(int i=0 ; i<26 ; i++)
	{
		for(int j=0 ; j<26 ; j++)
		{
			hexCells[i][j]=Cell(static_cast<char>(i+97), i ,cellState::empty);
		}
	}
	width=boardSize;
	height=boardSize;
	type=typeValue;
	turn=1;
	marked=0;
	loaded=false;
	saved=false;
	win=false;
	gameNum=Hex::games;
	Hex::games++;
	playNum=0;
	score1=0;
	score2=0;
}
bool Hex::getWin() const
{
	return win;
}
int Hex::getAllMarked()
{
	return allMarked;
}
int Hex::getGames()
{
	return games;
}
