#include <algorithm>
#include <chrono>
#include <iostream>
#include <numeric>
#include <future>
#include <vector>

#include "Profiling.h"

std::vector<int> generateVectorWithNumber()
{
	const auto getNumberFrom1to10000 = []()
	{
		static int i;

		return i % 10000;
	};

	std::vector<int> numbersFrom1To10000(10000);
	std::generate(numbersFrom1To10000.begin(), numbersFrom1To10000.end(), getNumberFrom1to10000);

	return numbersFrom1To10000;
}

void sumNumbersInVector(const std::vector<int>& numbers)
{
	PROFILE_FUNCSIG();
	const auto plus = [](const int sum, const int number)
	{
		return sum + number;
	};
	// Little more delay because sum is just too fast.
	std::this_thread::sleep_for(std::chrono::seconds(1));
	std::accumulate(numbers.begin(), numbers.end(), 0, plus);
}

int test()
{
	const std::vector<int> numbers = generateVectorWithNumber();

	Profiling::beginSession("./profilingResults/singleprofile.json");
	sumNumbersInVector(numbers);
	Profiling::endSession();

	Profiling::beginSession("./profilingResults/multipleprofilefromthreads.json");
	std::thread t1 = std::thread(sumNumbersInVector, numbers);
	std::thread t2 = std::thread(sumNumbersInVector, numbers);
	std::thread t3 = std::thread(sumNumbersInVector, numbers);
	std::thread t4 = std::thread(sumNumbersInVector, numbers);
	t1.join();
	t2.join();
	t3.join();
	t4.join();
	Profiling::beginSession("./profilingResults/singleprofile2.json");
	sumNumbersInVector(numbers);
	Profiling::endSession();

	return 0;
}