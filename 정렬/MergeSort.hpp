#pragma once
#include "../Common.h"

void MergeSort(int arr[], int tempArr[], int p, int r, bool printData = false, int n = 0);
void Merge(int arr[], int tempArr[], int p, int q, int r);

/// <summary>
/// 주어진 배열을 정렬한다.
/// </summary>
/// <param name="arr">정렬을 진행할 배열</param>
/// <param name="n">배열의 길이</param>
/// <param name="printData">중간 결과 출력 여부</param>
void MergeSort(int arr[], int n, bool printData = false)
{
	if (printData)
	{
		Common::PrintArray(arr, n);
	}

	int* tempArr = new int[n];

	MergeSort(arr, tempArr, 0, n, printData, n);

	delete[] tempArr;
}

/// <summary>
/// 주어진 배열을 정렬한다.
/// </summary>
/// <param name="arr">정렬을 진행할 배열</param>
/// <param name="tempArr">정렬 시 사용할 임시 배열</param>
/// <param name="p">배열의 시작 인덱스</param>
/// <param name="r">배열의 끝 인덱스</param>
/// <param name="printData">중간 결과 출력 여부</param>
/// <param name="n">배열의 길이</param>
void MergeSort(int arr[], int tempArr[], int p, int r, bool printData, int n)
{
	if (r - p <= 1)
	{
		return;
	}

	int q{ (p + r) / 2 };

	MergeSort(arr, tempArr, p, q, printData, n);
	MergeSort(arr, tempArr, q, r, printData, n);
	Merge(arr, tempArr, p, q, r);

	if (printData)
	{
		Common::PrintArray(arr, n);
	}
}

/// <summary>
/// 주어진 배열들을 병합한다.
/// </summary>
/// <param name="arr">정렬을 진행할 배열</param>
/// <param name="tempArr">정렬 시 사용할 임시 배열</param>
/// <param name="p">배열의 시작 인덱스</param>
/// <param name="q">배열의 중간 인덱스</param>
/// <param name="r">배열의 끝 인덱스</param>
void Merge(int arr[], int tempArr[], int p, int q, int r)
{
	int pi{ p }, qi{ q }, ti{ p };
	// 두 배열 비교하여 하나에 저장
	while (pi < q && qi < r)
	{
		if (arr[pi] < arr[qi])
		{
			tempArr[ti++] = arr[pi++];
		}
		else
		{
			tempArr[ti++] = arr[qi++];
		}
	}

	// 배열에 남은 값 처리
	while (pi < q)
	{
		tempArr[ti++] = arr[pi++];
	}
	while (qi < r)
	{
		tempArr[ti++] = arr[qi++];
	}

	for (int i = p; i < r; i++)
	{
		arr[i] = tempArr[i];
	}
}