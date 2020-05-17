#include "Menus.h"

void Introduction()
{
    cout << "\n\t\tWelcome to Board Builder!\n\n\n";
    cout << "\t       (Press any key to continue)";
    _getch(); clrscr();
}

void Dimension(Board* board)
{
    while (true)
    {
        cout << "\nInsert the number of lines you would like the board to have (min-5,max-20): ";
        int lines;
        cin >> lines;
        if (cin.fail())
        {
            if (cin.eof())
            {
                cin.clear();
                cout << "Invalid input." << endl;
            }
            else
            {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Invalid input." << endl;
            }
        }
        else if (cin.peek() != '\n')
        {
            cin.ignore(10000, '\n');
            cout << "Invalid input." << endl;
        }
        else if (lines < 5 || lines>20)
        {
            cout << "Invalid size." << endl;
        }
        else
        {
            board->setLines(lines);
            break;
        }
    }
    clrscr();
    while (true)
    {
        cout << "\nInsert the number of columns you would like the board to have (min-5,max-20): ";
        int columns;
        cin >> columns;
        if (cin.fail())
        {
            if (cin.eof())
            {
                cin.clear();
                cout << "Invalid input." << endl;
            }
            else
            {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Invalid input." << endl;
            }
        }
        else if (cin.peek() != '\n')
        {
            cin.ignore(10000, '\n');
            cout << "Invalid input." << endl;
        }
        else if (columns < 5 || columns>20)
        {
            cout << "Invalid size." << endl;
        }
        else
        {
            board->setColumns(columns);
            break;
        }
    }
    clrscr();
    board->setBoardSize();
    string str = to_string(board->getLines());
    str += " x " + to_string(board->getColumns());
    board->addStrBoardFile(str);
}

void Quit(Board* board)
{
    ofstream boardFile;
    boardFile.open("BOARD.txt");
    boardFile << board->getBoardFile();
    boardFile.close();
    clrscr();
}

