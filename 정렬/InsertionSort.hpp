#pragma once
#include "../Common.hpp"

/// <summary>
/// �־��� �迭�� �����Ѵ�.
/// </summary>
/// <param name="arr">������ ������ �迭</param>
/// <param name="n">�迭�� ����</param>
/// <param name="printData">�߰� ��� ��� ����</param>
void InsertionSort(int arr[], int n, bool printData = false)
{
	if (printData)
	{
		Common::PrintArray(arr, n);
	}

	for (int i = 1; i < n; i++)
	{
		for (int j = i; j > 0; j--)
		{
			if (arr[j] < arr[j - 1])
			{
				Common::Swap(arr, j, j - 1);
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