/**************************************************************************************************************
* Custom Timer - Header
*
* A static class that's used to produce a delta time which can be used to make timers.
*
* Created by Dean Atkinson-Walker 2023
***************************************************************************************************************/


#pragma once

#include <chrono>

using namespace std::chrono;

class Time
{
public:
    static void Update()
    {
        // The time between the last tick.......
        const duration<double, std::milli> elapsed_time = high_resolution_clock::now() - lastFrameTime;
        deltaTime = elapsed_time.count();
    }

    static void SetLastFrameTime(high_resolution_clock::time_point newFrameTime) { lastFrameTime = newFrameTime; }

    static double GetDeltaTime() { return deltaTime; }

private:
    static high_resolution_clock::time_point lastFrameTime;
    static double deltaTime;
};


// Initially set values.
double Time::deltaTime = 0;
high_resolution_clock::time_point Time::lastFrameTime = high_resolution_clock::now();