/*
 * CKeyboard.cpp
 *
 *  Created on: Sep 30, 2015
 *      Author: krzysiek
 */

#include "CKeyboard.h"

#include <string.h>

CKeyboard::CKeyboard() :
        m_keysCount(0), m_timer(CTimer::COUNTER_CSEK)
{
    memset(m_keyLastState, 0, sizeof(m_keyLastState));
    clearKeyEvents();
    m_timer.startFreeRun();
}

void CKeyboard::addKey(int8_t keyCode, IBoolInterface* boolInterface)
{
    if (m_keysCount < MAX_KEYS)
    {
        m_keys[m_keysCount] = boolInterface;
        m_keyCodes[m_keysCount] = keyCode;
        m_keysCount++;
    }
}

void CKeyboard::setOnKeyListener(IOnKeyListener *onKeyListener)
{
    m_onKeyListener = onKeyListener;
}

void CKeyboard::update()
{
    uint16_t time = m_timer.getElapsedTime();
    bool resetTimer = true;

    while (true)
    {
        int8_t keyCode = 0;
        int8_t keyEvent = 0;

        for (int16_t i = 0; i < m_keysCount; i++)
        {
            bool keyState = m_keys[i]->isOn();

            if (keyState)
            {
                resetTimer = false;
            }

            if (m_keyLastState[i] != keyState)
            {
                m_keyLastState[i] = keyState;

                keyEvent = keyState ? IOnKeyListener::KEY_EVENT_DOWN : IOnKeyListener::KEY_EVENT_UP;

                if (keyState)
                {
                    m_keyTime[i] = time;
                    m_keyRepeats[i] = 0;
                }
            }

            if (keyState)
            {
                int16_t interval = 200 / (5 + m_keyRepeats[i]);
                if (interval < 10)
                {
                    interval = 10;
                }

                if (m_keyTime[i] + interval <= time)
                {
                    keyEvent = IOnKeyListener::KEY_EVENT_PRESSED;
                    m_keyTime[i] = time;
                    if (m_keyRepeats[i] < 0xFF)
                    {
                        m_keyRepeats[i]++;
                    }
                }
            }

            if (keyEvent != 0)
            {
                keyCode = m_keyCodes[i];
                break;
            }
        }

        if (keyEvent == 0)
        {
            break;
        }

        if (m_onKeyListener != NULL)
        {
            m_onKeyListener->onKey(keyCode, keyEvent);
        }

        for (int8_t i = 0; i < MAX_KEY_EVENTS; i++)
        {
            if (m_keyEventsKeyEvent[i] == 0)
            {
                m_keyEventsKeyCode[i] = keyCode;
                m_keyEventsKeyEvent[i] = keyEvent;
                break;
            }
        }
    }

    if (resetTimer)
    {
        m_timer.startFreeRun();
    }
}

void CKeyboard::callKeyEvents(IOnKeyListener *onKeyListener)
{
    for (int8_t i = 0; i < MAX_KEY_EVENTS; i++)
    {
        int8_t keyCode = m_keyEventsKeyCode[i];
        int8_t keyEvent = m_keyEventsKeyEvent[i];
        if (keyEvent != 0)
        {
            int8_t tmp = m_keyEventsKeyEvent[i];
            m_keyEventsKeyEvent[i] = 0;
            if (onKeyListener->onKey(keyCode, keyEvent) == false)
            {
                m_keyEventsKeyEvent[i] = tmp;
            }
        }
    }
}

void CKeyboard::clearKeyEvents()
{
    for (int8_t i = 0; i < MAX_KEY_EVENTS; i++)
    {
        m_keyEventsKeyEvent[i] = 0;
    }
}
