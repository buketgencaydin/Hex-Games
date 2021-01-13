#include "helper.h"
#include <iostream>
#include <string>
#include <limits>
#include <random>
#include <chrono>
#include <fstream>
#include <vector>
using namespace std;

int Hex::allMarked=0;
int main()
{
	int choice, games=0, act, count=0,first,second;
	int marked;
	Hex game[20];

	do
	{
		printMenu();
		cin >> choice;
		cin.clear(); cin.ignore(256,'\n');
		switch(choice)
		{
			case 1:
				game[games].fillBoardDot();
				game[games].setGameNum(games);
				game[games].playGame();
				games++;
				break;

			case 2:
				cout << "\nACTIVE GAMES\n";
				for(int i=0 ; i<games ; i++)
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
				for(int i=0 ; i<games ; i++)
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
					if(game[first-1].compareMarked(game[second-1]))
					{
						cout << "\nGame"<< first << "-->"<< game[first-1].getMarked();
						cout << "  Game"<< second << "-->"<< game[second-1].getMarked();
						cout << "\nGame"<< first << " has more marked cells for the user\n";
					}
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
				cout << "\nNumber of marked cells in all the games is " << Hex::allMarked<<endl;
				break;

			case 5:
				break;
			default :
				cout << "INVALID INPUT!\n";
		}

	}while(choice!=5); // program ends if user wants to exit
	return 0;
}