#include "HashTable_Chaining.h"

#pragma region Public Functions
/// <summary>
/// �ؽ� �Լ��� �����ϰ� �ؽ� ���̺��� �ʱ�ȭ�Ѵ�.
/// </summary>
/// <param name="hashFunction">����� �ؽ� �Լ�</param>
HashTable_Chaining::HashTable_Chaining(HashFunction hashFunction)
	: HashTable(hashFunction)
{
	for (int i = 0, total = Size(); i < total; i++)
	{
		m_table.push_back(list<int>());
	}
}

/// <summary>
/// �����͸� �ؽ� ���̺� �߰��Ѵ�.
/// </summary>
/// <param name="data">�߰��� ������</param>
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
/// �����͸� �ؽ� ���̺��� �����Ѵ�.
/// </summary>
/// <param name="data">������ ������</param>
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
/// �־��� ���� �ؽ� ���̺� �����ϴ��� ���θ� ��ȯ�Ѵ�.
/// </summary>
/// <param name="data">ã�� ������</param>
/// <returns>���� ����</returns>
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
/// �ؽ� ���̺��� ��� �����͸� �����.
/// </summary>
void HashTable_Chaining::Clear()
{
	for (int i = 0, total = Size(); i < total; i++)
	{
		m_table[i].clear();
	}
}

/// <summary>
/// �ؽ� ���̺��� �� ���¸� ����Ѵ�.
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