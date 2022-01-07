#include "HashTable_OpenAddressing_QuadraticProbing.h"

#pragma region Public Functions
/// <summary>
/// 해시 테이블의 현 상태를 출력한다.
/// </summary>
void HashTable_OpenAddressing_QuadraticProbing::PrintHashTable(string hashTableName)
{
	HashTable_OpenAddressing::PrintHashTable(hashTableName);
}
#pragma endregion

#pragma region Protected Functions
/// <summary>
/// 알고리즘에 맞게 충돌을 피한 인덱스를 반환한다.
/// </summary>
/// <param name="idx">충돌한 인덱스</param>
/// <param name="data">추가/검색하려는 데이터</param>
/// <returns>해당 데이터의 인덱스 위치</returns>
int HashTable_OpenAddressing_QuadraticProbing::GetProperHashIndex(int idx, int data)
{
	int properIdx{ idx };
	
	for (int i = 1; m_table[properIdx] != Empty && m_table[properIdx] != data; i++)
	{
		properIdx = (idx + (i * i)) % Size();
	}

	return properIdx;
}
#pragma endregion