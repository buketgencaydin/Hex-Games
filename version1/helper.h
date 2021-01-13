#ifndef helper_h
#define helper_h


void printBoard(char board[12][12], int boardSize); // prints the board
bool checkMove(char moveLetter, int moveNumber, char board[12][12], int boardSize); // checks the move validity
void computerMove(char board[12][12], int boardSize);
int randomNumberGenerator(int boardSize);
bool boardFull(char board[12][12], int boardSize); // checks the board is full or not
bool userWin(char board[12][12], int boardSize, int x, int y); // checks the user won or not
bool computerWin(char board[12][12], int boardSize, int x, int y); // checks the computer won or not

#endif 
