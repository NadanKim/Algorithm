#pragma once
#include <iostream>

namespace Common
{
	void PrintArray(int arr[], int n)
	{
		for (int i = 0; i < n; i++)
		{
			std::cout << arr[i] << ' ';
		}
		std::cout << '\n';
	}

	void Swap(int arr[], int a, int b)
	{
		int temp{ arr[a] };
		arr[a] = arr[b];
		arr[b] = temp;
	}
}