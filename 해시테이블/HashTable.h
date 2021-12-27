#pragma once
#include "../Common.h"

/// <summary>
/// 해시 테이블의 구성 요소 테스트를 위한 베이스 클래스
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