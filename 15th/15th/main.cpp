#include <iostream>
#include "BinarySearchTree.h"

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

struct Test3 {
    int a;

    ~Test3() {
        Clear();
    }

    void Clear() {
        a = 0;
    }
};

int main() {
    ////���� ũ��� ���̰� ����
    ////�� �����Ϸ��� ������ ������ �ʴ���
    //std::cout << sizeof(Test) << '\n' << sizeof(Test2) << '\n';
    //
    //Test3* t = new Test3();
    //
    ////�� ���� ����
    ////���̰� �ִٸ� ��� �ִ���
    //t->~Test3();
    //t->Clear();
    ////freeȣ���� ����
    ////�ϵ���� �ܿ��� ���̴� �ϳ� �ִ�
    //free(t);
    //
    ////delete t;

    BST<int> tree;
    tree.AddNode(50);
    tree.AddNode(30);
    tree.AddNode(20);
    tree.AddNode(70);
    tree.AddNode(75);
    tree.AddNode(73);
    tree.AddNode(80);
    tree.AddNode(65);

    tree.DeleteNode(50);

    system("pause");
    return 0;
}