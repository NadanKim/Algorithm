#include "Sort/InsertionSort.hpp"
#include "Common.hpp"

int main()
{
	int n = 10;
	int* arr;

	// 동작 테스트를 위한 값
	arr = new int[n]{ 2, 4, 6, 8, 10, 9, 7, 5, 3, 1 };

	// 시간 테스트를 위한 값
	//n = Common::LoadRandomNumbersInFile(&arr);

	Common::StartClock();
	InsertionSort(arr, n/**/, true/**/);
	Common::StopClock();
	//Common::PrintElapsedTime();

	delete[] arr;
}