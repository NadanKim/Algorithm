#include "Common.h"
#include "해시테이블/HashTable_OpenAddressing_LinearProbing.h"

int main()
{
	HashTable_OpenAddressing_LinearProbing hashTable;

	int arr[] = { 1, 3, 5, 7, 9,
		12, 14, 16, 18, 20,
		23, 25, 27, 29,
		32, 34, 36, 38,
		40, 43, 45, 47, 49,
	    11, 21, 31, 41 ,51,
	    61, 71, 81, 91, 2 
	};

	for (int i = 0; i < 33; i++)
	{
		hashTable.Add(arr[i]);
	}

	hashTable.PrintHashTable();

	hashTable.Remove(16);
	hashTable.Remove(27);
	hashTable.Remove(47);

	hashTable.PrintHashTable();
}