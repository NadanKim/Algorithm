#include "HashTable_Chaining.h"

#pragma region Public Functions
/// <summary>
/// 해시 함수를 결정하고 해시 테이블을 초기화한다.
/// </summary>
/// <param name="hashFunction">사용할 해시 함수</param>
HashTable_Chaining::HashTable_Chaining(HashFunction hashFunction)
	: HashTable(hashFunction)
{
	for (int i = 0, total = Size(); i < total; i++)
	{
		m_table.push_back(list<int>());
	}
}

/// <summary>
/// 데이터를 해시 테이블에 추가한다.
/// </summary>
/// <param name="data">추가할 데이터</param>
void HashTable_Chaining::Add(int data)
{
	if (Contains(data))
	{
		return;
	}

	int idx{ GetHashIndex(data) };
	m_table[idx].push_back(data);
}

/// <summary>
/// 데이터를 해시 테이블에서 제거한다.
/// </summary>
/// <param name="data">제거할 데이터</param>
void HashTable_Chaining::Remove(int data)
{
	if (!Contains(data))
	{
		return;
	}

	int idx{ GetHashIndex(data) };
	m_table[idx].remove(data);
}

/// <summary>
/// 주어진 값이 해시 테이블에 존재하는지 여부를 반환한다.
/// </summary>
/// <param name="data">찾을 데이터</param>
/// <returns>존재 여부</returns>
bool HashTable_Chaining::Contains(int data)
{
	int idx{ GetHashIndex(data) };
	for (auto d = m_table[idx].cbegin(); d != m_table[idx].cend(); d++)
	{
		if (*d == data)
		{
			return true;
		}
	}
	return false;
}

/// <summary>
/// 해시 테이블의 모든 데이터를 지운다.
/// </summary>
void HashTable_Chaining::Clear()
{
	for (int i = 0, total = Size(); i < total; i++)
	{
		m_table[i].clear();
	}
}

/// <summary>
/// 해시 테이블의 현 상태를 출력한다.
/// </summary>
void HashTable_Chaining::PrintHashTable(string hashTableName)
{
	HashTable::PrintHashTable(hashTableName);

	for (int i = 0, total = Size(); i < total; i++)
	{
		std::cout << " Index " << i << " : ";
		if (m_table[i].size() > 0)
		{
			auto d = m_table[i].cbegin();
			while (true)
			{
				std::cout << *d;
				d++;

				if (d == m_table[i].cend())
				{
					break;
				}

				std::cout << " - ";
			}
		}
		else
		{
			std::cout << "Empty";
		}
		std::cout << '\n';
	}
	std::cout << '\n';
}
#pragma endregion