#pragma once
#include <vector>
#include <string>

using namespace std;

class Board
{
public:
	Board();
	Board(int lines, int columns);
	void setLines(int lines);
	void setColumns(int columns);
	void setBoardSize();
	int getLines();
	int getColumns();
	vector<vector<char>> getBoard();
	string getBoardFile();
	void addCharToBoard(int line,int column,char character);
	void addStrBoardFile(string str);
private:
	int lines;
	int columns;
	vector<vector<char>> board;
	string board_file;
};

