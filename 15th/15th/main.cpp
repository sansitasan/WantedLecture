#include <windows.h>
#include <iostream>

void SetConsoleFontSize(int width, int height) {
    // 콘솔 핸들 가져오기
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hConsole == INVALID_HANDLE_VALUE) {
        std::cerr << "Failed to get console handle." << std::endl;
        return;
    }

    // 콘솔 폰트 정보 설정
    CONSOLE_FONT_INFOEX cfi;
    cfi.cbSize = sizeof(CONSOLE_FONT_INFOEX); // 구조체 크기 설정
    if (!GetCurrentConsoleFontEx(hConsole, FALSE, &cfi)) {
        std::cerr << "Failed to get current console font info." << std::endl;
        return;
    }

    // 원하는 폰트 이름 (예: "Consolas")
    wcscpy_s(cfi.FaceName, L"Consolas");

    // 폰트 크기 설정
    cfi.dwFontSize.X = width;  // 가로 크기
    cfi.dwFontSize.Y = height; // 세로 크기

    // 폰트 정보 적용
    if (!SetCurrentConsoleFontEx(hConsole, FALSE, &cfi)) {
        std::cerr << "Failed to set console font." << std::endl;
    }
    else {
        std::cout << "Console font set to " << width << "x" << height << "." << std::endl;
    }
}

int main() {
    // 가로 12, 세로 24로 설정
    SetConsoleFontSize(1, 1);

    std::cout << "Console font size changed!" << std::endl;
    system("pause");
    return 0;
}