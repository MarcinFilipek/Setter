/*
 * CWidgetButtonsBar.cpp
 *
 *  Created on: Oct 2, 2015
 *      Author: krzysiek
 */

#include "CWidgetButtonsBar.h"
#include "CGraphicFont.h"

#include "CFont.h"
#include "CNapisy.h"
#include "CScreen.h"

const uint32_t CWidgetButtonsBar::ITEMS_CONFIRM_CANCEL[] =
{CNapisy::IDT_ZATWIERDZ, CNapisy::IDT_ANULUJ};

const uint32_t CWidgetButtonsBar::ITEMS_CONFIRM_CANCEL_EXIT[] =
{CNapisy::IDT_ZATWIERDZ, CNapisy::IDT_ANULUJ, CNapisy::IDT_WYJSCIE};

const uint32_t CWidgetButtonsBar::ITEMS_YES_NO[] =
{CNapisy::IDT_TAK, CNapisy::IDT_NIE};

const uint32_t CWidgetButtonsBar::ITEMS_OK[] =
{CNapisy::IDT_OK};

const uint32_t CWidgetButtonsBar::ITEMS_ABORT[] =
{CNapisy::IDT_ANULUJ};

const uint32_t CWidgetButtonsBar::ITEMS_DELETE_CANCEL[] =
{CNapisy::IDT_USUN, CNapisy::IDT_ANULUJ};

const uint32_t CWidgetButtonsBar::ITEMS_EXIT_DELETE[] =
{CNapisy::IDT_WYJSCIE, CNapisy::IDT_USUN};

const uint32_t CWidgetButtonsBar::ITEMS_EXIT_MORE_DELETE[] =
{CNapisy::IDT_WYJSCIE, CNapisy::IDT_DALEJ, CNapisy::IDT_USUN};


void CWidgetButtonsBar::init(uint8_t x, uint8_t y, const uint32_t *items, int8_t itemsNumber, bool focus)
{
    m_x = x;
    m_y = y;
    m_items = items;
    m_itemsNumber = itemsNumber;

    m_distance = 5;
    m_center = false;

    m_focus = focus;
    m_result = false;
    m_redraw = true;
    m_topLine = false;
    m_selectedItem = 0;

    if(m_items == ITEMS_DELETE_CANCEL)
    {
    	m_selectedItem = 1;
    }
}

void CWidgetButtonsBar::setFocus(bool focus)
{
    if (m_focus != focus)
    {
        m_focus = focus;
        m_selectedItem = focus ? 0 : -1;
        m_result = false;
        m_redraw = true;
    }
}

bool CWidgetButtonsBar::getFocus()
{
    return m_focus;
}

bool CWidgetButtonsBar::getResult(int8_t *result)
{
    if (m_result == false)
    {
        return false;
    }
    else
    {
        *result = m_selectedItem;
        m_result = false;
        return true;
    }
}

void CWidgetButtonsBar::update()
{
    if (m_redraw)
    {
        m_redraw = false;
        draw();
    }
}

void CWidgetButtonsBar::redraw()
{
    m_redraw = true;
}

void CWidgetButtonsBar::setTopLine(bool visible)
{
	m_topLine = visible;
}
void CWidgetButtonsBar::setCenter(bool enabled)
{
	m_center = enabled;
}

void CWidgetButtonsBar::setPosition(uint8_t x, uint8_t y)
{
	m_x = x;
	m_y = y;
}

bool CWidgetButtonsBar::onKey(int8_t keyCode, int8_t keyEvent)
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
        case KEY_CODE_MENU:
            m_result = true;
            return true;

        case KEY_CODE_UP:
            if (m_selectedItem < (m_itemsNumber - 1))
            {
                m_selectedItem++;
                m_redraw = true;
            }
            return true;

        case KEY_CODE_DOWN:

            if (m_selectedItem > 0)
            {
                m_selectedItem--;
                m_redraw = true;
            }
            return true;

        default:
            return false;
    }
}

void CWidgetButtonsBar::draw()
{
    CST7565Driver::suspendDrawing();

    int16_t x = m_x;
    CST7565Driver::fill(0, 53, 127, 63, CST7565Driver::FILL_OPERATION_ERASE);

    if(m_topLine)
    {
        CST7565Driver::fill(0, 52, 127, 52, CST7565Driver::FILL_OPERATION_FILL);
    }

    if (m_center)
    {
        int16_t itemsWidth = 0;
        for (int8_t i = 0; i < m_itemsNumber; i++)
        {
            itemsWidth += getTextWidth(i) + 2;
            if (i < (m_itemsNumber - 1))
            {
                itemsWidth += m_distance;
            }
        }
        x = (128 - itemsWidth) / 2;
    }

    for (int8_t i = 0; i < m_itemsNumber; i++)
    {
        int16_t textWidth = getTextWidth(i) + 2;

        if (m_focus && (m_selectedItem == i))
        {
            CScreen::drawRoundedRectangle(
                    x - 1,
                    m_y,
                    x - 1 + textWidth + 1,
                    m_y + 8,
                    CST7565Driver::FILL_OPERATION_FILL);
        }

        CGraphicFont::drawText( //
                x + 1,
                m_y,
                0,
                0,
                m_items[i],
                NULL,
                CFont::FONT_2,
                CGraphicFont::PR_NORMAL,
                CGraphicFont::AT_LEFT,
                CGraphicFont::MULTILINE_OFF,
                {CST7565Driver::BIT_OPERATION_XOR});

        x += textWidth + m_distance;
    }

    CST7565Driver::resumeDrawing();
}

int16_t CWidgetButtonsBar::getTextWidth(int8_t item)
{
    return CGraphicFont::getTextWidth(m_items[item], NULL, CFont::FONT_2, CGraphicFont::PR_NORMAL);
}
