/*
 * CContext.cpp
 *
 *  Created on: Sep 30, 2015
 *      Author: krzysiek
 */

#include "CContext.h"

IUpdatable *CContext::m_updatables[MAX_UPDATABLES];
IUpdatable *CContext::m_alwaysUpdatables[MAX_ALWAYS_UPDATABLES];
CKeyboard *CContext::m_keyboard;
bool CContext::m_redraw;
bool CContext::m_reinit;
CContext::SScreenItem CContext::m_screenItems[MAX_SCREENS];
int8_t CContext::m_screenItemsCount;
IOnKeyListener *CContext::m_onKeyListeners[MAX_KEY_LISTENERS];

#ifdef LOOPCOUNT
volatile uint32_t CContext::licz = 0;
#endif

void CContext::addUpdatable(IUpdatable *updatable, bool forceAlways)
{
    removeUpdatable(updatable, forceAlways);

    IUpdatable** updatables;
    int8_t maxUpdatables;

    if(forceAlways)
    {
    	updatables = CContext::m_alwaysUpdatables;
    	maxUpdatables = CContext::MAX_ALWAYS_UPDATABLES;
    }
    else
    {
    	updatables = CContext::m_updatables;
    	maxUpdatables = CContext::MAX_UPDATABLES;
    }

	if (updatables[maxUpdatables - 1] == NULL)
	{
		for (int8_t i = maxUpdatables - 1; i > 0; i--)
		{
			updatables[i] = updatables[i - 1];
		}
		updatables[0] = updatable;
	}
}

void CContext::removeUpdatable(IUpdatable *updatable, bool fromAlways)
{

    IUpdatable** updatables;
    int8_t maxUpdatables;

    if(fromAlways)
    {
    	updatables = CContext::m_alwaysUpdatables;
    	maxUpdatables = CContext::MAX_ALWAYS_UPDATABLES;
    }
    else
    {
    	updatables = CContext::m_updatables;
    	maxUpdatables = CContext::MAX_UPDATABLES;
    }

	for (int8_t i = 0; i < maxUpdatables; i++)
	{
		if (updatables[i] == updatable)
		{
			for (int8_t j = i; j < maxUpdatables - 1; j++)
			{
				updatables[j] = updatables[j + 1];
			}
			updatables[maxUpdatables - 1] = NULL;
		}
	}
}

void CContext::setKeyboard(CKeyboard *keyboard)
{
    m_keyboard = keyboard;
}

void CContext::showScreen(AScreen *screen)
{
    if (m_screenItemsCount == MAX_SCREENS)
    {
        return;
    }

    if (m_screenItemsCount > 0)
    {
        SScreenItem *screenPrev = &m_screenItems[m_screenItemsCount - 1];
        screenPrev->screen->onPause();
        screenPrev->state = 1;
    }

    SScreenItem *screenItem = &m_screenItems[m_screenItemsCount];
    m_screenItemsCount++;

    screenItem->screen = screen;
    screenItem->state = 0;
    screenItem->finish = false;

    while (true)
    {
        for (int16_t i = 0; i < MAX_ALWAYS_UPDATABLES; i++)
        {
            IUpdatable *updatable = m_alwaysUpdatables[i];
            if (updatable != NULL)
            {
                updatable->update();
            }
        }
        switch (screenItem->state)
        {
            case 0:
                screen->onStart();
                screenItem->state = 1;
                m_reinit = false;
            break;

            case 1:
#ifdef LOOPCOUNT
    	licz++;
#endif
                screen->onResume();
                m_redraw = false;
                screenItem->state = 2;
            break;

            case 2:
                screen->update();
                for (int16_t i = 0; i < MAX_UPDATABLES; i++)
                {
                    IUpdatable *updatable = m_updatables[i];
                    if (updatable != NULL)
                    {
                        updatable->update();
                    }
                }
                if (m_redraw)
                {
                    screenItem->state = 1;
                    break;
                }
                if(m_reinit)
                {
                	screenItem->state = 0;
                	break;
                }
                if (screenItem->finish)
                {
                    screenItem->state = 3;
                    break;
                }
            break;

            case 3:
                screen->onPause();
                screenItem->state = 4;
            break;

            case 4:
                screen->onStop();
                screenItem->state = 5;
            break;
        }

        if (screenItem->state >= 5)
        {
            break;
        }

        if (m_keyboard != NULL)
        {
            m_keyboard->update();

            for (int16_t i = 0; i < MAX_KEY_LISTENERS; i++)
            {
                IOnKeyListener *onKeyListener = m_onKeyListeners[i];
                if (onKeyListener != NULL)
                {
                    m_keyboard->callKeyEvents(onKeyListener);
                }
            }
            m_keyboard->clearKeyEvents();
        }
    }

    m_screenItemsCount--;
    screenItem->screen = NULL;
}

void CContext::finishScreen(AScreen *screen)
{
    if (m_screenItemsCount > 0)
    {
        if (screen == NULL)
        {
            m_screenItems[m_screenItemsCount - 1].finish = true;
        }
        else
        {
            for (int8_t i = 0; i < m_screenItemsCount; i++)
            {
                if (m_screenItems[i].screen == screen)
                {
                    m_screenItems[i].finish = true;
                }
            }
        }

    }
}

void CContext::reinitScreen()
{
	m_reinit = true;
}

void CContext::redraw()
{
    m_redraw = true;
}

void CContext::registerOnKeyListener(IOnKeyListener* onKeyListener)
{
    unregisterOnKeyListener(onKeyListener);
    if (m_onKeyListeners[MAX_KEY_LISTENERS - 1] == NULL)
    {
        for (int8_t i = MAX_KEY_LISTENERS - 1; i > 0; i--)
        {
            m_onKeyListeners[i] = m_onKeyListeners[i - 1];
        }
        m_onKeyListeners[0] = onKeyListener;
    }
}

void CContext::unregisterOnKeyListener(IOnKeyListener* onKeyListener)
{
    for (int8_t i = 0; i < MAX_KEY_LISTENERS; i++)
    {
        if (m_onKeyListeners[i] == onKeyListener)
        {
            for (int8_t j = i; j < MAX_KEY_LISTENERS - 1; j++)
            {
                m_onKeyListeners[j] = m_onKeyListeners[j + 1];
            }
            m_onKeyListeners[MAX_KEY_LISTENERS - 1] = NULL;
        }
    }
}
