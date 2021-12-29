#include "Common.h"
#include "해시테이블/HashTable_Chaining.h"

int main()
{
	HashTable_Chaining hashTable;

	int arr[] = { 1, 3, 5, 7, 9,
		12, 14, 16, 18, 20,
		23, 25, 27, 29,
		32, 34, 36, 38,
		40, 43, 45, 47, 49 };

	for (int i = 0; i < 23; i++)
	{
		hashTable.Add(arr[i]);
	}

	hashTable.PrintHashTable();

	hashTable.Remove(16);
	hashTable.Remove(27);
	hashTable.Remove(47);

	hashTable.PrintHashTable();
}