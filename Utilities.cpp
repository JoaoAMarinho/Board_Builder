#include "Utilities.h"

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

void setcolor(unsigned int color)
{
    HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hcon, color);
}

bool inDict(string word) {
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
        if (word == dictWord)
        {
            exists = true;
            break;
        }

    }
    dict.close();
    return exists;
}