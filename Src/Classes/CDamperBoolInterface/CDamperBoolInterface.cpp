/*
 * CDamperBoolInterface.cpp
 *
 *  Created on: Oct 7, 2015
 *      Author: krzysiek
 */

#include "CDamperBoolInterface.h"

void CDamperBoolInterface::init(IBoolInterface* boolInterface)
{
    m_boolInterface = boolInterface;
    m_timer.setCounterType(CTimer::COUNTER_CSEK);
}

bool CDamperBoolInterface::isOn()
{
    if (m_timer.isZero())
    {
        bool state = m_boolInterface->isOn();
        if (m_state != state)
        {
            m_state = state;
            m_timer.start(MILLISECONDS / 10);
        }
    }
    return m_state;
}
