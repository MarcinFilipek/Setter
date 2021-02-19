#ifndef CSYSTEM_H_
#define CSYSTEM_H_

#include <hal.h>
#include <stdint.h>
#include <stdio.h>
#include <stdarg.h>

#include "iinterruptupdatable.h"
#include "iDelay.h"

#define UPDATABLES_COUNT 6
#define FAST_UPDATABLES_COUNT 6

class CSystem
{
public:
    typedef enum
    {
        OT_OSCILATOR_EXTERNAL, OT_OSCILATOR_INTERNAL,
    } TOscilatorType;

    class CDelayFunctions: public IDelayFunctions
    {
    public:
        void delayms(uint16_t ms);
        void delayus(uint16_t ns);
    };

private:
    static IWDG_HandleTypeDef m_hiwdg;

    static TOscilatorType m_oscilatorType;
    static volatile uint64_t m_timeMiliseconds;

    static IInterruptUpdatable* m_interruptUpdatable[UPDATABLES_COUNT];
    static IInterruptUpdatable* m_fastInterruptUpdatable[FAST_UPDATABLES_COUNT];

public:
    static void initSystemClock(TOscilatorType oscilatorType);
    static uint32_t getSystemClockFreq(); //Uzywac dopiero po wywolaniu metody initSystemClock
    static void initPeripherialsClock();
    static void initBrownOutDetection();
    static void configureWatchdog(uint16_t miliseconds);
    static void reloadWatchdog();
    static void reset();

    static uint32_t getTimeSeconds();
    static uint64_t getTimeHSeconds();
    static uint64_t getTimeMiliseconds();
    static uint64_t getTimeMicroseconds();

    static void delayMs(uint32_t miliseconds);
    static void delayUs(uint32_t microseconds);

    static void print(const char *format, ...);
    static void vprint(const char *format, va_list ap);
    static void println(const char *format = "", ...);

    static void addInterruptUpdatable(IInterruptUpdatable *interruptUpdatable);
    static void addFastInterruptUpdatable(IInterruptUpdatable *interruptUpdatable);

    static void SysTick_Handler();

private:
    static bool initSystemClockOscExternal();
    static bool initSystemClockOscInternal();
};
#endif /* CSYSTEM_H_ */
