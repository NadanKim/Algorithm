#include "Common.h"
#include "검색트리/BTree.h"

int main()
{
	int n = 9;
	int* arr;

	// 동작 테스트를 위한 값
	arr = new int[n]{ 10, 5, 20, 3, 7, 15, 25, 1, 4 };

	BTree tree;
	for (int i = 0; i < n; i++)
	{
		tree.Insert(arr[i]);
		tree.PrintTree();
	}

	tree.Delete(5);

	tree.Delete(10);

	tree.Delete(15);

	delete[] arr;
}