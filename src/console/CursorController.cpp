#include "console/CursorController.h"

namespace CursorController {

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    bool cursorHidden = false;

    void RemoveCursor() {
        if (cursorHidden) return;

        CONSOLE_CURSOR_INFO info;
        if (GetConsoleCursorInfo(hConsole, &info)) {
            info.dwSize = 100;
            info.bVisible = FALSE;
            SetConsoleCursorInfo(hConsole, &info);
            cursorHidden = true;
        }
    }

    void MoveCursor(int x, int y) {
        COORD pos = { (SHORT)x, (SHORT)y };
        SetConsoleCursorPosition(hConsole, pos);
    }

    void ClearScreen() {
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        DWORD cellsWritten;
        DWORD cellCount;
        COORD homeCoords = {0, 0};

        GetConsoleScreenBufferInfo(hConsole, &csbi);
        cellCount = csbi.dwSize.X * csbi.dwSize.Y;

        FillConsoleOutputCharacterA(
            hConsole, ' ', cellCount, homeCoords, &cellsWritten
        );

        FillConsoleOutputAttribute(
            hConsole, csbi.wAttributes, cellCount, homeCoords, &cellsWritten
        );

        SetConsoleCursorPosition(hConsole, homeCoords);
    }

    void SetSquareConsoleFont(short size) {
        CONSOLE_FONT_INFOEX cfi;
        cfi.cbSize = sizeof(CONSOLE_FONT_INFOEX);
        cfi.nFont = 0;
        cfi.dwFontSize = { size, size };
        cfi.FontFamily = FF_DONTCARE;
        cfi.FontWeight = FW_NORMAL;
        wcscpy_s(cfi.FaceName, L"Consolas");

        SetCurrentConsoleFontEx(hConsole, FALSE, &cfi);
    }

    void WriteAt(int x, int y, const std::string& text, int color ) {
        COORD pos = { (SHORT)x, (SHORT)y };
        SetConsoleCursorPosition(hConsole, pos);
        SetConsoleTextAttribute(hConsole, color);
        DWORD written;
        WriteConsoleA(
            hConsole, text.c_str(),
            (DWORD)text.size(),
            &written, nullptr
        );
    }

} 
