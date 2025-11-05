// Json_Optimized.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Timer.h"
#include "json/json.h"

int main()
{
	std::cout << "=== JsonCpp Performance Testing ===\n\n";

	// Test 1: Read JSON file from disk
	std::cout << "Test 1: Reading random_data.json from disk...\n";
	std::ifstream file("random_data.json", std::ifstream::binary);
	if (!file.is_open())
	{
		std::cerr << "Error: Could not open random_data.json\n";
		return 1;
	}

	// Test 2: Parse JSON with JsonCpp
	std::cout << "\nTest 2: Parsing JSON with JsonCpp...\n";
	Json::Value root;
	{
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
		std::cout << "Number of elements: " << root.size() << "\n";
		timer.Print();
	}
	file.close();

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