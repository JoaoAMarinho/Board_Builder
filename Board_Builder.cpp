#define STD_OUTPUT_HANDLE ((DWORD)-11)
#include <iostream>
#include <windows.h>
#include <vector>
#include <string>
#include <conio.h>    /* _getch */
#include <fstream>
#include <algorithm> /* toupper */
#include <sstream>
#include "Board.h"
#include "Component.h"

using namespace std;

Board board; //Global board

//Clear screen function
void clrscr()
{
    COORD coordScreen = { 0, 0 }; // upper left corner
    DWORD cCharsWritten;
    DWORD dwConSize;
    HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hCon, &csbi);
    dwConSize = csbi.dwSize.X * csbi.dwSize.Y;
    FillConsoleOutputCharacter(hCon, TEXT(' '), dwConSize, coordScreen, &cCharsWritten);
    GetConsoleScreenBufferInfo(hCon, &csbi);
    FillConsoleOutputAttribute(hCon, csbi.wAttributes, dwConSize, coordScreen, &cCharsWritten);
    SetConsoleCursorPosition(hCon, coordScreen);
}
//Set color function
void setcolor(unsigned int color)
{
    HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hcon, color);
}
void Introduction()
{
    cout << "\n\t\tWelcome to Board Builder!\n\n\n";
    cout << "\t       (Press any key to continue)";
    _getch(); clrscr();
}
void Dimension()
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
        else if (lines<5||lines>20)
        {
            cout << "Invalid size." << endl;
        }else
        {
            board.setLines(lines);
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
            board.setColumns(columns);
            break;
        }
    }
    clrscr();
    board.setBoardSize();
    string str = to_string(board.getLines());
    str += " x " + to_string(board.getColumns());
    board.addStrBoardFile(str);
}
void Draw() {
    setcolor(112);
    cout << " ";
    for (int i = 0; i < board.getColumns(); i++)
    {
        cout << " " << char(97 + i);
    }
    setcolor(7);
    cout << endl;
    for (int i = 0; i < board.getLines(); i++)
    {
        setcolor(112);
        cout << char(65 + i);
        setcolor(7);
        for (int j = 0; j < board.getColumns(); j++)
        {
            cout << ' '<<board.getBoard()[i][j];
        }
        cout << endl;
    }
}
//Check if the word is in the dictionary
bool inDict(string word){
    ifstream dict;
    bool exists = false;
    dict.open("WORDS.txt");
    if (!dict.is_open())
    {
        cerr << "File Not Found!";
        exit(1);
    }
    string dictWord;
    while (getline(dict, dictWord))
    {
        transform(dictWord.begin(), dictWord.end(), dictWord.begin(), ::toupper);
        if (word==dictWord)
        {
            exists = true;
            break;
        }
        
    }
    dict.close();
    return exists;
}
//Check if the input is valid or if the user does not want to add more words
bool addWords(Component &component) {
    bool validInput = true;
    while (true)
    {
        validInput = true;
        cout << "\nInsert the position followed by the orientation and the word you want to add to the board (ex: Aa H APPLE):\n(Press Ctrl+Z if you don't want to add a new word)\n";
        char line=' ', column=' ', orientation=' ';
        string word;
        cin >> line;
        if (cin.fail())    //if no more words will be added
        {
            cin.clear();
            validInput = false;
            return false;
        }
        else if (int(line) < 65 || int(line)>(64 + board.getLines()))
        {
            cout << "Invalid line input." << endl;
            cin.ignore(1000, '\n');
            validInput = false;
        }
        if (validInput)
        {
            cin >> column;
        }
        if (cin.fail()&&validInput)
        {
            cin.clear();
            cout << "Invalid column input." << endl;
            validInput = false;
        }
        else if ((int(column) < 97 || int(column) > (96 + board.getColumns()))&& validInput)
        {
            cout << "Invalid column input." << endl;
            cin.ignore(1000, '\n');
            validInput = false;
        }
        if (validInput)
        {
            cin >> orientation;
        }
        if (cin.fail() && validInput)    
        {
            cin.clear();
            cout << "Invalid orientation input." << endl;
            validInput = false;
        }
        else if ((orientation=='H'||orientation=='V') && validInput)
        {
        }
        else if (validInput)
        {
            cout << "Invalid orientation input." << endl;
            cin.ignore(1000, '\n');
            validInput = false;

        }
        if (validInput)
        {
            cin >> word;
            transform(word.begin(), word.end(), word.begin(), ::toupper);
        }
        if (cin.fail() && validInput)
        {
            cin.clear();
            cout << "Invalid word input." << endl;
            validInput = false;
        }
        else if ((word.size()==0||word.size()==1) && validInput)
        {
            cout << "Invalid word input." << endl;
            cin.ignore(1000, '\n');
            validInput = false;
        }
        else if (!inDict(word) && validInput)
        {
            cout << "Inexistent word input." << endl;
            cin.ignore(1000, '\n');
            validInput = false;
        }
        if (validInput) // In case every input is valid
        {
            component.setLine(int(line)-65);
            component.setColumn(int(column)-97);
            component.setOrientation(orientation);
            component.setWord(word);
            string s(1, line);
            string d(1, column);
            string f(1, orientation);
            component.setToFile(s + d + " " + f + " " + word);
            cout << endl;
            return true;   
        }

    }

}
//Checks if the word will be out of bounds in the board
bool FitsInBoard(Component component)
{
    if (component.getOrientation()=='H')
    {
        if (component.getWord().size() + component.getColumn() <= board.getColumns())
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        if (component.getWord().size() + component.getLine() <= board.getLines())
        {
            return true;
        }
        else
        {
            return false;
        }
    }

}
//Checks if there are no letters different from the ones in the word already in the board (in the same position)
bool sameChar(Component component)
{
    if (component.getOrientation()=='H')
    {
        for (int i = 0; i < component.getWord().size(); i++)
        {
            if (board.getBoard()[component.getLine()][component.getColumn()+i]==' ')
            {
                continue;
            }
            else if (board.getBoard()[component.getLine()][component.getColumn() + i]== component.getWord()[i])
            {
                continue;
            }
            else
            {
                return false;
            }
        }
    }
    else
    {
        for (int i = 0; i < component.getWord().size(); i++)
        {
            if (board.getBoard()[component.getLine()+i][component.getColumn()] == ' ')
            {
                continue;
            }
            else if (board.getBoard()[component.getLine()+i][component.getColumn()] == component.getWord()[i])
            {
                continue;
            }
            else
            {
                return false;
            }
        }
    }
    return true;
}
//Checks if the word can be inserted without ruining other words, or creates invalid ones
bool rightInsertion(Component component)
{
    if (component.getOrientation()=='H')
    {
        string line;
        for (int i = 0; i < board.getColumns(); i++)
        {
            line += board.getBoard()[component.getLine()][i];
        }
        string newLine = line;
        for (int i = 0; i < component.getWord().size(); i++)
        {
            newLine[component.getColumn() + i] = component.getWord()[i];
        }
        if (line==newLine)
        {
            cout << "The word you want to insert is already in that position or is part of an existing board word.\n\n";
            return false;
        }
        else
        {
            istringstream iss1(line);
            vector<string> words1;   //Words from the original line
            for (int i = 0; i < line.size(); i++)
            {
                string str;
                iss1 >> str;
                if (str.size() > 1)
                {
                    words1.push_back(str);
                }
                else if (str=="")
                {
                    break;
                }
            }
            istringstream iss2(newLine);
            vector<string> words2;   //Words from the modified line
            for (int i = 0; i < newLine.size(); i++)
            {
                string str;
                iss2 >> str;
                if (str.size() > 1)
                {
                    words2.push_back(str);
                }
                else if (str == "")
                {
                    break;
                }
            }
            if (words1.size()==words2.size()|| words1.size()> words2.size())
            {
                cout << "The word can not be inserted in the board.\n\n";
                return false;
            }
            vector<Component> components;
            for (int i = 0; i < component.getWord().size(); i++)
            {
                string above="", under="";
                if (board.getBoard()[component.getLine()][component.getColumn()+i]==' ') //If the board is empty on that house we will check the above and lower lines of that column
                {
                    if (component.getLine()-1>=0)  //If the house in the above line is valid
                    {
                        if (board.getBoard()[component.getLine() - 1][component.getColumn() + i]!=' ')
                        {
                            above = board.getBoard()[component.getLine() - 1][component.getColumn() + i];
                            if (component.getLine() - 2 >= 0)  //If the house in the above 2 lines is valid
                            {
                                if (board.getBoard()[component.getLine() - 2][component.getColumn() + i] != ' ')  //If there is a word above that position then we will not insert the word
                                {
                                    cout << "The word can not be inserted in the board.\n\n";
                                    return false;
                                }
                            }
                        }
                    }
                    if (component.getLine()+1<board.getLines())  //If the house under has a valid line
                    {
                        if (board.getBoard()[component.getLine() + 1][component.getColumn() + i] != ' ')
                        {
                            under = board.getBoard()[component.getLine() + 1][component.getColumn() + i];
                            if (component.getLine() + 2 < board.getLines())   //If the house 2 lines under is valid
                            {
                                if (board.getBoard()[component.getLine() + 2][component.getColumn() + i] != ' ')
                                {
                                    cout << "The word can not be inserted in the board.\n\n";  //If there is a word under that position then we will not insert the word
                                    return false;
                                }
                            }

                        }
                    }
                    //If all the tests above have been passed we will check if the word formed is valid and if the user wants to insert it
                    if (above!=""||under!="")
                    {
                        string newWord = above + component.getWord()[i]+under;
                        if (inDict(newWord)) //If there is a new word created we will save it to the "components" vector
						{
							Component newComponent;
							newComponent.setOrientation('V');
							newComponent.setWord(newWord);
							if (above == "")
							{
								newComponent.setLine(component.getLine());
								newComponent.setColumn(component.getColumn() + i);
								newComponent.setToFile();
                                components.push_back(newComponent);
							}
							else
							{
								newComponent.setLine(component.getLine() - 1);
								newComponent.setColumn(component.getColumn() + i);
								newComponent.setToFile();
                                components.push_back(newComponent);
							}
						}
                        else
                        {
                            cout << "The word can not be inserted in the board.\n\n";  //If the word created by the insertion of that word is not in the dictionary, we will not insert that word
                            return false;
                        }
                    }
                }
            }
            //If the word can be inserted without destroying the existing ones we will see if there are new words formed and ask if he wants to add them
            for (int i = 0; i < components.size(); i++)
            {
                cout << "If you insert the word in this position you will form a new one ('" << components[i].getWord() << "').\n";
            }
            while (components.size()>0)
            {
                cout <<"Do you want to continue by adding the new word(s)? ('yes', 'no')\n";
                string input;
                cin >> input;
                if (cin.fail())
                {
                    cin.clear();
                    cout << "Invalid input.\n";
                }
                else if (cin.peek() != '\n')
                {
                    cin.ignore(1000, '\n');
                    cout << "Invalid input.\n";
                }
                else if (input == "yes")
                {
                    for (int i = 0; i < components.size(); i++)
                    {
                        board.addStrBoardFile(components[i].getToFile());
                    }
                    for (int i = 0; i < component.getWord().size(); i++)
                    {
                        board.addCharToBoard(component.getLine(), component.getColumn() + i, component.getWord()[i]);
                    }
                    return true;
                }
                else if (input == "no")
                {
                    cout << "Word not inserted.\n\n";
                    return false;
                }
                else
                {
                    cin.ignore(1000, '\n');
                    cout << "Invalid input.\n";
                }
            }
            for (int i = 0; i < component.getWord().size(); i++)
            {
                board.addCharToBoard(component.getLine(), component.getColumn() + i, component.getWord()[i]);
            }
            return true;
        }
    }
    else
    {
    string column;
    for (int i = 0; i < board.getLines(); i++)
    {
        column += board.getBoard()[i][component.getColumn()];
    }
    string newColumn = column;
    for (int i = 0; i < component.getWord().size(); i++)
    {
        newColumn[component.getLine() + i] = component.getWord()[i];
    }
    if (column == newColumn)
    {
        cout << "The word you want to insert is already in that position or is part of an existing board word.\n\n";
        return false;
    }
    else
    {
        istringstream iss1(column);
        vector<string> words1;   //Words from the original column
        for (int i = 0; i < column.size(); i++)
        {
            string str;
            iss1 >> str;
            if (str.size() > 1)
            {
                words1.push_back(str);
            }
            else if (str == "")
            {
                break;
            }
        }
        istringstream iss2(newColumn);
        vector<string> words2;   //Words from the modified column
        for (int i = 0; i < newColumn.size(); i++)
        {
            string str;
            iss2 >> str;
            if (str.size() > 1)
            {
                words2.push_back(str);
            }
            else if (str == "")
            {
                break;
            }
        }
        if (words1.size() == words2.size() || words1.size() > words2.size())
        {
            cout << "The word can not be inserted in the board.\n\n";
            return false;
        }
        vector<Component> components;
        for (int i = 0; i < component.getWord().size(); i++)
        {
            string left = "", right = "";
            if (board.getBoard()[component.getLine()+i][component.getColumn()] == ' ') //If the board is empty on that house we will check the left and right column of that line
            {
                if (component.getColumn() - 1 >= 0)  //If the house in the left column is valid
                {
                    if (board.getBoard()[component.getLine() + i][component.getColumn() - 1] != ' ')
                    {
                        left = board.getBoard()[component.getLine() + i][component.getColumn() - 1];
                        if (component.getColumn() - 2 >= 0)   //If the house in the left 2 columns is valid
                        {
                            if (board.getBoard()[component.getLine() + i][component.getColumn() - 2] != ' ')  //If there is a word left of that position then we will not insert the word
                            {
                                cout << "The word can not be inserted in the board.\n\n";
                                return false;
                            }
                        }
                    }
                }
                if (component.getColumn() + 1 < board.getColumns())  //If the house in the right column is valid
                {
                    if (board.getBoard()[component.getLine() + i][component.getColumn() + 1] != ' ')
                    {
                        right = board.getBoard()[component.getLine() + i][component.getColumn() + 1];
                        if (component.getColumn() + 2 < board.getColumns())   //If the house in the right 2 columns is valid
                        {
                            if (board.getBoard()[component.getLine() + i][component.getColumn() + 2] != ' ')
                            {
                                cout << "The word can not be inserted in the board.\n\n";  //If there is a word right of that position then we will not insert the word
                                return false;
                            }
                        }

                    }
                }
                //If all the tests above have been passed we will check if the word formed is valid and if the user wants to insert it
                if (left != "" || right != "")
                {
                    string newWord = left + component.getWord()[i] + right;
                    if (inDict(newWord)) //If there is a new word created we will save it to the "components" vector
                    {
                        Component newComponent;
                        newComponent.setOrientation('H');
                        newComponent.setWord(newWord);
                        if (left == "")
                        {
                            newComponent.setLine(component.getLine()+i);
                            newComponent.setColumn(component.getColumn());
                            newComponent.setToFile();
                            components.push_back(newComponent);
                        }
                        else
                        {
                            newComponent.setLine(component.getLine() +i);
                            newComponent.setColumn(component.getColumn()-1);
                            newComponent.setToFile();
                            components.push_back(newComponent);
                        }
                    }
                    else
                    {
                        cout << "The word can not be inserted in the board.\n\n";  //If the word created by the insertion of that word is not in the dictionary, we will not insert that word
                        return false;
                    }
                }
            }
        }
        //If the word can be inserted without destroying the existing ones we will see if there are new words formed and ask if he wants to add them
        for (int i = 0; i < components.size(); i++)
        {
            cout << "If you insert the word in this position you will form a new one ('" << components[i].getWord() << "').\n";
        }
        while (components.size() > 0)
        {
            cout << "Do you want to continue by adding the new word(s)? ('yes', 'no')\n";
            string input;
            cin >> input;
            if (cin.fail())
            {
                cin.clear();
                cout << "Invalid input.\n";
            }
            else if (cin.peek() != '\n')
            {
                cin.ignore(1000, '\n');
                cout << "Invalid input.\n";
            }
            else if (input == "yes")
            {
                for (int i = 0; i < components.size(); i++)
                {
                    board.addStrBoardFile(components[i].getToFile());
                }
                for (int i = 0; i < component.getWord().size(); i++)
                {
                    board.addCharToBoard(component.getLine() + i, component.getColumn(), component.getWord()[i]);
                }
                return true;
            }
            else if (input == "no")
            {
                cout << "Word not inserted.\n\n";
                return false;
            }
            else
            {
                cin.ignore(1000, '\n');
                cout << "Invalid input.\n";
            }
        }
        for (int i = 0; i < component.getWord().size(); i++)
        {
            board.addCharToBoard(component.getLine() + i, component.getColumn(), component.getWord()[i]);
        }
        return true;
    }
    }
}
//End function that writes to the file the board
void quit()
{
    ofstream boardFile;
    boardFile.open("BOARD.txt");
    boardFile << board.getBoardFile();
    boardFile.close();
    clrscr();
    cout << "\nBye\n";
}

int main()
{
    Introduction(); //Inicial function
    Dimension();    //Set the dimension of the board
    Draw();         //Function to draw the board
    Component component;  //Create a default component to be added to the board
    while (addWords(component)) //Add words to the board
    {
        if (FitsInBoard(component)) 
        {
            if (sameChar(component))
            {
                if (rightInsertion(component))
                {
                    cout << "The word was inserted with success.\n\n";
                    board.addStrBoardFile(component.getToFile());
                }
                else
                {
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
        Draw();
        //clrscr();

    }
    quit();
    return 0;
}
