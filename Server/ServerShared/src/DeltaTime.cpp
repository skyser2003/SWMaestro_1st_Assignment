#include "stdafx.h"
#include "DeltaTime.h"

using namespace std::chrono;

DeltaTime::DeltaTime()
{
	Init();
}

void DeltaTime::Init()
{
	prev = steady_clock::now();
	totalTime = 0;
}

int DeltaTime::NextMilli()
{
	auto now = steady_clock::now();
	auto diff = std::chrono::duration_cast<std::chrono::milliseconds>(now - prev);

	prev = now;

	totalTime += diff.count();

	return diff.count();
}

int DeltaTime::GetTotalTime() const
{
	return totalTime;
}