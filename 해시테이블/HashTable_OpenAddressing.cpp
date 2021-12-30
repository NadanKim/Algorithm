#include "HashTable_OpenAddressing.h"

#pragma region Public Functions
/// <summary>
/// 데이터를 해시 테이블에 추가한다.
/// </summary>
/// <param name="data">추가할 데이터</param>
void HashTable_OpenAddressing::Add(int data)
{
	if (Contains(data))
	{
		return;
	}

	int idx{ GetHashIndex(data) };
	m_table[idx] = data;
}

/// <summary>
/// 데이터를 해시 테이블에서 제거한다.
/// </summary>
/// <param name="data">제거할 데이터</param>
void HashTable_OpenAddressing::Remove(int data)
{
	if (!Contains(data))
	{
		return;
	}

	int idx{ GetHashIndex(data) };
	m_table[idx] = Deleted_Data;
}

/// <summary>
/// 주어진 값이 해시 테이블에 존재하는지 여부를 반환한다.
/// </summary>
/// <param name="data">찾을 데이터</param>
/// <returns>존재 여부</returns>
bool HashTable_OpenAddressing::Contains(int data)
{
	int idx{ GetHashIndex(data) };

	return m_table[idx] == data || m_table[idx] == Deleted_Data;
}

/// <summary>
/// 해시 테이블의 모든 데이터를 지운다.
/// </summary>
void HashTable_OpenAddressing::Clear()
{
	m_table.clear();
}

/// <summary>
/// 해시 테이블의 현 상태를 출력한다.
/// </summary>
void HashTable_OpenAddressing::PrintHashTable()
{
	HashTable::PrintHashTable();

	for (int i = 0, total = Size(); i < total; i++)
	{
		std::cout << " Index " << i << " : ";
		if (m_table.size() > 0)
		{
			auto d = m_table.cbegin();
			while (true)
			{
				if (*d == Deleted_Data)
				{
					std::cout << "Deleted";
				}
				else
				{
					std::cout << *d;
				}
				d++;

				if (d == m_table.cend())
				{
					break;
				}

				std::cout << " - ";
			}
		}
		else
		{
			std::cout << "EMPTY";
		}
		std::cout << '\n';
	}
	std::cout << '\n';
}
#pragma endregion

#pragma region Protected Functions
/// <summary>
/// 개방 주소 방법을 통해 적절한 인덱스를 반환한다.
/// </summary>
/// <param name="data">인덱스를 찾을 데이터</param>
/// <returns>해쉬 테이블에서의 인덱스</returns>
int HashTable_OpenAddressing::GetHashIndex(int data)
{
	int idx{ HashTable::GetHashIndex(data) };

	if (Contains(data))
	{
		idx = GetProperHashIndex(idx, data);
	}

	return idx;
}
#pragma endregion
