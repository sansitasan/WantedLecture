#include "BinaryTree.h"
#include <string>

int main() {
	BinaryTree<string> tree("1");
	tree.AddLeftChild("1", "2");
	tree.AddLeftChild("2", "4");
	tree.AddLeftChild("4", "8");
	tree.AddRightChild("4", "9");
	tree.AddRightChild("2", "5");
	tree.AddLeftChild("5", "10");
	tree.AddRightChild("5", "11");

	tree.AddRightChild("1", "3");
	tree.AddLeftChild("3", "6");
	tree.AddLeftChild("6", "12");
	tree.AddRightChild("6", "13");
	tree.AddRightChild("3", "7");
	tree.AddLeftChild("7", "14");
	tree.AddRightChild("7", "15");

	tree.PreOrderTraverse();
	tree.DeleteNode("6");

	tree.PreOrderTraverse();

	cin.get();
	return 0;
}