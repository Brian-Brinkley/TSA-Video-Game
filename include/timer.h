#pragma once
#include "raylib.h"
#include <functional>

class Timer{
public:
    int duration;
    bool active;
    double startTime;
    bool repeat;
    std::function<void()> func;
    Timer(int duration, bool repeat, bool autostart, std::function<void()> func);
    void Activate();
    void Deactivate();
    void Update();
};