The "Board Builder" program fulfilled all the proposed objectives:
-To select the size of the game board (minimum dimension of 5x5 and a maximum of 20x20).
-To create the game board.
-To save the contents of the board to a text file (in this case to "BOARD.TXT").

Two classes were created: class "Board" and class "Component". As well as two .cpp files named "Menus" and "Utilities".
The class "Component" is basically a way to structute the input of the user (line/column/orientation/word) so it is easier to check if a certain "Component" can fit the board.
As for the .cpp files, "Utilities" include 3 functions that help with the output (clear the screen and set colour) and the validation of a word.
In the "Menus" we have the introductory functions and the last one, this was done so that the classes don't have unecessary functions and are more general.

In terms of the program and the rules followed, if there is a word input that will destroy the words already in the board, the program will not allow it, although if a word input creats by accident a new word, the user will be asked if they want to accept that new word and add it to the "board builder" file.
The optional 2D view of the board was decided not to be included at the end of the file, however the board can be seen and its changes while the program is running.

João Marinho