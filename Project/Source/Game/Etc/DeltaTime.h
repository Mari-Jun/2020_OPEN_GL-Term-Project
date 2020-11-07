#pragma once
#include <chrono>

using namespace std::chrono;

using Clock = high_resolution_clock;

class DeltaTime final
{
private:
	Clock::time_point mStart;		

public:
	DeltaTime()
	{
		reset();
	}
	~DeltaTime()
	{}

	void reset()
	{
		mStart = Clock::now();
	}

	float getDeltaTime()
	{
		return static_cast<float>(duration_cast<duration<float>>(Clock::now() - mStart).count());
	}
};