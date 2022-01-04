#include "HashTable_OpenAddressing_LinearProbing.h"

#pragma region Public Functions
/// <summary>
/// �ؽ� ���̺��� �� ���¸� ����Ѵ�.
/// </summary>
void HashTable_OpenAddressing_LinearProbing::PrintHashTable(string hashTableName)
{
	HashTable_OpenAddressing::PrintHashTable(hashTableName);
}
#pragma endregion

#pragma region Protected Functions
/// <summary>
/// �˰��� �°� �浹�� ���� �ε����� ��ȯ�Ѵ�.
/// </summary>
/// <param name="idx">�浹�� �ε���</param>
/// <param name="data">�߰�/�˻��Ϸ��� ������</param>
/// <returns>�ش� �������� �ε��� ��ġ</returns>
int HashTable_OpenAddressing_LinearProbing::GetProperHashIndex(int idx, int data)
{
	int properIdx{ -1 };
	// �浹�� �� ��ġ�������� �� ������ �˻��Ѵ�.
	for (int i = idx; i < Size(); i++)
	{
		if (m_table[i] == Empty || m_table[i] == data)
		{
			properIdx = i;
			break;
		}
	}

	// ������ ���µ� �� ������ ������ �� ���������� Ž���Ѵ�.
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
