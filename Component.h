#pragma once
#include <string>

using namespace std;

class Component
{
public:
	/**
	@brief Default constructor
	*/
	Component();
	/**
	  @brief Change value of member variable line
	*/
	void setLine(int line);
	/**
	  @brief Change value of member variable column
	*/
	void setColumn(int column);
	/**
	  @brief Change value of member variable orientation
	*/
	void setOrientation(char orientation);
	/**
	  @brief Change value of member variable word
	*/
	void setWord(string word);
	/**
	  @brief Change value of member variable toFile (1º string to file)
	*/
	void setToFile();
	/**
	  @brief Change value of member variable toFile (All of the other strings to file)
	*/
	void setToFile(string toFile);
	/**
	  @brief Gets member variable line
	  @return line (member variable)
	*/
	int getLine()const;
	/**
	  @brief Gets member variable column
	  @return column (member variable)
	*/
	int getColumn()const;
	/**
	  @brief Gets member variable orientation
	  @return orientation (member variable)
	*/
	char getOrientation()const;
	/**
	  @brief Gets member variable word
	  @return word (member variable)
	*/
	string getWord()const;
	/**
	  @brief Gets member variable toFile
	  @return toFile (member variable)
	*/
	string getToFile()const;
private:
	int line, column;
	char orientation;
	string word,toFile;
};

