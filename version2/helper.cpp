#include "helper.h"
#include <iostream>
#include <string>
#include <limits>
#include <random>
#include <chrono>
#include <fstream>
using namespace std;

void printBoard(char board[12][12], const int &boardSize)
{
	int i,j,k;
	char letters=97;
	for(i=0 ; i<boardSize ; i++)
		cout << "  " << letters++ ;

	for(i=0 ; i<boardSize ; i++)
	{
		cout << endl << i+1;
		for(k=0 ; k<i ; k++)
			cout << "  ";
		for(j=0 ; j<boardSize ; j++)
			cout << "  " << board[i][j];
	}
	cout << endl;
}
bool checkMove(char moveLetter, int &moveNumber, char board[12][12], const int &boardSize)
{
	char letters[12] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L'};

	/*
	   if input is invalid checkMove() returns false
	   it input is valid checkMove() returns true
	 */
	if(board[moveNumber-1][moveLetter-'A'] != static_cast<char>(cellState::empty) || moveLetter<letters[0] || moveLetter>letters[boardSize-1] || moveNumber<0 || moveNumber>boardSize)
	{
		cerr << "INVALID MOVE PLEASE TRY AGAIN.\n";
		return false;
	}
	return true;
}
int randomNumberGenerator(int boardSize)
{
	unsigned seed = (std::chrono::system_clock::now().time_since_epoch().count());
	default_random_engine generator(seed);
	uniform_int_distribution<int> distribution(0,boardSize);
	return distribution(generator);
}
void computerMove(char board[12][12], int boardSize)
{
	auto i=0,j=0;

	while(board[i][j] != static_cast<char>(cellState::empty))
	{
		i = randomNumberGenerator(boardSize);
		j = randomNumberGenerator(boardSize);
	}
	board[i][j]=static_cast<char>(cellState::user1);
	cout << "\nCOMPUTER MOVE-->" << static_cast<char>(j+65) << " " << i+1 << endl;
}
bool boardFull(char board[12][12], int boardSize)
{
	int count=0;

	for(int i=0 ; i<boardSize ; i++)
	{
		for(int j=0 ; j<boardSize ; j++)
			if(board[i][j] == static_cast<char>(cellState::empty)) count++;
	}
	if(count != 0) return false;
	else return true;
}
bool userWin(char board[12][12], int boardSize, int i, int j)
{
	if (i == boardSize ) return true; // reaching the opposite side
    if ( i < 0 || j < 0 || i > boardSize || j > boardSize) return false; // invalid positions
    if ( board[i][j] != static_cast<char>(cellState::user2)) return false;

    board[i][j] = static_cast<char>(cellState::winUser2); // winning path is marked with capital X

    if (userWin(board, boardSize,i,   j-1) == true ) return true; // WEST
    if (userWin(board, boardSize,i,   j+1) == true ) return true; // EAST
    if (userWin(board, boardSize,i-1, j)   == true ) return true; // NORTH-WEST
    if (userWin(board, boardSize,i-1, j+1) == true ) return true; // NORTH-EAST
    if (userWin(board, boardSize,i+1, j-1) == true ) return true; // SOUTH-WEST
    if (userWin(board, boardSize,i+1, j)   == true ) return true; // SOUTH-EAST

    board[i][j] = static_cast<char>(cellState::user2); // not winning path is unmarked
    return false;
}
bool computerWin(char board[12][12], int boardSize, int i, int j)
{
	if (j == boardSize ) return true; // reaching the opposite side
    if ( i < 0 || j < 0 || i > boardSize || j > boardSize ) return false; // invalid positions
    if ( board[i][j] != static_cast<char>(cellState::user1)) return false;

    board[i][j] = static_cast<char>(cellState::winUser1); // winning path is marked with capital X

    if (computerWin(board, boardSize,i,   j-1) == true ) return true; // WEST
    if (computerWin(board, boardSize,i+1, j)   == true ) return true; // SOUTH-EAST
    if (computerWin(board, boardSize,i,   j+1) == true ) return true; // EAST
    if (computerWin(board, boardSize,i-1, j)   == true ) return true; // NORTH-WEST
    if (computerWin(board, boardSize,i-1, j+1) == true ) return true; // NORTH-EAST
    if (computerWin(board, boardSize,i+1, j-1) == true ) return true; // SOUTH-WEST

    board[i][j] = static_cast<char>(cellState::user1); // not winning path is unmarked
    return false;
}
void clearBuffer(void) {cin.clear(); cin.ignore(256,'\n'); }
void saveFile(char board[12][12], int boardSize, int gameType, string input, int turn)
{
	ofstream outStream;
	string filename;

	int pos = input.find(".");
	filename = input.substr(5,pos-5);
	filename += ".txt";
	outStream.open(filename);

	if(outStream.fail()) cerr << "Output file opening failed.\n";
	else
	{
		outStream << boardSize << endl << gameType << endl << turn << endl;

		for(int i=0 ; i<boardSize ; i++)
		{
			for(int j=0 ; j<boardSize ; j++) outStream << board[i][j];
			outStream <<endl;
		}
		cout << "\nGAME SAVED\n";
		outStream.close();
	}
}
void loadFile(char board[12][12], int &boardSize, int &gameType, string input, int &turn)
{
	ifstream inStream;
	string filename;

	int pos = input.find(".");
	filename = input.substr(5,pos-5);
	filename += ".txt";
	inStream.open(filename);
	char ch;

	if(inStream.fail()) cerr << "Input file opening failed.\n";
	else
	{
		inStream >> boardSize >> gameType >> turn;

		for(int i=0 ; i<boardSize ; i++)
		{
			for(int j=0 ; j<boardSize ; j++) inStream >> board [i][j];
		}
		cout << "\nGAME LOADED\n";
		if(gameType==1) cout << "Game Type --> User vs User\n";
		else cout << "Game Type --> User vs Computer\n";
		inStream.close();
	}
}
