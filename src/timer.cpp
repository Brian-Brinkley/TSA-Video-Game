#include "timer.h"

Timer::Timer(int duration, bool repeat, bool autostart, std::function<void()> func)
    : duration(duration), startTime(0), active(false), repeat(repeat), func(func)
{
if(autostart){
    Activate();
}
}

void Timer::Activate(){
    active = true;
    startTime = GetTime();
}

void Timer::Deactivate(){
    active = false;
    startTime = 0;
    if(repeat){
        Activate();
    }
}

void Timer::Update(){
    if(!active){
        return;
    }
    if((GetTime() - startTime) >= duration){
       if((func && startTime) >= 0){
        func();
       }
       Deactivate();
    }
}