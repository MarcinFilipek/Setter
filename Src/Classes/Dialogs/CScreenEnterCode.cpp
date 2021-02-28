/*
 * CScreenEnterCode.cpp
 *
 *  Created on: Oct 12, 2015
 *      Author: krzysiek
 */

#include "CScreenEnterCode.h"

void CScreenEnterCode::init(uint32_t title)
{
    m_title = title;
}

bool CScreenEnterCode::getResult(int32_t *result)
{
    if (m_result)
    {
        *result = 0;
        for (int8_t i = 0; i < NUM_OF_EDIT_NUMBER; i++)
        {
            *result *= 10;
            *result += m_widgetEditNumber[i].getValue();
        }
        return true;
    }
    else
    {
        return false;
    }
}

void CScreenEnterCode::onStart()
{
    m_widgetButtonsBar.init(1, 54, CWidgetButtonsBar::ITEMS_CONFIRM_CANCEL, 2);
    for (int8_t i = 0; i < NUM_OF_EDIT_NUMBER; i++)
    {
        m_widgetEditNumber[i].init((128 - 14 * NUM_OF_EDIT_NUMBER) / 2 + 14 * i, 21, 0, 0, 9, 1, 0);
    }
    m_pointer = 0;
}

void CScreenEnterCode::onResume()
{
    CScreen::onResume();
    CContext::registerOnKeyListener(&m_widgetButtonsBar);
    for (int8_t i = 0; i < NUM_OF_EDIT_NUMBER; i++)
    {
        CContext::registerOnKeyListener(&m_widgetEditNumber[i]);
    }

    CST7565Driver::suspendDrawing();
    CST7565Driver::clear();

    drawHeader(m_title);

    CST7565Driver::fill(0, 52, 127, 52, CST7565Driver::FILL_OPERATION_FILL);

    m_widgetButtonsBar.redraw();
    m_widgetButtonsBar.update();

    for (int8_t i = 0; i < NUM_OF_EDIT_NUMBER; i++)
    {
        m_widgetEditNumber[i].redraw();
        m_widgetEditNumber[i].update();
    }

    CST7565Driver::resumeDrawing();
}

void CScreenEnterCode::update()
{
    CScreen::update();

    m_widgetButtonsBar.update();

    for (int8_t i = 0; i < NUM_OF_EDIT_NUMBER; i++)
    {
        m_widgetEditNumber[i].setFocus((m_pointer == i) && (m_widgetButtonsBar.getFocus() == false));
        m_widgetEditNumber[i].update();
    }

    int8_t result;
    if (m_widgetButtonsBar.getResult(&result))
    {
        m_result = (result == 0);
        finish();
    }
}

void CScreenEnterCode::onPause()
{
    CScreen::onPause();
    CContext::unregisterOnKeyListener(&m_widgetButtonsBar);
    for (int8_t i = 0; i < NUM_OF_EDIT_NUMBER; i++)
    {
        CContext::unregisterOnKeyListener(&m_widgetEditNumber[i]);
    }
}

bool CScreenEnterCode::onKey(int8_t keyCode, int8_t keyEvent)
{
    if (keyEvent == KEY_EVENT_UP)
    {
        return false;
    }

    switch (keyCode)
    {
        case KEY_CODE_MENU:
            if (m_pointer == NUM_OF_EDIT_NUMBER - 1)
            {
                m_pointer = 0;
                m_widgetButtonsBar.setFocus(true);
            }
            else
            {
                m_pointer++;
            }
            return true;

        case KEY_CODE_EXIT:
            m_widgetButtonsBar.setFocus(!m_widgetButtonsBar.getFocus());
            resume();
            return true;

        default:
            return false;
    }
}
