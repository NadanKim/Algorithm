#include "정렬/MergeSort.hpp"
#include "Common.hpp"

int main()
{
	int n = 10;
	int* arr;

	// 동작 테스트를 위한 값
	//arr = new int[n]{ 10, 8, 6, 4, 2, 9, 7, 5, 3, 1 };

	// 시간 테스트를 위한 값
	n = Common::LoadRandomNumbersInFile(&arr);

	Common::StartClock();
	MergeSort(arr, n/*/, true/**/);
	Common::StopClock();
	Common::PrintElapsedTime();

	delete[] arr;
}