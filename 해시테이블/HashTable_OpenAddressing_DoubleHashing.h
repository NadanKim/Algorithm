#pragma once
#include "../Common.h"
#include "HashTable_OpenAddressing.h"
#include <vector>
#include <list>

using std::vector;
using std::list;

/// <summary>
/// �浹 �ذ� ��� �� ü�̴��� ������ �ؽ� ���̺�
/// </summary>
class HashTable_OpenAddressing_DoubleHashing : public HashTable_OpenAddressing
{
public:
	HashTable_OpenAddressing_DoubleHashing(HashFunction hashFunction = HashFunction::Division) : HashTable_OpenAddressing(hashFunction) {};

	virtual void PrintHashTable(string hashTableName = "HashTable_OpenAddressing_DoubleHashing") override;

protected:
	virtual int GetProperHashIndex(int idx, int data) override;
};