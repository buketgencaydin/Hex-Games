#ifndef helper_h
#define helper_h

#include <string>
using namespace std;
void printBoard(char board[12][12], const int &boardSize); // prints the board
bool checkMove(char moveLetter, int &moveNumber, char board[12][12], const int &boardSize); // checks the move validity
void computerMove(char board[12][12], int boardSize);
int randomNumberGenerator(int boardSize);
bool boardFull(char board[12][12], int boardSize); // checks the board is full or not
bool userWin(char board[12][12], int boardSize, int x=0, int y=0); // checks the user won or not
bool computerWin(char board[12][12], int boardSize, int x=0, int y=0); // checks the computer won or not
void clearBuffer(void);
void saveFile(char board[12][12], int boardSize, int gameType, string input, int turn);
void loadFile(char board[12][12], int &boardSize, int &gameType, string input, int &turn);

enum class cellState {user1='x', user2='o', empty='.', winUser1='X', winUser2='O'};

#endif 