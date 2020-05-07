#include "Board.h"

Board::Board() { lines = 0; columns = 0; setBoardSize();}
Board::Board(int lines, int columns) { this->lines = lines; this->columns = columns; setBoardSize(); }
void Board::setLines(int lines){ this->lines = lines; }
void Board::setColumns(int columns){ this->columns = columns; }
void Board::setBoardSize() { vector<vector<char>> v(lines, vector<char>(columns, ' ')); board = v; }
void Board::addStrBoardFile(string str) { board_file += str + '\n'; }
int Board::getLines() { return lines; }
int Board::getColumns() { return columns; }
string Board::getBoardFile() { return board_file; }
vector<vector<char>> Board::getBoard() { return board; }
void Board::addCharToBoard(int line, int column, char character) { board[line][column] = character; }

