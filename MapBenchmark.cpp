#include "stopwatch.h"

#include <string>
#include <map>
#include <unordered_map>
#include <random>

static constexpr int64_t numItems = 50000000;
static constexpr int64_t numRandomSamples = 50000000;

static std::random_device random_device;
static std::mt19937 random_engine(random_device());
static std::uniform_int_distribution<int64_t> random_distribution(0, numItems - 1);

template<typename T>
void fillElements(T& m, std::string name)
{
	StopWatch stopWatch(name + " fill");
	for (int64_t item = 0; item < numItems; item++)
	{
		m[item] = item;
	}
	stopWatch.LogElapsed();
}

template<typename T>
int64_t iterateElements(T& m, std::string name)
{
	StopWatch stopWatch(name + " iteration");
	int64_t checksum = 0;
	for (const auto& [key, value] : m)
	{
		checksum += value + key;
	}
	stopWatch.LogElapsed();
	return checksum;
}

template<typename T>
int64_t randomAccess(T& m, std::string name)
{
	StopWatch stopWatch(name + " random access of " + std::to_string(numRandomSamples) + " elements");
	random_engine.seed(324873);
	int64_t checksum = 0;
	for (int64_t sample = 0; sample < numRandomSamples; sample++)
	{
		const int64_t key = random_distribution(random_engine);
		checksum += m[key] + key;
	}
	stopWatch.LogElapsed();
	return checksum;
}

template<typename T>
void runTests(T& m, std::string name)
{
	printf("\n%s map test with %llu items\n", name.c_str(), numItems);
	int64_t checksum = 0;

	for (int i = 0; i < 2; i++)
	{
		fillElements(m, name);
		m.clear();
	}
	fillElements(m, name);

	checksum += iterateElements(m, name);
	checksum += iterateElements(m, name);
	checksum += randomAccess(m, name);
	checksum += randomAccess(m, name);

	printf("Test checksum: %#llx\n", checksum);
}

int main()
{
	{
		std::map<int64_t, int64_t> testMapOrdered;
		runTests(testMapOrdered, "Ordered");
	}
	{
		std::unordered_map<int64_t, int64_t> testMapUnordered;
		runTests(testMapUnordered, "Unordered");
	}
}
