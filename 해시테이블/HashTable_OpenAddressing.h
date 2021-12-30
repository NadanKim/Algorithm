#pragma once
#include "../Common.h"
#include "HashTable.h"
#include <vector>
#include <list>

using std::vector;
using std::list;

/// <summary>
/// 충돌 해결 방법 중 체이닝을 구현한 해시 테이블
/// </summary>
class HashTable_OpenAddressing : public HashTable
{
public:
	HashTable_OpenAddressing(HashFunction hashFunction = HashFunction::Division) : HashTable(hashFunction) {}

	virtual void Add(int data) override;
	virtual void Remove(int data) override;
	virtual bool Contains(int data) override;
	virtual void Clear() override;

	virtual void PrintHashTable() override;

protected:
	virtual int GetHashIndex(int data);

	virtual int GetProperHashIndex(int idx, int data) = 0;

private:
	vector<int> m_table;

	static const int Deleted_Data = -INT_MAX;
};