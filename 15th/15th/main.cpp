#include <windows.h>
#include <iostream>

struct Test {
    char a;
    long long b;
    char c;
    long long d;
    char e;
};

struct Test2 {
    long long b;
    long long d;
    char a;
    char c;
    char e;
};

int main() {
    std::cout << sizeof(Test) << '\n' << sizeof(Test2) << '\n';

    system("pause");
    return 0;
}