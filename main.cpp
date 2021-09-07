﻿#include "Common.h"
#include "검색트리/BinarySearchTree.h"

int main()
{
	int n = 7;
	int* arr;

	// 동작 테스트를 위한 값
	//arr = new int[n]{ 2, 4, 6, 8, 10, 9, 7, 5, 3, 1 };
	arr = new int[7]{ 10, 5, 20, 3, 7, 15, 25 };

	BinarySearchTree tree;
	for (int i = 0; i < n; i++)
	{
		tree.Insert(arr[i]);
	}
	tree.PrintBinarySearchTree();

	//tree.Delete(5);
	//tree.PrintBinarySearchTree();

	// 출력하고 싶은 모양
	std::cout << "       10\n";
	std::cout << "  ┌────┴────┐\n";
	std::cout << "  5         20\n";
	std::cout << "┌─┴─┐     ┌─┴─┐\n";
	std::cout << "5   20    5   20\n";

	delete[] arr;
}