/**
  @file Utilities.h
  @author João Marinho
  @author Rodrigo Andrade
  Contains utility functions
*/

#pragma once
#define STD_OUTPUT_HANDLE ((DWORD)-11)
#include <fstream>
#include <iostream>
#include <algorithm> /* toupper */
#include <windows.h>
#include <string>

using namespace std;

/**
  @brief Clears the console screen output
*/
void clrscr();

/**
  @brief Changes the text color
  @param color int to be changed to
*/
void setcolor(unsigned int color);

/**
  @brief Verifies if a certain word belongs to the dictionary
  @param word String to be validated
  @return True if string belongs to the dictionary
*/
bool inDict(string word);