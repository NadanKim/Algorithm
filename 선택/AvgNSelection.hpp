#pragma once
#include "../Common.hpp"

int AvgNSelection(int arr[], int p, int r, int idx);
int Partition(int arr[], int p, int r);

/// <summary>
/// �־��� �迭���� idx ��°�� ���� ���� ã�´�.
/// </summary>
/// <param name="arr">������ ������ �迭</param>
/// <param name="n">�迭�� ����</param>
/// <param name="target">ã������ ��</param>
/// <param name="printData">��� ��� ����</param>
void AvgNSelection(int arr[], int n, int idx, bool printData = false)
{
	int result{ AvgNSelection(arr, 0, n - 1, idx) };

	if (printData)
	{
		std::cout << result << '\n';
	}
}

/// <summary>
/// �־��� �迭���� idx ��°�� ���� ���� ã�´�.
/// </summary>
/// <param name="arr">������ ������ �迭</param>
/// <param name="p">�迭�� ���� �ε���</param>
/// <param name="r">�迭�� �� �ε���</param>
/// <param name="target">ã������ ��</param>
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
/// �־��� �迭�� �� �� �������� ������.
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