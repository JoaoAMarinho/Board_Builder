#pragma once
#include <conio.h>    /* _getch */
#include <fstream>
#include "Board.h"
#include "Utilities.h"

//Inicial function
void Introduction();

//Set the dimension of the board
void Dimension(Board* board);

//End function that writes to the file the board
void Quit(Board* board);