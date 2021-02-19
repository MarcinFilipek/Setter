/*
 * CDriverBuzzerAsync.cpp
 *
 *  Created on: Oct 14, 2014
 *      Author: krzysiek
 */

#include "CDriverBuzzerAsync.h"

#include <string.h>

CDriverBuzzerAsync::CDriverBuzzerAsync() :
        m_output(NULL), m_interval(0)
{
    memset(m_intervalQueue, 0, sizeof(m_intervalQueue));
}

void CDriverBuzzerAsync::init(ITwoLogicalStatesHardware* output)
{
    m_output = output;
}

void CDriverBuzzerAsync::beep(uint16_t milliseconds)
{
    addInterval(milliseconds);
}

void CDriverBuzzerAsync::updateFromInterrupt(uint16_t updateFrequency)
{
    if (m_output == NULL)
        return;

    int32_t interval = m_interval;

    if (interval != 0)
    {
        interval -= 1000 / updateFrequency;

        if (interval <= 0)
        {
            if (m_output->isOn())
            {
                interval = m_intervalCopy / 2;
                m_output->turnOff();
            }
            else
            {
                interval = 0;
            }
        }

        m_interval = interval;
    }
    else
    {
        interval = m_intervalQueue[0];
        if (interval != 0)
        {
            moveIntervals();

            m_interval = interval;
            m_intervalCopy = interval;
            m_output->turnOn();
        }
    }
}

void CDriverBuzzerAsync::addInterval(uint16_t interval)
{
    for (uint8_t i = 0; i < QUEUE_SIZE; i++)
    {
        if (m_intervalQueue[i] == 0)
        {
            m_intervalQueue[i] = interval;
            return;
        }
    }
}

void CDriverBuzzerAsync::moveIntervals()
{
    for (uint8_t i = 1; i < QUEUE_SIZE; i++)
        m_intervalQueue[i - 1] = m_intervalQueue[i];
    m_intervalQueue[QUEUE_SIZE - 1] = 0;
}
