#pragma once
#include <string>

using namespace std;

class Component
{
public:
	Component();
	void setLine(int line);
	void setColumn(int column);
	void setOrientation(char orientation);
	void setWord(string word);
	void setToFile(string toFile);
	void setToFile();
	int getLine();
	int getColumn();
	char getOrientation();
	string getWord();
	string getToFile();
private:
	int line, column;
	char orientation;
	string word,toFile;
};

