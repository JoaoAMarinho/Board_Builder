#pragma once
#define STD_OUTPUT_HANDLE ((DWORD)-11)
#include <fstream>
#include <iostream>
#include <algorithm> /* toupper */
#include <windows.h>
#include <string>

using namespace std;

//Clear screen function
void clrscr();

//Set color function
void setcolor(unsigned int color);

//Check if the word is in the dictionary
bool inDict(string word);