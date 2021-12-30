#include "HashTable_OpenAddressing.h"

#pragma region Public Functions
/// <summary>
/// �ؽ� �Լ��� �����ϰ� �ؽ� ���̺��� �ʱ�ȭ�Ѵ�.
/// </summary>
/// <param name="hashFunction">����� �ؽ� �Լ�</param>
HashTable_OpenAddressing::HashTable_OpenAddressing(HashFunction hashFunction)
	: HashTable(hashFunction)
{
	for (int i = 0, total = Size(); i < total; i++)
	{
		m_table.push_back(Empty);
	}
}

/// <summary>
/// �����͸� �ؽ� ���̺� �߰��Ѵ�.
/// </summary>
/// <param name="data">�߰��� ������</param>
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
/// �����͸� �ؽ� ���̺��� �����Ѵ�.
/// </summary>
/// <param name="data">������ ������</param>
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
/// �־��� ���� �ؽ� ���̺� �����ϴ��� ���θ� ��ȯ�Ѵ�.
/// </summary>
/// <param name="data">ã�� ������</param>
/// <returns>���� ����</returns>
bool HashTable_OpenAddressing::Contains(int data)
{
	int idx{ GetHashIndex(data) };

	return m_table[idx] == data;
}

/// <summary>
/// �ؽ� ���̺��� ��� �����͸� �����.
/// </summary>
void HashTable_OpenAddressing::Clear()
{
	m_table.clear();
}

/// <summary>
/// �ؽ� ���̺��� �� ���¸� ����Ѵ�.
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

#pragma region Private Functions
/// <summary>
/// �־��� �ε����� ���� �����Ͽ� �浹�� �߻��ϴ��� ���θ� ��ȯ�Ѵ�.
/// </summary>
/// <param name="idx">Ȯ���� �ε���</param>
/// <returns>�浹 ����</returns>
bool HashTable_OpenAddressing::IsCollided(int idx)
{
	return m_table[idx] != Empty;
}
#pragma endregion


#pragma region Protected Functions
/// <summary>
/// ���� �ּ� ����� ���� ������ �ε����� ��ȯ�Ѵ�.
/// </summary>
/// <param name="data">�ε����� ã�� ������</param>
/// <returns>�ؽ� ���̺����� �ε���</returns>
int HashTable_OpenAddressing::GetHashIndex(int data)
{
	int idx{ HashTable::GetHashIndex(data) };

	if (IsCollided(data))
	{
		idx = GetProperHashIndex(idx, data);
	}

	return idx;
}
#pragma endregion
