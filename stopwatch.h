#pragma once

#include <chrono>
#include <string>
#include <cstdio>

class StopWatch
{
public:
	StopWatch(const std::string& name) : mName{name} { Restart(); }

	void Restart()
	{
		mStart = std::chrono::system_clock::now();
	}

	uint64_t GetElapsedMilliseconds() { return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - mStart).count(); }

	void LogElapsed()
	{
		const auto ms = GetElapsedMilliseconds();
		if (ms < 1000)
		{
			printf("%s finished, time elapsed: %llu milliseconds.\n", mName.c_str(), ms);
		}
		else if (ms < (60ull * 1000))
		{
			printf("%s finished, time elapsed: %llu.%03llu seconds\n", mName.c_str(), ms / 1000, ms % 1000);
		}
		else
		{
			const auto seconds = ms / 1000;
			const auto minutes = seconds / 60;
			const auto rest_seconds = seconds - minutes * 60;
			printf("%s finished, time elapsed: %llu minutes and %llu seconds\n", mName.c_str(), minutes, rest_seconds);
		}
	}

private:
	std::string mName;
	std::chrono::system_clock::time_point mStart;
};
