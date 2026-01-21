#pragma once
#include <string>
#include <windows.h>

namespace CursorController {

    extern HANDLE hConsole;    // Handler
    extern bool cursorHidden;  // Is cursor hidden or not

    void RemoveCursor();  // Remove Cursor
    void MoveCursor(int x, int y);   // Move Cursor to {x,y}
    void ClearScreen();   // Clear Screen
    void SetSquareConsoleFont(short size = 8);  // Set cell size squarely
    void WriteAt(int x, int y, const std::string& text, int color = 7);  // Custom print
}