#include "HashTable_OpenAddressing_LinearProbing.h"

#pragma region Public Functions
/// <summary>
/// 해시 테이블의 현 상태를 출력한다.
/// </summary>
void HashTable_OpenAddressing_LinearProbing::PrintHashTable(string hashTableName)
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
int HashTable_OpenAddressing_LinearProbing::GetProperHashIndex(int idx, int data)
{
	int properIdx{ -1 };
	// 충돌이 난 위치에서부터 빈 공간을 검색한다.
	for (int i = idx; i < Size(); i++)
	{
		if (m_table[i] == Empty || m_table[i] == data)
		{
			properIdx = i;
			break;
		}
	}

	// 끝까지 갔는데 빈 공간이 없으면 맨 위에서부터 탐색한다.
	if (properIdx == -1)
	{
		for (int i = 0; i < idx; i++)
		{
			if (m_table[i] == Empty || m_table[i] == data)
			{
				properIdx = i;
				break;
			}
		}
	}

	return properIdx;
}
#pragma endregion
