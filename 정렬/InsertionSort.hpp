#pragma once
#include "../Common.h"

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

	for (int i = 1, j; i < n; i++)
	{
		int val{ arr[i] };
		for (j = i; j > 0; j--)
		{
			if (val < arr[j - 1])
			{
				arr[j] = arr[j - 1];
			}
			else
			{
				break;
			}
		}
		arr[j] = val;

		if (printData)
		{
			Common::PrintArray(arr, n);
		}
	}
}