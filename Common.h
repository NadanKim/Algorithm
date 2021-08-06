#pragma once
#include <iostream>
#include <fstream>
#include <ctime>

//#define MAKE_RANDOM_NUMBERS

#ifdef MAKE_RANDOM_NUMBERS
#include <random>
#include <limits>
#endif

namespace Common
{
#ifdef MAKE_RANDOM_NUMBERS
	int* GenerateRandomNumber(int n = 100'000);
	void MakeRandomNumbersFile(int n = 100'000);
#endif

#pragma region ���� �����
	int LoadRandomNumbersInFile(int** arr);
#pragma endregion
	
#pragma region �ð� ����
	static std::clock_t startTime;
	static std::clock_t endTime;

	void StartClock();
	void StopClock();
	void PrintElapsedTime();
#pragma endregion
	
	void PrintArray(int arr[], int n);
	void Swap(int arr[], int a, int b);
}