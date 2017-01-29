/**
References : 2nd Year C++ Project (Romesh Selvanathan) ,
			 Nehe.gamedev.net tutorial 22:
			 http://nehe.gamedev.net/tutorial/lines,_antialiasing,_timing,_ortho_view_and_simple_sounds/17003/
*/ 

#include "FrameTimer.h"
#include "GameUtil.h"

/** Sets up the timer with a requested frame rate of the program,
	if not met it will skip the frames
	Also Sets up values for the timer to be used for timing purposes
*/ 
void FrameTimer::init(int fps){
	// Query's the CPU
	QueryPerformanceFrequency(&timerFreq);
	QueryPerformanceCounter(&timeNow);
	QueryPerformanceCounter(&timePrevious);

	// Store Timer Frequency
	QueryPerformanceFrequency((largeInt *) &frequency);
	// Get Current time and store it in timer start
	QueryPerformanceCounter((largeInt *) &timer_start);
	// Calcu resolution using the frequency
	resolution = (float)(((double)1.0f)/((double)frequency));
	// Set the time elapsed since start was called
	timer_elapsed = timer_start;
	
	//init fps time info
	Requested_FPS=fps;

	//The number of intervals in the given timer, per frame at the requested rate.
	intervalsPerFrame = ( (float)timerFreq.QuadPart / Requested_FPS );
}

/** Returns number of frames that need to be updated to maintain the fps, 
	since last time the function was called
*/
const int FrameTimer::framesToUpdate(){
	int framesToUpdate = 0;
	QueryPerformanceCounter(&timeNow);

	intervalsSinceLastUpdate = (float)timeNow.QuadPart - (float)timePrevious.QuadPart;
	
	framesToUpdate = (int)( intervalsSinceLastUpdate / intervalsPerFrame );

	//If it is not updateing any frames, keep the old previous timer count
	if (framesToUpdate != 0){
		QueryPerformanceCounter(&timePrevious);
	}

	return framesToUpdate;
}
/* Returns the current time  since program was started*/
const float FrameTimer::GetTime()
{
	// A 64 bit hold value of time
	__int64 time;
	// Store current time into the time variable
	QueryPerformanceCounter((largeInt *) &time);
	// returns current time minus the time at start * the resolution then times 1000 to get millisecond value 
	return ((float)(time - timer_start) * resolution) * 1000.f;
}

/* Returns a steady time to be used for update purposes in game */ 
const float FrameTimer::GetElapsedTimeSinceLastUpdate()
{
	// Difference in Time
	float dt;
	// Time of last Update
	static float lastUpdate;
	// Difference in time equals current time minus time of last update
	dt = GetTime() - lastUpdate;
	// last Update equals the current time
	lastUpdate = GetTime();

	return dt;
}