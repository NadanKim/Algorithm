#include "HashTable.h"

#pragma region Public Functions
/// <summary>
/// 해시 테이블의 현 상태를 출력한다.
/// </summary>
void HashTable::PrintHashTable()
{
	std::cout << "--- " << typeid(this).name() << " ---\n";
	std::cout << "- HashFuncion : " << GetHashFunctionString() << "---\n";
}
#pragma endregion

#pragma region Private Functions
/// <summary>
/// 나누기 방법을 이용해 주어진 값의 해쉬 인덱스를 생성해 반환한다.
/// </summary>
/// <param name="data">인덱스를 찾을 데이터</param>
/// <returns>해쉬 테이블에서의 인덱스</returns>
int HashTable::GetHashIndexByDivision(int data)
{
	return data % m_size;
}

/// <summary>
/// 곱하기 방법을 이용해 주어진 값의 해쉬 인덱스를 생성해 반환한다.
/// </summary>
/// <param name="data">인덱스를 찾을 데이터</param>
/// <returns>해쉬 테이블에서의 인덱스</returns>
int HashTable::GetHashIndexByMultiplication(int data)
{
	static double multiplePrimeNumber = (std::sqrt(5) - 1.0) / 2.0;
	return static_cast<int>(std::floor(std::fmod(data * multiplePrimeNumber, 1) * m_size));
}

/// <summary>
/// 현재 해쉬 함수를 string 으로 반환한다.
/// </summary>
/// <returns>해쉬 함수 string</returns>
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
/// 주어진 데이터를 이용하여 해쉬 인덱스를 생성해 반환한다.
/// </summary>
/// <param name="data">인덱스를 찾을 데이터</param>
/// <returns>해쉬 테이블에서의 인덱스</returns>
int HashTable::GetHashIndex(int data)
{
	if (m_hashFunction == HashFunction::Multiplication)
	{
		return GetHashIndexByMultiplication(data);
	}
	return GetHashIndexByDivision(data);
}
#pragma endregion