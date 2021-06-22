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
	/// <summary>
	/// 난수 배열을 생성하여 반환한다.
	/// </summary>
	/// <param name="n">생성할 난수의 개수</param>
	/// <returns>생성된 난수 배열</returns>
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

	/// <summary>
	/// 난수를 생성하여 파일에 저장한다.
	/// </summary>
	/// <param name="n">생성할 난수의 개수</param>
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
	/// <summary>
	/// 파일에 있는 난수를 불러와 입력된 포인터에 저장한다.
	/// </summary>
	/// <param name="arr">불러온 난수 배열을 반환할 포인터</param>
	/// <returns>불러온 난수의 개수</returns>
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

	/// <summary>
	/// 시간 측정을 시작한다.
	/// </summary>
	void StartClock()
	{
		startTime = std::clock();
	}

	/// <summary>
	/// 시간 측정을 종료한다.
	/// </summary>
	void StopClock()
	{
		endTime = std::clock();
	}

	/// <summary>
	/// 측정한 시간을 계산하여 출력한다.
	/// </summary>
	void PrintElapsedTime()
	{
		std::clock_t elapsed = endTime - startTime;

		double timeSecond = static_cast<double>(elapsed / CLOCKS_PER_SEC);

		std::cout << "total time is " << timeSecond << "s ( " << elapsed << "ms )\n";
	}
#pragma endregion
	/// <summary>
	/// 입력된 배열을 출력한다.
	/// </summary>
	/// <param name="arr">출력할 배열</param>
	/// <param name="n">배열의 길이</param>
	void PrintArray(int arr[], int n)
	{
		for (int i = 0; i < n; i++)
		{
			std::cout << arr[i] << ' ';
		}
		std::cout << '\n';
	}

	/// <summary>
	/// 주어진 인덱스의 값을 서로 바꾼다.
	/// </summary>
	/// <param name="arr">값이 들어있는 배열</param>
	/// <param name="a">첫 번째 인덱스</param>
	/// <param name="b">두 번째 인덱스</param>
	void Swap(int arr[], int a, int b)
	{
		int temp{ arr[a] };
		arr[a] = arr[b];
		arr[b] = temp;
	}
}