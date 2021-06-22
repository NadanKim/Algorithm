#pragma once
#include "../Common.hpp"

void SelectionSort(int arr[], int n, bool printData = false)
{
	if (printData)
	{
		Common::PrintArray(arr, n);
	}

	for (int i = 1; i < n; i++)
	{
		int biggest{ n - i };
		for (int j = 0; j < n - i; j++)
		{
			if (arr[biggest] < arr[j])
			{
				biggest = j;
			}
		}
		Common::Swap(arr, biggest, n - i);

		if (printData)
		{
			Common::PrintArray(arr, n);
		}
	}
}