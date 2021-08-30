#include "Common.h"
#include "검색트리/AVLTree.h"

int main()
{
	int n = 10;
	int* arr;

	// 동작 테스트를 위한 값
	arr = new int[n]{ 2, 4, 6, 8, 10, 9, 7, 5, 3, 1 };

	// 시간 테스트를 위한 값
	//n = Common::LoadRandomNumbersInFile(&arr);

	Common::StartClock();
	AVLTree tree;
	for (int i = 0; i < n; i++)
	{
		tree.Insert(arr[i]);
	}

	std::cout << std::boolalpha << tree.Exists(5) << '\n';
	tree.Delete(5);
	std::cout << std::boolalpha << tree.Exists(5) << '\n';
	Common::StopClock();
	//Common::PrintElapsedTime();

	delete[] arr;
}