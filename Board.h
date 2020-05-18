/**
  @file Board.h
  @author João Marinho
  @author Rodrigo Andrade
  Contains declaration of class Board
*/

#pragma once
#include "Component.h"
#include "Utilities.h"
#include <sstream>
#include <vector>



class Board
{
public:
	/**
	@brief Default constructor
	*/
	Board();
	/**
	  @brief Change value of member variable lines
	*/
	void setLines(int lines);
	/**
	  @brief Change value of member variable columns
	*/
	void setColumns(int columns);
	/**
	  @brief Fills the board with certain lines and columns with the char ' ' 
	*/
	void setBoardSize();
	/**
	  @brief Gets member variable lines
	  @return lines (member variable)
	*/
	int getLines() const;
	/**
	  @brief Gets member variable columns
	  @return columns (member variable)
	*/
	int getColumns()const;
	/**
	  @brief Gets member variable board
	  @return board (member variable)
	*/
	vector<vector<char>> getBoard()const;
	/**
	  @brief Gets member variable board_file
	  @return board_file (member variable)
	*/
	string getBoardFile()const;
	/**
	  @brief Adds a certain string to the member variable board_file
	  @param str - string that is added to the member variable board_file
	*/
	void addStrBoardFile(string str);
	/**
	  @brief Adds a certain char to a certain position of the board
	  @param line - line in which the char is being added
	  @param column - column in which the char is being added
	  @param character - character that is being added to the board
	*/
	void addCharToBoard(int line,int column,char character);
	/**
	  @brief Draws the board to the console
	*/
	void Draw();
	/**
	  @brief Check if the user wants to insert any more words to the board and/or if that input is valid
	  @param component - From class component, saves the information inputed by the user
	  @return True if the user wants to add another word to the board
	*/
	bool addWords(Component* component);
	/**
	  @brief Checks if the word will be out of bounds in the board
	  @param component - From class component, used to access the input of the user
	  @return True if the word will fit in the board
	*/
	bool fitsInBoard(Component* component);
	/**
	  @brief Checks if there are letters different from the ones in the word already in the board (in the same position)
	  @param component - From class component, used to access the input of the user
	  @return True if every char on the string (word) can be placed in the position requested by the user 
	*/
	bool sameChar(Component* component);
	/**
	  @brief Checks if the word can be inserted in the board without ruining other words or creates invalid ones
	  @param component - From class component, used to access the input of the user
	  @return True if the word can be inserted without problems in the board
	*/
	bool rightInsertion(Component* component);
private:
	int lines;
	int columns;
	vector<vector<char>> board;
	string board_file;
};

