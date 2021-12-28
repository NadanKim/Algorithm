#include "HashTable.h"

#pragma region Public Functions
/// <summary>
/// �ؽ� ���̺��� �� ���¸� ����Ѵ�.
/// </summary>
void HashTable::PrintHashTable()
{
	std::cout << "--- " << typeid(this).name() << " ---\n";
	std::cout << "- HashFuncion : " << GetHashFunctionString() << "---\n";
}
#pragma endregion

#pragma region Private Functions
/// <summary>
/// ������ ����� �̿��� �־��� ���� �ؽ� �ε����� ������ ��ȯ�Ѵ�.
/// </summary>
/// <param name="data">�ε����� ã�� ������</param>
/// <returns>�ؽ� ���̺����� �ε���</returns>
int HashTable::GetHashIndexByDivision(int data)
{
	return data % m_size;
}

/// <summary>
/// ���ϱ� ����� �̿��� �־��� ���� �ؽ� �ε����� ������ ��ȯ�Ѵ�.
/// </summary>
/// <param name="data">�ε����� ã�� ������</param>
/// <returns>�ؽ� ���̺����� �ε���</returns>
int HashTable::GetHashIndexByMultiplication(int data)
{
	static double multiplePrimeNumber = (std::sqrt(5) - 1.0) / 2.0;
	return static_cast<int>(std::floor(std::fmod(data * multiplePrimeNumber, 1) * m_size));
}

/// <summary>
/// ���� �ؽ� �Լ��� string ���� ��ȯ�Ѵ�.
/// </summary>
/// <returns>�ؽ� �Լ� string</returns>
std::string HashTable::GetHashFunctionString()
{
	if (m_hashFunction == HashFunction::Multiplication)
	{
		return "Multiplication";
	}
	return "Division";
}
#pragma endregion

#pragma region Protected Functions
/// <summary>
/// �־��� �����͸� �̿��Ͽ� �ؽ� �ε����� ������ ��ȯ�Ѵ�.
/// </summary>
/// <param name="data">�ε����� ã�� ������</param>
/// <returns>�ؽ� ���̺����� �ε���</returns>
int HashTable::GetHashIndex(int data)
{
	if (m_hashFunction == HashFunction::Multiplication)
	{
		return GetHashIndexByMultiplication(data);
	}
	return GetHashIndexByDivision(data);
}
#pragma endregion