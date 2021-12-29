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
class HashTable_Chaining : public HashTable
{
public:
	HashTable_Chaining(HashFunction hashFunction = HashFunction::Division);

	virtual void Add(int data) override;
	virtual void Remove(int data) override;
	virtual bool Contains(int data) override;
	virtual void Clear() override;

	virtual void PrintHashTable() override;

private:
	vector<list<int>> m_table;
};