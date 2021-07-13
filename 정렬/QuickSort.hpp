#pragma once
#include "../Common.hpp"

void QuickSort(int arr[], int p, int r, bool printData = false, int n = 0);
int Partition(int arr[], int p, int r);

/// <summary>
/// �־��� �迭�� �����Ѵ�.
/// </summary>
/// <param name="arr">������ ������ �迭</param>
/// <param name="n">�迭�� ����</param>
/// <param name="printData">�߰� ��� ��� ����</param>
void QuickSort(int arr[], int n, bool printData = false)
{
	if (printData)
	{
		Common::PrintArray(arr, n);
	}

	QuickSort(arr, 0, n - 1, printData, n);
}

/// <summary>
/// �־��� �迭�� �����Ѵ�.
/// </summary>
/// <param name="arr">������ ������ �迭</param>
/// <param name="p">�迭�� ���� �ε���</param>
/// <param name="r">�迭�� �� �ε���</param>
/// <param name="printData">�߰� ��� ��� ����</param>
/// <param name="n">�迭�� ����</param>
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
/// �־��� �迭���� �����Ѵ�.
/// </summary>
/// <param name="arr">������ ������ �迭</param>
/// <param name="p">�迭�� ���� �ε���</param>
/// <param name="r">�迭�� �� �ε���</param>
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