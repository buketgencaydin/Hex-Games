#include "helper.h"
#include <iostream>
#include <string>
#include <limits>
#include <random>
#include <chrono>
#include <fstream>
using namespace std;

int main()
{
	int boardSize;
	char board[12][12];

	cout << "\n**************\n"
			"   HEX GAME  \n"
			"**************\n";

	/* Asking the user for the board size */
	cout << "\n6x6  7x7  8x8  9x9  10x10  11x11  12x12\n";
	cout << "Please select a board size above by typing a integer number from 6 to 12 --> ";
	cin >> boardSize;

	/* Validity check until user enters a valid input */
	while(boardSize<6 || boardSize>12)
	{
		clearBuffer();
		cerr << "\nINVALID INPUT!\n";
		cout << "\n6x6  7x7  8x8  9x9  10x10  11x11  12x12\n";
		cout << "Please select a board size above by typing an integer from 6 to 12 --> ";
		cin >> boardSize;
	}

	/* Filling the board with dots for the start position */
	for(int i=0 ; i<boardSize ; i++)
		for(int j=0 ; j<boardSize ; j++)
			board[i][j]=static_cast<char>(cellState :: empty);

	int gameType;
	/* Asking the user for the game type */
	cout << "\n1)Two Player 2)User versus Computer\n";
	cout << "Please select the game type above by typing 1 or 2 --> ";
	cin >> gameType;

	/* Validity check until user enters a valid input */
	while(boardSize<6 || boardSize>12)
	{
		clearBuffer();
		cerr << "\nINVALID INPUT!\n";
		cout << "\n1)Two Player 2)User versus Computer\n";
		cout << "Please select the game type above by typing 1 or 2 --> ";
		cin >> gameType;
	}

	printBoard(board, boardSize); // prints the initial board

	string input, str, filename;
	char moveLetter1, moveLetter2;
	decltype(boardSize) moveNumber1, moveNumber2;
	bool win = false;
	int pos, turn=1, count=0;
	bool flag=false;

	ifstream inStream;
	ofstream outStream;

	while(boardFull(board, boardSize) == false && win == false ) // game continues until all the board is filled or one of the players wins
	{
		switch(gameType)
		{
			case 1: // user1-user2
				switch(turn)
				{
					case 1: // user1
						cout << "EXAMPLE MOVES: A 1, C 3 --- EXAMPLE COMMANDS: LOAD FILE.txt, SAVE FILE.txt\nUSER1 MOVE-->";
						cin >> ws;

						getline(cin,input);

						if(input.size()>4)
						{
							str = input.substr(0,4);
							if(str == "LOAD")
							{
								loadFile( board, boardSize, gameType, input, turn);
								flag=true;
							}
							else if(str == "SAVE")
							{
								saveFile(board, boardSize, gameType, input, 1);
								flag=false;
							}
						}
						else
						{
							moveLetter1 = input[0];
							moveNumber1 = input[2] - '0';
							flag=checkMove(moveLetter1,moveNumber1, board, boardSize);
							if(flag==true)
							{
								board[moveNumber1-1][moveLetter1-'A']=static_cast<char>(cellState::user1);
								turn=2;
							}

						}
						/* checks whether user1 won or not */
						for(int i=0 ; i<boardSize ; i++)
						{
							if(computerWin(board, boardSize, i, 0)==true)
							{
								cout<<"\n****USER1 WON!****\n";
								//printBoard(board,boardSize);
								win=true;
							}
						}
						if(flag==true)printBoard(board, boardSize);

						break;

					case 2: // user2
						cout << "EXAMPLE MOVES: A 1, C 3 --- COMMANDS: LOAD FILE.txt, SAVE FILE.txt\nUSER2 MOVE-->";

						getline(cin,input);

						if(input.size()>4)
						{
							str = input.substr(0,4);
							if(str == "LOAD")
							{
								loadFile( board, boardSize, gameType, input, turn);
								flag=true;
							}
							else if(str == "SAVE")
							{
								saveFile(board, boardSize, gameType, input, 2);
								flag=false;
							}
						}
						else
						{
							moveLetter2 = input[0];
							moveNumber2 = input[2] - '0';
							flag=checkMove(moveLetter2,moveNumber2, board, boardSize);
							if(flag==true)
							{
								board[moveNumber2-1][moveLetter2-'A']=static_cast<char>(cellState::user2);
								turn=1;
							}

						}
						/* checks whether user2 won or not */
						for(int i=0 ; i<boardSize ; i++)
						{
							if(userWin(board, boardSize, 0, i)==true)
							{
								cout<<"\n****USER2 WON!****\n";
								win=true;
							}
						}
						if(flag == true) printBoard(board, boardSize);
						break;
				}
				break;

			case 2: // user-computer
				switch(turn)
				{
					case 1: // user
						cout << "EXAMPLE MOVES: A 1, C 3 --- COMMANDS: LOAD FILE.txt, SAVE FILE.txt\nUSER MOVE-->";
						cin >> ws;
						getline(cin,input);

						if(input.size()>4)
						{
							str = input.substr(0,4);
							if(str == "LOAD")
							{
								loadFile( board, boardSize, gameType, input, turn);
								flag=true;
							}
							else if(str == "SAVE")
							{
								saveFile(board, boardSize, gameType, input, 1);
								flag=false;
							}
						}
						else
						{
							moveLetter2 = input[0];
							moveNumber2 = input[2] - '0';
							flag=checkMove(moveLetter2,moveNumber2, board, boardSize);
							if(flag==true)
							{
								board[moveNumber2-1][moveLetter2-'A']=static_cast<char>(cellState::user2);
								turn=2;
							}

						}
						/* checks whether user won or not */
						for(int i=0 ; i<boardSize ; i++)
						{
							if(userWin(board, boardSize, 0, i)==true)
							{
								cout<<"\n****USER WON!****\n";
								win=true;
							}
						}
						if(flag == true) printBoard(board, boardSize);
						break;

					case 2: // computer
						computerMove(board, boardSize);

						/* checks whether computer won or not */
						for(int i=0 ; i<boardSize ; i++)
						{
							if(computerWin(board, boardSize, i, 0)==true)
							{
								cout<<"\n****COMPUTER WON!****\n";
								win=true;
							}
						}
						turn=1;
						printBoard(board, boardSize);
						break;
				}
				break;
		}

	}
	return 0;
}