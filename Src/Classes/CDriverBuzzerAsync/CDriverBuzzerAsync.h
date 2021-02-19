/*
 * CDriverBuzzerAsync.h
 *
 *  Created on: Oct 14, 2014
 *      Author: krzysiek
 */

#ifndef CDRIVERBUZZERASYNC_H_
#define CDRIVERBUZZERASYNC_H_

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "iTwoLogicalStatesHardware.h"
#include "iinterruptupdatable.h"
#include "IBuzzer.h"


class CDriverBuzzerAsync: public IBuzzer, public IInterruptUpdatable
{
    static const uint8_t QUEUE_SIZE = 4;

    ITwoLogicalStatesHardware *m_output;

    uint16_t m_interval;
    uint16_t m_intervalCopy;
    uint16_t m_intervalQueue[QUEUE_SIZE];

public:
    CDriverBuzzerAsync();
    void init(ITwoLogicalStatesHardware *output);
    void beep(uint16_t milliseconds);
    void updateFromInterrupt(uint16_t updateFrequency);

private:
    void addInterval(uint16_t interval);
    void moveIntervals();
};

#endif /* CDRIVERBUZZERASYNC_H_ */
