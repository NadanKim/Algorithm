#pragma once
#include "../Common.h"

void BuildHeap(int arr[], int n);
void Heapify(int arr[], int k, int n);

/// <summary>
/// �־��� �迭�� �����Ѵ�.
/// </summary>
/// <param name="arr">������ ������ �迭</param>
/// <param name="n">�迭�� ����</param>
/// <param name="printData">�߰� ��� ��� ����</param>
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
/// ���� �����Ѵ�.
/// </summary>
/// <param name="arr">������ ���� �迭</param>
/// <param name="n">�迭�� ����</param>
void BuildHeap(int arr[], int n)
{
	for (int i = n / 2; i >= 0; i--)
	{
		Heapify(arr, i, n);
	}
}

/// <summary>
/// �迭�� ������ ����� ó��
/// </summary>
/// <param name="arr">������ ���� �迭</param>
/// <param name="k">���� ��</param>
/// <param name="n">�迭�� ����</param>
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