#pragma once

#include <vector>
#include <map>
#include <string>
#include <chrono>

namespace softengine
{
	class Profiler
	{
	public:
		Profiler();
		void ResetTimer();
		void ResetProfileRun();
		void AddTiming(const std::string& name);
		void PrintTimings();

	private:
		std::map<std::string, std::vector<double>> timings;
		std::chrono::steady_clock::time_point startTime;
	};
}