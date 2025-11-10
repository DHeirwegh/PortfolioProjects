// Json_Optimized.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include "Timer.h"
#include "json/json.h"

int main()
{
	std::cout << "=== JsonCpp Performance Testing ===\n\n";

	// Test 2: Parse JSON with JsonCpp - Run 10 times for benchmarking
	std::cout << "Test: Parsing JSON with JsonCpp (10 runs)...\n";
	
	const int NUM_RUNS = 5;
	std::vector<double> durations;
	durations.reserve(NUM_RUNS);
	
	Json::Value root;
	
	for (int run = 0; run < NUM_RUNS; ++run)
	{
		// Open file for each run
		std::ifstream file("random_data.json", std::ifstream::binary);
		if (!file.is_open())
		{
			std::cerr << "Error: Could not open random_data.json\n";
			return 1;
		}
		
		Timer timer;
		timer.Start();
		
		Json::CharReaderBuilder builder;
		std::string errs;

		if (!Json::parseFromStream(builder, file, &root, &errs))
		{
			std::cerr << "Error parsing JSON: " << errs << "\n";
			return 1;
		}

		timer.Stop();
		double elapsed = timer.ElapsedMilliseconds();
		durations.push_back(elapsed);
		
		std::cout << "  Run " << (run + 1) << ": " << (elapsed / 1000.0) << "s\n";
		
		file.close();
	}
	
	// Sort durations to find min, max, and calculate average of middle 8
	std::vector<double> sortedDurations = durations;
	std::sort(sortedDurations.begin(), sortedDurations.end());
	
	double minDuration = sortedDurations.front();
	double maxDuration = sortedDurations.back();
	
	// Calculate average of middle 8 (exclude min and max)
	double sum = 0.0;
	for (size_t i = 1; i < sortedDurations.size() - 1; ++i)
	{
		sum += sortedDurations[i];
	}
	double avgMiddle8 = sum / NUM_RUNS;
	
	std::cout << "\n=== Benchmark Results ===\n";
	std::cout << "Number of elements: " << root.size() << "\n";
	std::cout << "Min time:  " << (minDuration / 1000.0) << "s\n";
	std::cout << "Max time:  " << (maxDuration / 1000.0) << "s\n";
	std::cout << "Avg (middle " + std::to_string(NUM_RUNS) + "): " << (avgMiddle8 / 1000.0) << "s\n";

	// Write results to file
	std::ofstream outFile("benchmark_results.txt", std::ios::app);
	if (outFile.is_open())
	{
		// Get current date/time for the timestamp
		auto now = std::chrono::system_clock::now();
		auto time = std::chrono::system_clock::to_time_t(now);
		char timeStr[100];
		tm timeInfo;
		localtime_s(&timeInfo, &time);
		std::strftime(timeStr, sizeof(timeStr), "%Y-%m-%d %H:%M:%S", &timeInfo);
		
		outFile << "\n=== JsonCpp Benchmark Results ===\n";
		outFile << "Date/Time: " << timeStr << "\n";
		outFile << "Total Runs: " << NUM_RUNS << "\n";
		outFile << "Number of elements: " << root.size() << "\n\n";
		
		outFile << "Statistics:\n";
		outFile << "Min time: " << (minDuration / 1000.0) << "s\n";
		outFile << "Max time: " << (maxDuration / 1000.0) << "s\n";
		outFile << "Avg (middle 8): " << (avgMiddle8 / 1000.0) << "s\n";
		outFile << "----------------------------------------\n";
		
		outFile.close();
		std::cout << "\nResults appended to benchmark_results.txt\n";
	}
	else
	{
		std::cerr << "Warning: Could not write to benchmark_results.txt\n";
	}

	//// Test 3: Iterate through JSON array
	//std::cout << "\nTest 3: Iterating through all elements...\n";
	//{
	//	Timer timer;
	//	int count = 0;
	//	for (const auto& item : root)
	//	{
	//		count++;
	//	}
	//	timer.Stop();
	//	std::cout << "Iterated " << count << " elements\n";
	//	timer.Print();
	//}

	//// Test 4: Access and filter data
	//std::cout << "\nTest 4: Filtering active items...\n";
	//{
	//	Timer timer;
	//	std::vector<Json::Value> activeItems;
	//	for (const auto& item : root)
	//	{
	//		if (item["active"].asBool())
	//		{
	//			activeItems.push_back(item);
	//		}
	//	}
	//	timer.Stop();
	//	std::cout << "Found " << activeItems.size() << " active items\n";
	//	timer.Print();
	//}

	//// Test 5: Calculate average value
	//std::cout << "\nTest 5: Calculating average value...\n";
	//{
	//	Timer timer;
	//	double sum = 0.0;
	//	int count = 0;
	//	for (const auto& item : root)
	//	{
	//		sum += item["value"].asDouble();
	//		count++;
	//	}
	//	double average = sum / count;
	//	timer.Stop();
	//	std::cout << "Average value: " << average << "\n";
	//	timer.Print();
	//}

	//// Test 6: Serialize back to string
	//std::cout << "\nTest 6: Serializing to JSON string...\n";
	//{
	//	Timer timer;
	//	Json::StreamWriterBuilder builder;
	//	builder["indentation"] = "";
	//	std::string output = Json::writeString(builder, root);
	//	timer.Stop();
	//	std::cout << "Output size: " << output.size() / (1024.0 * 1024.0) << " MB\n";
	//	timer.Print();
	//}

	//// Test 7: Pretty print first 3 items
	//std::cout << "\nTest 7: Pretty printing first 3 items...\n";
	//{
	//	Timer timer;
	//	Json::Value firstThree(Json::arrayValue);
	//	for (int i = 0; i < 3 && i < root.size(); ++i)
	//	{
	//		firstThree.append(root[i]);
	//	}
	//
	//	Json::StreamWriterBuilder builder;
	//	builder["indentation"] = "    ";
	//	std::string prettyOutput = Json::writeString(builder, firstThree);
	//	timer.Stop();
	//	std::cout << prettyOutput << "\n";
	//	timer.Print();
	//}

	std::cout << "\n=== All tests completed ===\n";

	return 0;
}