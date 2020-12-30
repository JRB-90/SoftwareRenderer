#include "Profiler.h"

#include <iostream>
#include <ios>

using namespace softengine;

Profiler::Profiler()
{
	startTime = std::chrono::high_resolution_clock::now();
}

void Profiler::ResetTimer()
{
	startTime = std::chrono::high_resolution_clock::now();
}

void Profiler::ResetProfileRun()
{
	timings.clear();
	ResetTimer();
}

void Profiler::AddTiming(const std::string& name)
{
	auto endTime = std::chrono::high_resolution_clock::now();
	auto duration =
		std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime)
		.count();
	auto search = timings.find(name);
	if (search == timings.end())
	{
		std::vector<double> vals;
		vals.push_back((double)duration / 1000.0);
		timings.insert({ name, vals });
	}
	else
	{
		search->second.push_back((double)duration / 1000.0);
	}
	ResetTimer();
}

void Profiler::PrintTimings()
{
	std::printf("\n");
	for (std::pair<const std::string, std::vector<double>>& pair : timings)
	{
		double sum = 0;
		double min = 9999999999;
		double max = 0;
		for (double val : pair.second)
		{
			sum += val;
			if (val < min)
			{
				min = val;
			}
			if (val > max)
			{
				max = val;
			}
		}
		std::printf(
			"%s\t\t\t%i\t\t%.3f\t\t%.3f\t\t%.3f\n", 
			pair.first.c_str(),
			pair.second.size(),
			sum / (double)pair.second.size(),
			min,
			max
		);
	}
}
