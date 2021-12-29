#pragma once
#include "../Common.h"
#include <cmath>
#include <string>

/// <summary>
/// �ؽ� ���̺��� ����� �ؽ� �Լ�
/// </summary>
enum class HashFunction
{
	Division,
	Multiplication,
};

/// <summary>
/// �ؽ� ���̺��� ���� ��� �׽�Ʈ�� ���� ���̽� Ŭ����
/// </summary>
class HashTable
{
public:
	HashTable(HashFunction hashFunction = HashFunction::Division) : m_hashFunction(hashFunction) { m_size = Default_Table_Size; };

	virtual void Add(int data) = 0;
	virtual void Remove(int data) = 0;
	virtual bool Contains(int data) = 0;
	virtual void Clear() = 0;

	virtual void PrintHashTable();

private:
	int GetHashIndexByDivision(int data);
	int GetHashIndexByMultiplication(int data);

	std::string GetHashFunctionString();

protected:
	int GetHashIndex(int data);

	int Size() { return m_size; }

private:
	HashFunction m_hashFunction;
	int m_size;

	static const int Default_Table_Size{ 17 };
};
