#include "Board.h"

Board::Board() { lines = 0; columns = 0; setBoardSize();}
Board::Board(int lines, int columns) { this->lines = lines; this->columns = columns; setBoardSize(); }
void Board::setLines(int lines){ this->lines = lines; }
void Board::setColumns(int columns){ this->columns = columns; }
void Board::setBoardSize() { vector<vector<char>> v(lines, vector<char>(columns, ' ')); board = v; }
void Board::addStrBoardFile(string str) { board_file += str + '\n'; }
int Board::getLines() { return lines; }
int Board::getColumns() { return columns; }
string Board::getBoardFile() { return board_file; }
vector<vector<char>> Board::getBoard() { return board; }
void Board::addCharToBoard(int line, int column, char character) { board[line][column] = character; }
void Board::Draw() {
    setcolor(112);
    cout << " ";
    for (int i = 0; i < columns; i++)
    {
        cout << " " << char(97 + i);
    }
    setcolor(7);
    cout << endl;
    for (int i = 0; i < lines; i++)
    {
        setcolor(112);
        cout << char(65 + i);
        setcolor(7);
        for (int j = 0; j < columns; j++)
        {
            cout << ' ' << board[i][j];
        }
        cout << endl;
    }
}
bool Board::addWords(Component* component) {
    bool validInput = true;
    while (true)
    {
        validInput = true;
        cout << "\nInsert the position followed by the orientation and the word you want to add to the board (ex: Aa H APPLE):\n(Press Ctrl+Z if you don't want to add a new word)\n";
        char line = ' ', column = ' ', orientation = ' ';
        string word;
        cin >> line;
        if (cin.fail())    //if no more words will be added
        {
            cin.clear();
            validInput = false;
            return false;
        }
        else if (int(line) < 65 || int(line) > (64 + lines))
        {
            cout << "Invalid line input." << endl;
            cin.ignore(1000, '\n');
            validInput = false;
        }
        if (validInput)
        {
            cin >> column;
        }
        if (cin.fail() && validInput)
        {
            cin.clear();
            cout << "Invalid column input." << endl;
            validInput = false;
        }
        else if ((int(column) < 97 || int(column) > (96 + columns)) && validInput)
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
        else if ((orientation == 'H' || orientation == 'V') && validInput)
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
        else if ((word.size() == 0 || word.size() == 1) && validInput)
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
            component->setLine(int(line) - 65);
            component->setColumn(int(column) - 97);
            component->setOrientation(orientation);
            component->setWord(word);
            string s(1, line);
            string d(1, column);
            string f(1, orientation);
            component->setToFile(s + d + " " + f + " " + word);
            cout << endl;
            return true;
        }

    }

}
bool Board::fitsInBoard(Component* component)
{
    if (component->getOrientation() == 'H')
    {
        if (component->getWord().size() + component->getColumn() <= columns)
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
        if (component->getWord().size() + component->getLine() <= lines)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

}
bool Board::sameChar(Component* component)
{
    if (component->getOrientation() == 'H')
    {
        for (int i = 0; i < component->getWord().size(); i++)
        {
            if (board[component->getLine()][component->getColumn() + i] == ' ')
            {
                continue;
            }
            else if (board[component->getLine()][component->getColumn() + i] == component->getWord()[i])
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
        for (int i = 0; i < component->getWord().size(); i++)
        {
            if (board[component->getLine() + i][component->getColumn()] == ' ')
            {
                continue;
            }
            else if (board[component->getLine() + i][component->getColumn()] == component->getWord()[i])
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
bool Board::rightInsertion(Component* component)
{
    if (component->getOrientation() == 'H')
    {
        string line;
        for (int i = 0; i < columns; i++)
        {
            line += board[component->getLine()][i];
        }
        string newLine = line;
        for (int i = 0; i < component->getWord().size(); i++)
        {
            newLine[component->getColumn() + i] = component->getWord()[i];
        }
        if (line == newLine)
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
                else if (str == "")
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
            if (words1.size() == words2.size() || words1.size() > words2.size())
            {
                cout << "The word can not be inserted in the board.\n\n";
                return false;
            }
            vector<Component> components;
            for (int i = 0; i < component->getWord().size(); i++)
            {
                string above = "", under = "";
                if (board[component->getLine()][component->getColumn() + i] == ' ') //If the board is empty on that house we will check the above and lower lines of that column
                {
                    if (component->getLine() - 1 >= 0)  //If the house in the above line is valid
                    {
                        if (board[component->getLine() - 1][component->getColumn() + i] != ' ')
                        {
                            above = board[component->getLine() - 1][component->getColumn() + i];
                            if (component->getLine() - 2 >= 0)  //If the house in the above 2 lines is valid
                            {
                                if (board[component->getLine() - 2][component->getColumn() + i] != ' ')  //If there is a word above that position then we will not insert the word
                                {
                                    cout << "The word can not be inserted in the board.\n\n";
                                    return false;
                                }
                            }
                        }
                    }
                    if (component->getLine() + 1 < lines)  //If the house under has a valid line
                    {
                        if (board[component->getLine() + 1][component->getColumn() + i] != ' ')
                        {
                            under = board[component->getLine() + 1][component->getColumn() + i];
                            if (component->getLine() + 2 < lines)   //If the house 2 lines under is valid
                            {
                                if (board[component->getLine() + 2][component->getColumn() + i] != ' ')
                                {
                                    cout << "The word can not be inserted in the board.\n\n";  //If there is a word under that position then we will not insert the word
                                    return false;
                                }
                            }

                        }
                    }
                    //If all the tests above have been passed we will check if the word formed is valid and if the user wants to insert it
                    if (above != "" || under != "")
                    {
                        string newWord = above + component->getWord()[i] + under;
                        if (inDict(newWord)) //If there is a new word created we will save it to the "components" vector
                        {
                            Component newComponent;
                            newComponent.setOrientation('V');
                            newComponent.setWord(newWord);
                            if (above == "")
                            {
                                newComponent.setLine(component->getLine());
                                newComponent.setColumn(component->getColumn() + i);
                                newComponent.setToFile();
                                components.push_back(newComponent);
                            }
                            else
                            {
                                newComponent.setLine(component->getLine() - 1);
                                newComponent.setColumn(component->getColumn() + i);
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
                        addStrBoardFile(components[i].getToFile());
                    }
                    for (int i = 0; i < component->getWord().size(); i++)
                    {
                        addCharToBoard(component->getLine(), component->getColumn() + i, component->getWord()[i]);
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
            for (int i = 0; i < component->getWord().size(); i++)
            {
                addCharToBoard(component->getLine(), component->getColumn() + i, component->getWord()[i]);
            }
            return true;
        }
    }
    else
    {
        string column;
        for (int i = 0; i < lines; i++)
        {
            column += board[i][component->getColumn()];
        }
        string newColumn = column;
        for (int i = 0; i < component->getWord().size(); i++)
        {
            newColumn[component->getLine() + i] = component->getWord()[i];
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
            for (int i = 0; i < component->getWord().size(); i++)
            {
                string left = "", right = "";
                if (board[component->getLine() + i][component->getColumn()] == ' ') //If the board is empty on that house we will check the left and right column of that line
                {
                    if (component->getColumn() - 1 >= 0)  //If the house in the left column is valid
                    {
                        if (board[component->getLine() + i][component->getColumn() - 1] != ' ')
                        {
                            left = board[component->getLine() + i][component->getColumn() - 1];
                            if (component->getColumn() - 2 >= 0)   //If the house in the left 2 columns is valid
                            {
                                if (board[component->getLine() + i][component->getColumn() - 2] != ' ')  //If there is a word left of that position then we will not insert the word
                                {
                                    cout << "The word can not be inserted in the board.\n\n";
                                    return false;
                                }
                            }
                        }
                    }
                    if (component->getColumn() + 1 < columns)  //If the house in the right column is valid
                    {
                        if (board[component->getLine() + i][component->getColumn() + 1] != ' ')
                        {
                            right = board[component->getLine() + i][component->getColumn() + 1];
                            if (component->getColumn() + 2 < columns)   //If the house in the right 2 columns is valid
                            {
                                if (board[component->getLine() + i][component->getColumn() + 2] != ' ')
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
                        string newWord = left + component->getWord()[i] + right;
                        if (inDict(newWord)) //If there is a new word created we will save it to the "components" vector
                        {
                            Component newComponent;
                            newComponent.setOrientation('H');
                            newComponent.setWord(newWord);
                            if (left == "")
                            {
                                newComponent.setLine(component->getLine() + i);
                                newComponent.setColumn(component->getColumn());
                                newComponent.setToFile();
                                components.push_back(newComponent);
                            }
                            else
                            {
                                newComponent.setLine(component->getLine() + i);
                                newComponent.setColumn(component->getColumn() - 1);
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
                        addStrBoardFile(components[i].getToFile());
                    }
                    for (int i = 0; i < component->getWord().size(); i++)
                    {
                        addCharToBoard(component->getLine() + i, component->getColumn(), component->getWord()[i]);
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
            for (int i = 0; i < component->getWord().size(); i++)
            {
                addCharToBoard(component->getLine() + i, component->getColumn(), component->getWord()[i]);
            }
            return true;
        }
    }
}