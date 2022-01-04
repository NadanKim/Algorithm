#include "HashTable_OpenAddressing.h"

#pragma region Public Functions
/// <summary>
/// �ؽ� �Լ��� �����ϰ� �ؽ� ���̺��� �ʱ�ȭ�Ѵ�.
/// </summary>
/// <param name="hashFunction">����� �ؽ� �Լ�</param>
HashTable_OpenAddressing::HashTable_OpenAddressing(HashFunction hashFunction)
	: HashTable(hashFunction)
{
	ResetTable();
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

	m_usedCount++;

	if (NeedToResize())
	{
		Resize();
	}
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
	m_table[idx] = Deleted;
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
/// �ؽ� ���̺��� ũ�⸦ �����ϰ� �����͸� �ٽ� �ؽ��Ѵ�.
/// </summary>
void HashTable_OpenAddressing::Resize()
{
	vector<int> oldData;
	oldData.reserve(Size());

	for (int i = 0; i < Size(); i++)
	{
		if (m_table[i] != Empty && m_table[i] != Deleted)
		{
			oldData.emplace_back(m_table[i]);
		}
	}

	HashTable::Resize();
	ResetTable();

	int oldDataCount = static_cast<int>(oldData.size());
	for (int i = 0; i < oldDataCount; i++)
	{
		Add(oldData[i]);
	}

	m_usedCount = oldDataCount;
}

/// <summary>
/// �ؽ� ���̺��� �� ���¸� ����Ѵ�.
/// </summary>
void HashTable_OpenAddressing::PrintHashTable(string hashTableName)
{
	HashTable::PrintHashTable(hashTableName);

	for (int i = 0, total = Size(); i < total; i++)
	{
		std::cout << " Index " << i << " : ";
		if (m_table[i] == Deleted)
		{
			std::cout << "Deleted";
		}
		else if (m_table[i] == Empty)
		{
			std::cout << "Empty";
		}
		else
		{
			std::cout << m_table[i];
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

/// <summary>
/// ������� �ʿ����� ���θ� ��ȯ�Ѵ�.
/// </summary>
/// <returns>�������� �ʿ� ����</returns>
bool HashTable_OpenAddressing::NeedToResize()
{
	return m_usedCount > LimitCount();
}

/// <summary>
/// ���̺��� �ʱ�ȭ�Ѵ�.
/// </summary>
void HashTable_OpenAddressing::ResetTable()
{
	m_table.clear();
	for (int i = 0, total = Size(); i < total; i++)
	{
		m_table.push_back(Empty);
	}

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

	if (IsCollided(idx))
	{
		idx = GetProperHashIndex(idx, data);
	}

	return idx;
}
#pragma endregion
