#include "helper.h"
#include <iostream>
#include <string>
#include <limits>
#include <random>
#include <chrono>
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
		cin.clear(); cin.ignore(256,'\n'); // clearing the buffer in case of input is not an integer
		cerr << "\nINVALID INPUT!\n";
		cout << "\n6x6  7x7  8x8  9x9  10x10  11x11  12x12\n";
		cout << "Please select a board size above by typing an integer from 6 to 12 --> ";
		cin >> boardSize;
	}

	/* Filling the board with dots for the start position */
	for(int i=0 ; i<boardSize ; i++)
		for(int j=0 ; j<boardSize ; j++)
			board[i][j]='.';

	int gameType;
	/* Asking the user for the game type */
	cout << "\n1)Two Player 2)User versus Computer\n";
	cout << "Please select the game type above by typing 1 or 2 --> ";
	cin >> gameType;

	/* Validity check until user enters a valid input */
	while(boardSize<6 || boardSize>12)
	{
		cin.clear(); cin.ignore(256,'\n'); // clearing the buffer in case of input is not an integer
		cerr << "\nINVALID INPUT!\n";
		cout << "\n1)Two Player 2)User versus Computer\n";
		cout << "Please select the game type above by typing 1 or 2 --> ";
		cin >> gameType;
	}

	printBoard(board, boardSize); // prints the initial board

	char moveLetter1, moveLetter2;
	int moveNumber1, moveNumber2;
	bool win = false;

	if(gameType==1) // user1-user2
	{
		while(boardFull(board, boardSize) == false && win == false ) // game continues until all the board is filled or one of the players wins
		{
			cout << "EXAMPLE MOVES: A 1, C 3\nUSER1 MOVE-->";
			cin >> moveLetter1 >> moveNumber1;

			/* Validity check until user enters a valid input */
			while(checkMove(moveLetter1,moveNumber1, board, boardSize) == false)
				cin  >> moveLetter1 >> moveNumber1;
			board[moveNumber1-1][moveLetter1-'A']='x';

			/* checks whether user1 won or not */
			for(int i=0 ; i<boardSize ; i++)
			{
				if(computerWin(board, boardSize, i, 0)==true)
				{
					cout<<"\n****USER1 WON!****\n";
					printBoard(board,boardSize);
					win=true;
				}
			}
			if(win == false) // if user1 did not win
			{
				printBoard(board,boardSize);

				cout << "EXAMPLE MOVES: A 1, C 3\nUSER2 MOVE-->";
				cin >> moveLetter2 >> moveNumber2;

				/* Validity check until user enters a valid input */
				while(checkMove(moveLetter2,moveNumber2, board, boardSize) == false)
					cin  >> moveLetter2 >> moveNumber2;
				board[moveNumber2-1][moveLetter2-'A']='o';

				/* checks whether user2 won or not */
				for(int i=0 ; i<boardSize ; i++)
				{
					if(userWin(board, boardSize, 0, i)==true)
					{
						cout<<"\n****USER2 WON!****\n";
						win=true;
					}
				}
				printBoard(board,boardSize);
			}
		}
	}
	else // user-computer
	{
		while(boardFull(board, boardSize) == false && win == false) // game continues until all the board is filled or one of the players wins
		{
			cout << "EXAMPLE MOVES: A 1, C 3\nUSER MOVE-->";
			cin >> moveLetter1 >> moveNumber1;

			/* Validity check until user enters a valid input */
			while(checkMove(moveLetter1,moveNumber1, board, boardSize) == false)
				cin  >> moveLetter1 >> moveNumber1;
			board[moveNumber1-1][moveLetter1-'A']='o';

			/* checks whether user won or not */
			for(int i=0 ; i<boardSize ; i++)
			{
				if(userWin(board, boardSize, 0, i)==true)
				{
					cout<<"\n****USER WON!****\n";
					printBoard(board,boardSize);
					win=true;
				}
			}
			if(win == false) // if user did not win
			{
				printBoard(board,boardSize);
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
				printBoard(board,boardSize);
			}
		}
	}
	return 0;
}




