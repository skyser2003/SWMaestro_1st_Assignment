#pragma once

#include <chrono>

class DeltaTime
{
public:
	DeltaTime();

	void Init();

	int NextMilli();
	int GetTotalTime() const;

private:
	std::chrono::time_point<std::chrono::steady_clock> prev;
	int totalTime;
};