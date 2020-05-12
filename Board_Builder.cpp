#include "Board.h"
#include "Component.h"
#include "Utilities.h"
#include "Menus.h"

using namespace std;


int main()
{
    Board board;
    Introduction();                              //Inicial function
    Dimension(&board);                           //Set the dimension of the board
    board.Draw();                                       
    Component componentObject;                   //Create a default component to be added to the board
    Component* component = &componentObject;     //Create a pointer to the component object
    while (board.addWords(component))            //Add words to the board
    {
        if (board.fitsInBoard(component)) 
        {
            if (board.sameChar(component))
            {
                if (board.rightInsertion(component))
                {
                    cout << "The word was inserted with success.\n\n";
                    board.addStrBoardFile(component->getToFile());
                }
            }
            else
            {
                cout << "The word can not be inserted in the board.\n\n";
            }
        }
        else
        {
            cout << "The word is out of boundaries.\n\n";
        }
        board.Draw();
    }
    Quit(&board);                         //End function that writes to the file the board
    return 0;
}
