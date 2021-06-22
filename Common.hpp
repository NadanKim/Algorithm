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
	int* GenerateRandomNumber(int n = 100'000)
	{
		std::default_random_engine randomEngine;
		std::uniform_int_distribution<int> distribution(0, INT_MAX);

		int* arr = new int[n];
		for (int i = 0; i < n; ++i)
		{
			arr[i] = distribution(randomEngine);
		}

		return arr;
	}

	void MakeRandomNumbersFile(int n = 100'000)
	{
		int* arr = GenerateRandomNumber(n);

		std::ofstream ofs("./Randoms.txt");

		ofs << n << "; ";
		for (int i = 0; i < n; ++i)
		{
			ofs << arr[i] << "; ";
		}

		ofs.close();
	}
#endif

#pragma region 파일 입출력
	int LoadRandomNumbersInFile(int** arr)
	{
		std::ifstream ifs("./Randoms.txt");

		int n;
		ifs >> n;

		*(arr) = new int[n];
		for (int i = 0; i < n; ++i)
		{
			ifs >> (*arr)[i];
		}

		ifs.close();

		return n;
	}
#pragma endregion
	
#pragma region 시간 측정
	std::clock_t startTime;
	std::clock_t endTime;

	void StartClock()
	{
		startTime = std::clock();
	}

	void StopClock()
	{
		endTime = std::clock();
	}

	void PrintElapsedTime()
	{
		std::clock_t elapsed = endTime - startTime;

		double timeSecond = static_cast<double>(elapsed / CLOCKS_PER_SEC);

		std::cout << "total time is " << timeSecond << "s ( " << elapsed << "ms )\n";
	}
#pragma endregion


	void PrintArray(int arr[], int n)
	{
		for (int i = 0; i < n; i++)
		{
			std::cout << arr[i] << ' ';
		}
		std::cout << '\n';
	}

	void Swap(int arr[], int a, int b)
	{
		int temp{ arr[a] };
		arr[a] = arr[b];
		arr[b] = temp;
	}
}