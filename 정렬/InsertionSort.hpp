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