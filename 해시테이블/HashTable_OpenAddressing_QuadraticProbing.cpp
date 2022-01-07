#include "HashTable_OpenAddressing_QuadraticProbing.h"

#pragma region Public Functions
/// <summary>
/// �ؽ� ���̺��� �� ���¸� ����Ѵ�.
/// </summary>
void HashTable_OpenAddressing_QuadraticProbing::PrintHashTable(string hashTableName)
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