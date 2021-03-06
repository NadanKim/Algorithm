#pragma once
#include "../Common.h"
#include <cmath>
#include <string>

using std::string;

/// <summary>
/// 해시 테이블에서 사용할 해시 함수
/// </summary>
enum class HashFunction
{
	Division,
	Multiplication,
};

/// <summary>
/// 해시 테이블의 구성 요소 테스트를 위한 베이스 클래스
/// </summary>
class HashTable
{
public:
	HashTable(HashFunction hashFunction = HashFunction::Division) : m_hashFunction(hashFunction) { m_size = Default_Table_Size; };

	virtual void Add(int data) = 0;
	virtual void Remove(int data) = 0;
	virtual bool Contains(int data) = 0;
	virtual void Clear() = 0;

	virtual void Resize();

	virtual void PrintHashTable(string hashTableName = "HashTable");

private:
	int GetHashIndexByDivision(int data);
	int GetHashIndexByMultiplication(int data);

	string GetHashFunctionString();

protected:
	virtual int GetHashIndex(int data);

	int GetHashIndex(int data, HashFunction hashFunction);

	int Size() { return m_size; }
	HashFunction CurrentHashFunction() { return m_hashFunction; }

private:
	HashFunction m_hashFunction;
	int m_size;

	static const int Default_Table_Size{ 17 };
};