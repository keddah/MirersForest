/**************************************************************************************************************
* Custom Timer - Header
*
* A static class that's used to produce a delta time which can be used to make timers.
*
* Created by Dean Atkinson-Walker 2023
***************************************************************************************************************/


#pragma once

#include <chrono>
#include <SDL.h>
using namespace std::chrono;

class Time 
{
public:
    static void Update() 
    {
        // The time between the last tick.......
        const duration<float, std::milli> elapsed_time = high_resolution_clock::now() - lastFrameTime;
        deltaTime = elapsed_time.count();
    }

    static void SetLastFrameTime(high_resolution_clock::time_point newFrameTime) { lastFrameTime = newFrameTime; }

    static float GetDeltaTime() { return deltaTime; }

private:
    static high_resolution_clock::time_point lastFrameTime;
    static float deltaTime;
};