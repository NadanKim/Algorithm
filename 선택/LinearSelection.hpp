#pragma once
#include "../Common.hpp"
#include "AvgNSelection.hpp"

int LinearSelection(int arr[], int midArr[], int p, int r, int idx);
int GetMidValue(int arr[], int midArr[], int p, int r);
int Partition(int arr[], int p, int r, int midValue);

/// <summary>
/// �־��� �迭���� idx ��°�� ���� ���� ã�´�.
/// </summary>
/// <param name="arr">������ ������ �迭</param>
/// <param name="n">�迭�� ����</param>
/// <param name="target">ã������ ��</param>
/// <param name="printData">��� ��� ����</param>
void LinearSelection(int arr[], int n, int idx, bool printData = false)
{
	int midArrCount = (n / 5) + 1;
	int* midArr = new int[midArrCount];

	int result{ LinearSelection(arr, midArr, 0, n - 1, idx) };

	if (printData)
	{
		std::cout << result << '\n';
	}

	delete[] midArr;
}

/// <summary>
/// �־��� �迭���� idx ��°�� ���� ���� ã�´�.
/// </summary>
/// <param name="arr">������ ������ �迭</param>
/// <param name="p">�迭�� ���� �ε���</param>
/// <param name="r">�迭�� �� �ε���</param>
/// <param name="target">ã������ ��</param>
int LinearSelection(int arr[], int midArr[], int p, int r, int idx)
{
	if (p - r < 5)
	{
		return AvgNSelection(arr, p, r, idx);
	}

	int q{ Partition(arr, p, r, GetMidValue(arr, midArr, p, r)) };
	int k{ q - p + 1 };
	if (idx < k)
	{
		return LinearSelection(arr, midArr, p, q - 1, idx);
	}
	else if (idx == k)
	{
		return arr[q];
	}
	else
	{
		return LinearSelection(arr, midArr, q + 1, r, idx - k);
	}
}

/// <summary>
/// �߰� ���� ã�� ��ȯ�Ѵ�.
/// </summary>
/// <param name="arr">��ü �迭</param>
/// <param name="midArr">�߰� �� ���� �迭</param>
/// <param name="p">�迭�� ���� �ε���</param>
/// <param name="r">�迭�� �� �ε���</param>
/// <returns>�߰� ��</returns>
int GetMidValue(int arr[], int midArr[], int p, int r)
{
	int midIdx{ 0 };
	int midTempArr[5];
	for (int i = p; i <= r;)
	{
		int j = 0;
		for (; j < 5 && i <= r; j++, i++)
		{
			midTempArr[j] = arr[i];
		}

		midArr[midIdx++] = AvgNSelection(midTempArr, 0, j - 1, 3);
	}

	return AvgNSelection(midTempArr, 0, midIdx - 1, midIdx / 2);
}

/// <summary>
/// �־��� �迭�� �� �� �������� ������.
/// </summary>
/// <param name="arr">������ ������ �迭</param>
/// <param name="p">�迭�� ���� �ε���</param>
/// <param name="r">�迭�� �� �ε���</param>
int Partition(int arr[], int p, int r, int midValue)
{
	int i{ p }, j{ p };
	int midValueIdx{ p };
	while (i < r && j < r)
	{
		if (arr[j] == midValue)
		{
			midValueIdx = j++;
			continue;
		}

		if (arr[j++] < midValue)
		{
			Common::Swap(arr, i, j - 1);
			i++;
		}
	}
	Common::Swap(arr, i, midValueIdx);

	return i;
}