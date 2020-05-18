#include "Board.h"
#include "Component.h"
#include "Utilities.h"
#include "Menus.h"

using namespace std;

int main()
{
    Board board;
    Introduction(); 
    Dimension(&board);          
    board.Draw();
    Component componentObject;            
    Component* component = &componentObject;
    while (board.addWords(component))     
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
                else
                {
                    cout << "The word can not be inserted in the board.\n\n";
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
    Quit(&board);
    return 0;
}
