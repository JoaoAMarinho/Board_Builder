#include "Component.h"

Component::Component() { line = -1; column = -1; orientation = ' '; word = ""; toFile = ""; }

void Component::setLine(int line) { this->line = line; }

void Component::setColumn(int column) { this->column = column; }

void Component::setOrientation(char orientation) { this->orientation = orientation; }

void Component::setWord(string word) { this->word = word; }

void Component::setToFile(string toFile) { this->toFile = toFile; }

int Component::getLine()const { return line; }

int Component::getColumn()const { return column; }

char Component::getOrientation()const { return orientation; }

string Component::getWord()const { return word; }

string Component::getToFile()const { return toFile; }

void Component::setToFile()
{
	string str;
	string s(1, char(65+line));
	string d(1, char(97+column));
	string f(1, orientation);
	str += s+ d+" "+f+" "+word;
	toFile = str;
}