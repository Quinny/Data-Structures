#include <iostream>
#include "BinaryTree.h"

using namespace std;

int main(void){

	BinaryTree<int> tree;

	tree.insert(4);
	tree.insert(5);
	tree.insert(3);

	tree.displayIn();

	return 0;
}