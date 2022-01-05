#pragma once
#include "../Common.h"
#include "HashTable_OpenAddressing.h"
#include <vector>
#include <list>

using std::vector;
using std::list;

/// <summary>
/// 충돌 해결 방법 중 체이닝을 구현한 해시 테이블
/// </summary>
class HashTable_OpenAddressing_QuadraticProbing : public HashTable_OpenAddressing
{
public:
	HashTable_OpenAddressing_QuadraticProbing(HashFunction hashFunction = HashFunction::Division) : HashTable_OpenAddressing(hashFunction) {};

	virtual void PrintHashTable(string hashTableName = "HashTable_OpenAddressing_QuadraticProbing") override;

protected:
	virtual int GetProperHashIndex(int idx, int data) override;
};