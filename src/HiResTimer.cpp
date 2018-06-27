#include "stdafx.h"
#include "HiResTimer.h"
#include "win32.h"
#include <chrono>>

uint64_t frequency = 0;

HiResTime::HiResTime(uint64_t counter)
	:counter(counter)
{
}

HiResTime::~HiResTime()
{
}

double HiResTime::ToSeconds() const
{

	//Resolution is microseconds
	return  ((counter * 1'000'000) / frequency) / 1'000'000.0;
}


HiResTimer::HiResTimer()
{
	if (frequency==0)
	{
		LARGE_INTEGER fr;
		QueryPerformanceFrequency(&fr);
		frequency = fr.QuadPart;
	}


	LARGE_INTEGER startingCounter;
	QueryPerformanceCounter(&startingCounter);
	counter = startingCounter.QuadPart;
}

HiResTimer::~HiResTimer()
{
}

HiResTime HiResTimer::Update()
{
	LARGE_INTEGER newCounter;
	QueryPerformanceCounter(&newCounter);

	uint64_t delta = newCounter.QuadPart - counter;


	return HiResTime(delta);
}

void HiResTimer::Reset()
{
	LARGE_INTEGER newCounter;

	QueryPerformanceCounter(&newCounter);

	counter = newCounter.QuadPart;
}

