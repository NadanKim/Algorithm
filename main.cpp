﻿#include "Common.h"
#include "검색트리/BinarySearchTree.h"

int main()
{
	int n = 10;
	int* arr;

	// 동작 테스트를 위한 값
	arr = new int[n]{ 2, 4, 6, 8, 10, 9, 7, 5, 3, 1 };

	BinarySearchTree tree;
	for (int i = 0; i < n; i++)
	{
		tree.Insert(arr[i]);
	}
	tree.PrintBinarySearchTree();

	tree.Delete(5);
	tree.PrintBinarySearchTree();

	delete[] arr;
}