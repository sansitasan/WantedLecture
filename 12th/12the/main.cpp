#include "String.h"
#include "List.h"
#include "Node.h"
#include "Tree.h"

int main() {
    Tree<String> tree("A");
    tree.AddChild("B");
    tree.AddChild("B", "B2");
    tree.AddChild("B", "B3");
    tree.AddChild("B3", "B31");

    tree.PreOrderTraverse();
    return 0;
}