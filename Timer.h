#pragma once

#include <chrono>
#include <iostream>

class Timer
{
public:
	Timer()
	{
		// Initialize to current time to avoid garbage values
		m_StartTimepoint = std::chrono::high_resolution_clock::now();
	}

	~Timer()
	{
		Stop();
	}

	void Start()
	{
		m_StartTimepoint = std::chrono::high_resolution_clock::now();
		m_Stopped = false;
		m_Duration = 0;
	}

	void Stop()
	{
		if (!m_Stopped)
		{
			auto endTimepoint = std::chrono::high_resolution_clock::now();
			auto start = std::chrono::time_point_cast<std::chrono::microseconds>(m_StartTimepoint).time_since_epoch().count();
			auto end = std::chrono::time_point_cast<std::chrono::microseconds>(endTimepoint).time_since_epoch().count();

			m_Duration = end - start;
			m_Stopped = true;
		}
	}

	void Print() const
	{
		std::cout << "Duration: " << ElapsedMilliseconds() / 1000 << "s\n";
	}

	void Reset()
	{
		m_StartTimepoint = std::chrono::high_resolution_clock::now();
		m_Stopped = false;
		m_Duration = 0;
	}

	long long ElapsedMicroseconds() const
	{
		auto endTimepoint = std::chrono::high_resolution_clock::now();
		auto start = std::chrono::time_point_cast<std::chrono::microseconds>(m_StartTimepoint).time_since_epoch().count();
		auto end = std::chrono::time_point_cast<std::chrono::microseconds>(endTimepoint).time_since_epoch().count();
		return end - start;
	}

	double ElapsedMilliseconds() const
	{
		return ElapsedMicroseconds() * 0.001;
	}

private:
	std::chrono::time_point<std::chrono::high_resolution_clock> m_StartTimepoint;
	bool m_Stopped = false;
	long long m_Duration = 0;
};
