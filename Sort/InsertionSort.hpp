#pragma once
#include "../Common.hpp"

/// <summary>
/// 주어진 배열을 정렬한다.
/// </summary>
/// <param name="arr">정렬을 진행할 배열</param>
/// <param name="n">배열의 길이</param>
/// <param name="printData">중간 결과 출력 여부</param>
void InsertionSort(int arr[], int n, bool printData = false)
{
	if (printData)
	{
		Common::PrintArray(arr, n);
	}

	for (int i = 1; i < n; i++)
	{
		int curIdx{ i };
		for (int j = i - 1; j >= 0; j--)
		{
			if (arr[curIdx] < arr[j])
			{
				Common::Swap(arr, curIdx, j);
				curIdx = j;
			}
			else
			{
				break;
			}
		}

		if (printData)
		{
			Common::PrintArray(arr, n);
		}
	}
}