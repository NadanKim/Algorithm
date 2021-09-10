#include "Common.h"
#include "검색트리/BinarySearchTree.h"

int main()
{
	//int n = 9;
	//int* arr;

	//// 동작 테스트를 위한 값
	////arr = new int[n]{ 2, 4, 6, 8, 10, 9, 7, 5, 3, 1 };
	//arr = new int[n]{ 10, 5, 20, 3, 7, 15, 25, 1, 4 };

	//BinarySearchTree tree;
	//for (int i = 0; i < n; i++)
	//{
	//	tree.Insert(arr[i]);
	//}
	//tree.PrintBinarySearchTree();

	////tree.Delete(5);
	////tree.PrintBinarySearchTree();

	//// 출력하고 싶은 모양
	//std::cout << "         10\n";
	//std::cout << "    ┌────┴────┐\n";
	//std::cout << "    5         20\n";
	//std::cout << "  ┌─┴─┐     ┌─┴─┐\n";
	//std::cout << "  3   7    15   25\n";
	//std::cout << "┌─┴─┐\n";
	//std::cout << "1   4\n";

	//delete[] arr;

	BinarySearchNode node;
	node.data = 1;
	std::cout << node.ToString() << '\n';
	node.data = 12;
	std::cout << node.ToString() << '\n';
	node.data = 123;
	std::cout << node.ToString() << '\n';
	node.data = 1234;
	std::cout << node.ToString() << '\n';
	node.data = 12345;
	std::cout << node.ToString() << '\n';
}