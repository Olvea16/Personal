// ADA_Assignment_3.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "AVLTree.h"

int main()
{
	AVLTree<int> tree;

	for (int i = 0; i < 11; i++) tree.insert(i);

    return 0;
}

