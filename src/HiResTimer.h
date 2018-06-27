#pragma once

#include <stdint.h>

struct HiResTime
{
private:
	uint64_t counter;
public:
	HiResTime(uint64_t counter);
	~HiResTime();

	double ToSeconds() const;
};

class HiResTimer
{
private:
	uint64_t counter = 0;

public:
	HiResTimer();
	~HiResTimer();

	HiResTime Update();
	void Reset();
};

