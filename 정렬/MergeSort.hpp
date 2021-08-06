#pragma once
#include "../Common.h"

void MergeSort(int arr[], int tempArr[], int p, int r, bool printData = false, int n = 0);
void Merge(int arr[], int tempArr[], int p, int q, int r);

/// <summary>
/// �־��� �迭�� �����Ѵ�.
/// </summary>
/// <param name="arr">������ ������ �迭</param>
/// <param name="n">�迭�� ����</param>
/// <param name="printData">�߰� ��� ��� ����</param>
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
/// �־��� �迭�� �����Ѵ�.
/// </summary>
/// <param name="arr">������ ������ �迭</param>
/// <param name="tempArr">���� �� ����� �ӽ� �迭</param>
/// <param name="p">�迭�� ���� �ε���</param>
/// <param name="r">�迭�� �� �ε���</param>
/// <param name="printData">�߰� ��� ��� ����</param>
/// <param name="n">�迭�� ����</param>
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
/// �־��� �迭���� �����Ѵ�.
/// </summary>
/// <param name="arr">������ ������ �迭</param>
/// <param name="tempArr">���� �� ����� �ӽ� �迭</param>
/// <param name="p">�迭�� ���� �ε���</param>
/// <param name="q">�迭�� �߰� �ε���</param>
/// <param name="r">�迭�� �� �ε���</param>
void Merge(int arr[], int tempArr[], int p, int q, int r)
{
	int pi{ p }, qi{ q }, ti{ p };
	// �� �迭 ���Ͽ� �ϳ��� ����
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

	// �迭�� ���� �� ó��
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