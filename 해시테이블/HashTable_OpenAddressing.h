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
	HashTable_OpenAddressing(HashFunction hashFunction = HashFunction::Division);

	virtual void Add(int data) override;
	virtual void Remove(int data) override;
	virtual bool Contains(int data) override;
	virtual void Clear() override;

	virtual void Resize() override;

	virtual void PrintHashTable(string hashTableName = "HashTable_OpenAddressing") override;

private:
	bool IsCollided(int idx);
	bool NeedToResize();

	void ResetTable();

	int LimitCount() { return Size() * 3 / 4; }

protected:
	virtual int GetHashIndex(int data) override;

	virtual int GetProperHashIndex(int idx, int data) = 0;

protected:
	vector<int> m_table;

	int m_usedCount{ 0 };

	static const int Empty{ INT_MAX };
	static const int Deleted{ -INT_MAX };
};