#pragma once
#include "../Common.h"

/// <summary>
/// 주어진 배열을 정렬한다.
/// </summary>
/// <param name="arr">정렬을 진행할 배열</param>
/// <param name="n">배열의 길이</param>
/// <param name="printData">중간 결과 출력 여부</param>
void BubbleSort(int arr[], int n, bool printData = false)
{
	if (printData)
	{
		Common::PrintArray(arr, n);
	}

	for (int i = 1; i < n; i++)
	{
		for (int j = 0; j < n - i; j++)
		{
			if (arr[j] > arr[j + 1])
			{
				Common::Swap(arr, j, j + 1);
			}
		}

		if (printData)
		{
			Common::PrintArray(arr, n);
		}
	}
}