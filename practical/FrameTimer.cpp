#include "FrameTimer.h"

void FrameTimer::Init(int FPS)
{
	QueryPerformanceFrequency(&timerFreq);
	QueryPerformanceCounter(&timeNow);
	QueryPerformanceCounter(&timePrevious);
	//init fps time info
	RequestedFPS=FPS;
	// //The number of intervals in the given
	//timer, per frame at the requested rate.
	intervalsPerFrame = 	((float)timerFreq.QuadPart / RequestedFPS);
}

int FrameTimer::FramesToUpdate()
{
	int framesToUpdate = 0;
	QueryPerformanceCounter(&timeNow);
	//getting the delta time
	intervalsSinceLastUpdate = timeNow.QuadPart - timePrevious.QuadPart;
	framesToUpdate = (int)( intervalsSinceLastUpdate / intervalsPerFrame );
	//If we are not updating any frames, keep the old previous timer count
   if (framesToUpdate != 0){
	   QueryPerformanceCounter(&timePrevious);
	}
	return framesToUpdate;

}
