#pragma once
#include "../Common.hpp"

int AvgNSelection(int arr[], int p, int r, int idx);
int Partition(int arr[], int p, int r);

/// <summary>
/// 주어진 배열에서 idx 번째로 작은 값을 찾는다.
/// </summary>
/// <param name="arr">정렬을 진행할 배열</param>
/// <param name="n">배열의 길이</param>
/// <param name="target">찾으려는 값</param>
/// <param name="printData">결과 출력 여부</param>
void AvgNSelection(int arr[], int n, int idx, bool printData = false)
{
	int result{ AvgNSelection(arr, 0, n - 1, idx) };

	if (printData)
	{
		std::cout << result << '\n';
	}
}

/// <summary>
/// 주어진 배열에서 idx 번째로 작은 값을 찾는다.
/// </summary>
/// <param name="arr">정렬을 진행할 배열</param>
/// <param name="p">배열의 시작 인덱스</param>
/// <param name="r">배열의 끝 인덱스</param>
/// <param name="target">찾으려는 값</param>
int AvgNSelection(int arr[], int p, int r, int idx)
{
	if (p == r)
	{
		return arr[p];
	}

	int q{ Partition(arr, p, r) };
	int k{ q - p + 1 };
	if (idx < k)
	{
		return AvgNSelection(arr, p, q - 1, idx);
	}
	else if (idx == k)
	{
		return arr[q];
	}
	else
	{
		return AvgNSelection(arr, q + 1, r, idx - k);
	}
}

/// <summary>
/// 주어진 배열을 끝 값 기준으로 나눈다.
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