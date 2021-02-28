#include "wtp3drivercalls.h"
#include "timer.h"

static CTimer wtp4timers[3] = {CTimer(CTimer::UNIT_MILISEC), CTimer(CTimer::UNIT_MILISEC), CTimer(CTimer::UNIT_MILISEC)};

void wtp3drivercalls_setTimer(uint8_t nr, uint32_t ms)
{
    wtp4timers[nr].start(ms);
}

uint8_t wtp3drivercalls_isTimerZero(uint8_t nr)
{
    return wtp4timers[nr].isZero();
}

void wtp3drivercalls_updateCounters()
{
    uint8_t i;

    for(i = 0; i < 3; i++)
    {
        wtp4timers[i].isZero();
    }
}

