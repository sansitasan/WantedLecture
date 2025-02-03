#include "Queue.h"
#include <iostream>
#include "Location2D.h"
#include <Windows.h>

Location2D startPos;
Location2D endPos;
const size_t MAZE_SIZE = 20;
char map[MAZE_SIZE][MAZE_SIZE] =
{
    {'1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1'},
    {'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1', '0', '0', '0', '1'},
    {'1', '0', '1', '1', '1', '1', '1', '1', '1', '0', '1', '0', '1', '0', '1', '0', '1'},
    {'1', '0', '1', '0', '0', '0', '1', '0', '0', '0', '1', '0', '0', '0', '1', '0', '1'},
    {'1', '0', '1', '0', '1', '0', '1', '0', '1', '1', '1', '1', '1', '1', '1', '0', '1'},
    {'1', '0', '0', '0', '1', '0', '1', '0', '0', '0', '0', '0', '0', '0', '1', '0', '1'},
    {'1', '1', '1', '1', '1', '0', '1', '1', '1', '1', '1', '1', '1', '0', '1', '0', '1'},
    {'s', '0', '1', '0', '0', '0', '0', '0', '0', '0', '1', '0', '0', '0', '1', '0', '1'},
    {'1', '0', '1', '1', '1', '1', '1', '1', '1', '0', '1', '0', '1', '1', '1', '0', '1'},
    {'1', '0', '1', '0', '0', '0', '0', '0', '1', '0', '1', '0', '1', '0', '1', '0', '1'},
    {'1', '0', '1', '0', '1', '1', '1', '0', '1', '0', '1', '0', '1', '0', '1', '0', '1'},
    {'1', '0', '0', '0', '1', '0', '1', '0', '1', '0', '1', '0', '1', '0', '0', '0', '1'},
    {'1', '1', '1', '1', '1', '0', '1', '0', '1', '1', '1', '0', '1', '1', '1', '0', '1'},
    {'1', '0', '0', '0', '0', '0', '1', '0', '0', '0', '1', '0', '0', '0', '1', '0', '1'},
    {'1', '0', '1', '1', '1', '1', '1', '1', '1', '0', '1', '1', '1', '0', '1', '0', '1'},
    {'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1', '0', 'e'},
    {'1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1'}
};

bool IsVaildLocation(int row, int column) {
    if (row >= MAZE_SIZE || column >= MAZE_SIZE) return false;
    if (row < 0 || column < 0) return false;

    return map[row][column] == '0' || map[row][column] == 'e';
}

void DrawMap() {
    std::cout << '\n';
    for (int i = 0; i < MAZE_SIZE; ++i) {
        for (int j = 0; j < MAZE_SIZE; ++j) {
            if (map[i][j] == 's') {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
            }
            else if (map[i][j] == '0') {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN);
            }

            else {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY);
            }
            std::cout << map[i][j] << ' ';
        }
        std::cout << '\n';
    }
    std::cout << '\n';
}

//화면 지우기
void ClearScreen() {
    CONSOLE_CURSOR_INFO info = {};

    info.dwSize = 1;
    info.bVisible = FALSE;

    static HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorInfo(handle, &info);

    //for (int i = 0; i < MAZE_SIZE; ++i) {
    //    for (int j = 0; j < MAZE_SIZE; ++j) {
    //        std::cout << " ";
    //    }
    //    std::cout << '\n';
    //}

    SetConsoleCursorPosition(handle, { 0, 0 });
}

void Init() {
    for (int i = 0; i < MAZE_SIZE; ++i) {
        for (int j = 0; j < MAZE_SIZE; ++j) {
            if (map[i][j] == '.') {
                map[i][j] = '0';
            }
        }
    }
    map[startPos.row][startPos.column] = 's';
    map[endPos.row][endPos.column] = 'e';
    ClearScreen();
    for (int i = 0; i < MAZE_SIZE; ++i) {
        for (int j = 0; j < MAZE_SIZE; ++j) {
            std::cout << " ";
        }
        std::cout << '\n';
    }
    ClearScreen();
}

int main() {
    int startRow = 0, startColumn = 0;
    int row, column;

    for (int i = 0; i < MAZE_SIZE; ++i) {
        for (int j = 0; j < MAZE_SIZE; ++j) {
            if (map[i][j] == 's') {
                startRow = i;
                startColumn = j;
                startPos = Location2D(i, j);
            }

            else if (map[i][j] == 'e') {
                endPos = Location2D(i, j);
            }
        }
    }

    while (true) {
        bool flag = false;
        Queue<Location2D, 1000> locationQueue;
        locationQueue.Enqueue(Location2D(startRow, startColumn));
        Location2D current;

        while (!locationQueue.IsEmpty()) {
            ClearScreen();
            locationQueue.Dequeue(current);
            row = current.row;
            column = current.column;

            if (map[row][column] == 'e') {
                flag = true;
            }

            map[row][column] = 's';
            DrawMap();
            map[row][column] = '.';

            if (flag) {
                std::cout << "\n미로 탐색 성공\n";
                break;
            }

            if (IsVaildLocation(row - 1, column)) {
                locationQueue.Enqueue(Location2D(row - 1, column));
            }
            if (IsVaildLocation(row + 1, column)) {
                locationQueue.Enqueue(Location2D(row + 1, column));
            }
            if (IsVaildLocation(row, column - 1)) {
                locationQueue.Enqueue(Location2D(row, column - 1));
            }
            if (IsVaildLocation(row, column + 1)) {
                locationQueue.Enqueue(Location2D(row, column + 1));
            }
            Sleep(167);
        }

        Sleep(500);
        Init();
    }

	return 0;
}