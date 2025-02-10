#include <iostream>
using namespace std;

int main()
{
    int a = 10;
    int& r = a;
    int* p = &a;
    int* rp = &r;

    cout << &p << '\n';
    cout << p << '\n';
    cout << rp << '\n';
    cout << &rp << '\n';
}