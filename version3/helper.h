#ifndef helper_h
#define helper_h

#include <string>
#include <vector>
using namespace std;

enum class cellState {user1='x', user2='o', empty='.', winUser1='X', winUser2='O'};

class Hex
{
private:
	class Cell
	{
	public:
		char position;
		int row;
		cellState state;
		cellState getState();
		void setState(cellState s);
		void setPosition(char p);
		char getPosition();
		void setRow(int r);
		int getRow();

	};
	vector<vector<Cell> > hexCells;

public:
	void readFile();
	void writeFile();
	int getWidth();
	int getHeight();
	void displayBoard();
	void play(); // computer play
	void play(int row, int column); // user play
	bool endGame(int i, int j);
	void playGame();
	int width, height, type, turn, gameNum,marked=0;
	int getMarked();
	void setGameNum(int num);
	int getGameNum();
	bool loaded=false,saved=false, win=false;
	bool getWin();
	bool testSize(int boardSize);
	bool testType(int gameType);
	void fillBoardDot();
	bool checkMove(char moveLetter, int &moveNumber);
	void saveFile(const string num);
	void loadFile(const string filename);
	static int getAllMarked();
	bool compareMarked(Hex other);
	static int allMarked;

	/* Constructors */
	Hex();
	Hex(int widthValue, int heightValue);
	Hex(int boardSize);
};
void printMenu();
int randomNumberGenerator(int boardSize);

#endif 