#include <windows.h>
#include <iostream>

void SetConsoleFontSize(int width, int height) {
    // �ܼ� �ڵ� ��������
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hConsole == INVALID_HANDLE_VALUE) {
        std::cerr << "Failed to get console handle." << std::endl;
        return;
    }

    // �ܼ� ��Ʈ ���� ����
    CONSOLE_FONT_INFOEX cfi;
    cfi.cbSize = sizeof(CONSOLE_FONT_INFOEX); // ����ü ũ�� ����
    if (!GetCurrentConsoleFontEx(hConsole, FALSE, &cfi)) {
        std::cerr << "Failed to get current console font info." << std::endl;
        return;
    }

    // ���ϴ� ��Ʈ �̸� (��: "Consolas")
    wcscpy_s(cfi.FaceName, L"Consolas");

    // ��Ʈ ũ�� ����
    cfi.dwFontSize.X = width;  // ���� ũ��
    cfi.dwFontSize.Y = height; // ���� ũ��

    // ��Ʈ ���� ����
    if (!SetCurrentConsoleFontEx(hConsole, FALSE, &cfi)) {
        std::cerr << "Failed to set console font." << std::endl;
    }
    else {
        std::cout << "Console font set to " << width << "x" << height << "." << std::endl;
    }
}

int main() {
    // ���� 12, ���� 24�� ����
    SetConsoleFontSize(1, 1);

    std::cout << "Console font size changed!" << std::endl;
    system("pause");
    return 0;
}