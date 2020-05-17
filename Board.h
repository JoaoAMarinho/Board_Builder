#pragma once
#include "Component.h"
#include "Utilities.h"
#include <sstream>
#include <vector>



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
	void Draw();                               //Function to draw the board
	bool addWords(Component* component);       //Check if the input is valid or if the user does not want to add more words
	bool fitsInBoard(Component* component);    //Checks if the word will be out of bounds in the board
	bool sameChar(Component* component);       //Checks if there are no letters different from the ones in the word already in the board (in the same position)
	bool rightInsertion(Component* component); //Checks if the word can be inserted without ruining other words, or creates invalid ones
private:
	int lines;
	int columns;
	vector<vector<char>> board;
	string board_file;
};

