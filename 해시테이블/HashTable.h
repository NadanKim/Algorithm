#pragma once
#include "../Common.h"

/// <summary>
/// �ؽ� ���̺��� ���� ��� �׽�Ʈ�� ���� ���̽� Ŭ����
/// </summary>
class HashTable
{
public:
	virtual void Add(int data) = 0;
	virtual void Remove(int data) = 0;
	virtual bool Contains(int data) = 0;
	virtual void Clear() = 0;

	virtual void PrintHashTable();

protected:
	virtual int GetHashIndex(int data) = 0;
};