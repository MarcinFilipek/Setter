/*
 * CWidgetEditNumber.cpp
 *
 *  Created on: Oct 12, 2015
 *      Author: krzysiek
 */

#include "CWidgetEditNumber.h"
#include "CGraphicFont.h"
#include "st7565Driver.h"
#include "CFont.h"

#include <stdio.h>

void CWidgetEditNumber::init(uint8_t x, uint8_t y, int32_t value, int32_t min, int32_t max, int8_t digitsNumber,
        int8_t flags)
{
    m_x = x;
    m_y = y;
    m_value = value;
    m_min = min;
    m_max = max;
    m_digitsNumber = digitsNumber;
    m_flags = flags;
    m_focus = false;
    m_redraw = true;
}

void CWidgetEditNumber::setFocus(bool focus)
{
    if (m_focus != focus)
    {
        m_focus = focus;
        m_redraw = true;
    }
}

bool CWidgetEditNumber::getFocus()
{
    return m_focus;
}

int32_t CWidgetEditNumber::getValue()
{
    return m_value;
}

void CWidgetEditNumber::update()
{
    if (m_redraw)
    {
        m_redraw = false;
        draw();
    }
}

void CWidgetEditNumber::redraw()
{
    m_redraw = true;
}

bool CWidgetEditNumber::onKey(int8_t keyCode, int8_t keyEvent)
{
    if (keyEvent == KEY_EVENT_UP)
    {
        return false;
    }

    if (m_focus == false)
    {
        return false;
    }

    switch (keyCode)
    {
        case KEY_CODE_UP:
            if (m_value < m_max)
            {
                m_value++;
                m_redraw = true;
            }
            return true;

        case KEY_CODE_DOWN:
            if (m_value > m_min)
            {
                m_value--;
                m_redraw = true;
            }
            return true;

        default:
            return false;
    }
}

void CWidgetEditNumber::draw()
{
    char buffer[16];
    char format[16];
    char tmp[16];
    bool showZeros = (m_flags & FLAG_SHOW_ZEROS);
    bool showSign = (m_flags & FLAG_SHOW_SIGN);

    uint8_t posX2 = m_x + (13 * m_digitsNumber);
    uint8_t posY2 = m_y + 17;
    int16_t tempY = ((m_y + posY2 + 1) / 2) - (CGraphicFont::getFontHeight(CFont::FONT_3) / 2);

    snprintf(tmp, sizeof(tmp), "%d", m_digitsNumber);
    snprintf(format, sizeof(format), "%%%s%s%sd", showSign ? "+" : "", showZeros ? "0" : "", tmp);
    snprintf(buffer, sizeof(buffer), format, m_value);

    CST7565Driver::fill( //
            m_x,
            m_y,
            posX2,
            posY2,
            getFocus() ? CST7565Driver::FILL_OPERATION_FILL : CST7565Driver::FILL_OPERATION_ERASE);

    CGraphicFont::drawText( //
            m_x,
            tempY,
            posX2,
            tempY + 17,
            0,
            buffer,
            CFont::FONT_3,
            CGraphicFont::PR_NORMAL,
            CGraphicFont::AT_CENTER,
            CGraphicFont::MULTILINE_OFF,
            {CST7565Driver::BIT_OPERATION_XOR});

}
