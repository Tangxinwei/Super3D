#pragma once
#include <vector>
#include <util/Function.hpp>
#include <time.h>
using namespace std;

class FrameTimer : public SingletonBase<FrameTimer>
{
private:
	int64_t preTime;
	int64_t dt;
public:
	void doInit()
	{
		preTime = 0;
	}
	void update()
	{
		clock_t now = clock();
		if (preTime)
			dt = now - preTime;
		else
			dt = 0;
		preTime = now;
	}
	int64_t getFrameDeltaTime()
	{
		return dt;
	}
};
