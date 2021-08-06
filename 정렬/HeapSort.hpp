#pragma once
#include "../Common.h"

void BuildHeap(int arr[], int n);
void Heapify(int arr[], int k, int n);

/// <summary>
/// 주어진 배열을 정렬한다.
/// </summary>
/// <param name="arr">정렬을 진행할 배열</param>
/// <param name="n">배열의 길이</param>
/// <param name="printData">중간 결과 출력 여부</param>
void HeapSort(int arr[], int n, bool printData = false)
{
	if (printData)
	{
		Common::PrintArray(arr, n);
	}

	BuildHeap(arr, n);
	for (int i = n - 1; i > 0; i--)
	{
		Common::Swap(arr, 0, i);

		if (printData)
		{
			Common::PrintArray(arr, n);
		}

		Heapify(arr, 0, i);
	}
}

/// <summary>
/// 힙을 생성한다.
/// </summary>
/// <param name="arr">힙으로 만들 배열</param>
/// <param name="n">배열의 길이</param>
void BuildHeap(int arr[], int n)
{
	for (int i = n / 2; i >= 0; i--)
	{
		Heapify(arr, i, n);
	}
}

/// <summary>
/// 배열을 힙으로 만드는 처리
/// </summary>
/// <param name="arr">힙으로 만들 배열</param>
/// <param name="k">기준 점</param>
/// <param name="n">배열의 길이</param>
void Heapify(int arr[], int k, int n)
{
	int left{ 1 }, right{ 2 };
	if (k > 0)
	{
		left = k * 2 + 1;
		right = k * 2 + 2;
	}

	if (left >= n)
	{
		return;
	}

	int bigChild = left;
	if (right < n)
	{
		if (arr[right] > arr[left])
		{
			bigChild = right;
		}
	}

	if (arr[bigChild] > arr[k])
	{
		Common::Swap(arr, k, bigChild);
		Heapify(arr, bigChild, n);
	}
}