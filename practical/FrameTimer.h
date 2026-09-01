#pragma once
#include<Windows.h>
class FrameTimer
{
	public:
		void Init(int FPS);
		int FramesToUpdate();
	private:
		LARGE_INTEGER timerFreq;
		LARGE_INTEGER timeNow;
		LARGE_INTEGER timePrevious;
		int RequestedFPS;
		float intervalsPerFrame;
		float intervalsSinceLastUpdate;

};

