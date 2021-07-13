#pragma once
#include "../Common.hpp"

void QuickSort(int arr[], int p, int r, bool printData = false, int n = 0);
int Partition(int arr[], int p, int r);

/// <summary>
/// 주어진 배열을 정렬한다.
/// </summary>
/// <param name="arr">정렬을 진행할 배열</param>
/// <param name="n">배열의 길이</param>
/// <param name="printData">중간 결과 출력 여부</param>
void QuickSort(int arr[], int n, bool printData = false)
{
	if (printData)
	{
		Common::PrintArray(arr, n);
	}

	QuickSort(arr, 0, n - 1, printData, n);
}

/// <summary>
/// 주어진 배열을 정렬한다.
/// </summary>
/// <param name="arr">정렬을 진행할 배열</param>
/// <param name="p">배열의 시작 인덱스</param>
/// <param name="r">배열의 끝 인덱스</param>
/// <param name="printData">중간 결과 출력 여부</param>
/// <param name="n">배열의 길이</param>
void QuickSort(int arr[], int p, int r, bool printData, int n)
{
	if (r - p < 1)
	{
		return;
	}

	int q{ Partition(arr, p, r) };

	if (printData)
	{
		Common::PrintArray(arr, n);
	}

	QuickSort(arr, p, q - 1, printData, n);
	QuickSort(arr, q + 1, r, printData, n);
}

/// <summary>
/// 주어진 배열들을 병합한다.
/// </summary>
/// <param name="arr">정렬을 진행할 배열</param>
/// <param name="p">배열의 시작 인덱스</param>
/// <param name="r">배열의 끝 인덱스</param>
int Partition(int arr[], int p, int r)
{
	int i{ p }, j{ p };
	while (i < r && j < r)
	{
		if (arr[j++] < arr[r])
		{
			Common::Swap(arr, i, j - 1);
			i++;
		}
	}
	Common::Swap(arr, i, r);

	return i;
}