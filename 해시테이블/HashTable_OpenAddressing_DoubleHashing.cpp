#include "HashTable_OpenAddressing_DoubleHashing.h"

#pragma region Public Functions
/// <summary>
/// �ؽ� ���̺��� �� ���¸� ����Ѵ�.
/// </summary>
void HashTable_OpenAddressing_DoubleHashing::PrintHashTable(string hashTableName)
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
int HashTable_OpenAddressing_DoubleHashing::GetProperHashIndex(int idx, int data)
{
	int jumpValue{ HashTable::GetHashIndex(data, HashFunction::Multiplication) };
	if (CurrentHashFunction() == HashFunction::Multiplication)
	{
		jumpValue = HashTable::GetHashIndex(data, HashFunction::Division);
	}

	int properIdx{ idx };

	for (int i = 1; m_table[properIdx] != Empty && m_table[properIdx] != data; i++)
	{
		properIdx = (idx + (i * jumpValue)) % Size();
	}
	
	return properIdx;
}
#pragma endregion