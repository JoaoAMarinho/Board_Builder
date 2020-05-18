/**
  @file Menus.h
  @author João Marinho
  @author Rodrigo Andrade
  Contains i/o menus
*/

#pragma once
#include <conio.h>    /* _getch */
#include <fstream>
#include "Board.h"
#include "Utilities.h"


/*
  @brief Inicial function, say hello to user
*/
void Introduction();

/*
  @brief Reads the dimension of the board and sets its dimension
  @param board pointer
*/
void Dimension(Board* board);

/*
  @brief End function that writes to the file the board created
  @param Board pointer
*/
void Quit(Board* board);