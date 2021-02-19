/*
 * CScreenMenu.cpp
 *
 *  Created on: Sep 30, 2015
 *      Author: krzysiek
 */

#include "CScreenMenu.h"

CScreenMenu::CScreenMenu(AMenuList *menuList) :
        AMenuScreen(menuList, PAGE_SIZE), m_timeout(true)
{
}

void CScreenMenu::setTimeout(bool timeout)
{
    m_timeout = timeout;
}

void CScreenMenu::onStart()
{
    m_slot = 0;
}

void CScreenMenu::onResume()
{
    char buffer[32];

    CScreen::onResume();

    CST7565Driver::suspendDrawing();
    CST7565Driver::clear();

    drawHeader(getTitle());

//  SCROLL
    int16_t scrollFieldX = 118;
    int16_t scrollFieldY = 17;
    int16_t currSliderOffsetY = (28 * (getOffset() + m_slot)) / (getItemsCount() - 1);
    CST7565Driver::imgBitBlt(
            scrollFieldX + 3,
            scrollFieldY,
            CImgData::IMG_MALY_TROJKAT_GORA,
            CST7565Driver::BIT_OPERATION_OR);
    CST7565Driver::imgBitBlt(
            scrollFieldX + 3,
            scrollFieldY + 31 + 7,
            CImgData::IMG_MALY_TROJKAT_DOL,
            CST7565Driver::BIT_OPERATION_OR);
    CST7565Driver::fill(
            scrollFieldX + 4,
            scrollFieldY + 4,
            scrollFieldX + 6,
            scrollFieldY + 5 + 31,
            CST7565Driver::FILL_OPERATION_ERASE);
    CST7565Driver::imgBitBlt(
            scrollFieldX + 5,
            scrollFieldY + 5,
            CImgData::IMG_SCROLL_DOT_LINE,
            CST7565Driver::BIT_OPERATION_OR);
    CST7565Driver::imgBitBlt(
            scrollFieldX + 4,
            currSliderOffsetY + scrollFieldY + 5,
            CImgData::IMG_SCROLL_SLIDER,
            CST7565Driver::BIT_OPERATION_OR);

//  ROWS
    int16_t rowPosX = 0;
    int16_t rowPosY = 12;
    int16_t iconPosX = 0;
    int16_t iconPosY = 0;
    int16_t iconFieldWidth = 0;

    for (int8_t i = 0; i < getItemsCount(); i++)
    {
        if (getItemAtIndex(i)->selectable || (getItemAtIndex(i)->icon != 0))
        {
            iconFieldWidth = 12;
            break;
        }
    }

    for (int8_t i = 0; i < getSlotsCount(); i++)
    {
        AMenuList::SMenuItem *menuItem = getItemAtSlot(i);
        if (iconFieldWidth > 0)
        {
            iconPosX = rowPosX + ((iconFieldWidth - 6) >> 1);
            iconPosY = rowPosY + 1;
        }

        if (i == m_slot)
        {
            drawRoundedRectangle(0, 12 + i * 12, (128 - 10 - 1), 12 + (i + 1) * 12);
        }

        uint32_t icon = 0;

        if (menuItem->selectable)
        {
            icon = menuItem->selected ? CImgData::IMG_SELECT_FULL : CImgData::IMG_SELECT_EMPTY;
        }
        else
        {
            icon = menuItem->icon;
        }

        if (icon != 0)
        {
            CST7565Driver::imgBitBlt(iconPosX, iconPosY, icon, CST7565Driver::BIT_OPERATION_XOR);
        }

        uint32_t stringAddress = 0;
        const char* stringPtr = NULL;
        if (menuItem->text < 0x10000)
        {
            stringAddress = menuItem->text;
        }
        else
        {
            strncpy(buffer, (const char*) menuItem->text, sizeof(buffer));
            buffer[sizeof(buffer) - 1] = 0;

            while (true)
            {
                int16_t width = CGraphicFont::getTextWidth(0, buffer, CFont::FONT_1, CGraphicFont::PR_NORMAL);
                if (width <= (116 - (rowPosX + iconFieldWidth + 2)))
                    break;
                buffer[strlen(buffer) - 1] = 0;
            }

            stringPtr = buffer;
        }
        CGraphicFont::drawText(
                rowPosX + iconFieldWidth + 2,
                rowPosY + 1,
                105,
                rowPosY + 12,
                stringAddress,
                stringPtr,
                CFont::FONT_1,
                CGraphicFont::PR_NORMAL,
                CGraphicFont::AT_LEFT,
                CGraphicFont::MULTILINE_OFF,
                {CST7565Driver::BIT_OPERATION_XOR});

        rowPosY += 12;
    }

    CST7565Driver::resumeDrawing();
}

void CScreenMenu::update()
{
    if (m_timeout)
    {
        CScreen::update();
    }
}

void CScreenMenu::onPause()
{
    CScreen::onPause();
}

bool CScreenMenu::onKey(int8_t keyCode, int8_t keyEvent)
{
    if (keyEvent == KEY_EVENT_UP)
    {
        return false;
    }

    switch (keyCode)
    {
        case KEY_CODE_MENU:
            selectItem(getItemAtSlot(m_slot));
            resume();
            return true;

        case KEY_CODE_EXIT:
            finish();
            return true;

        case KEY_CODE_UP:
            if (m_slot > 0)
            {
                m_slot--;
                resume();
            }
            else
            {
                int8_t offset = getOffset();
                if (offset > 0)
                {
                    setOffset(offset - PAGE_SIZE);
                    m_slot = getSlotsCount() - 1;
                    resume();
                }
            }
            return true;

        case KEY_CODE_DOWN:
            if (m_slot + 1 < getSlotsCount())
            {
                m_slot++;
                resume();
            }
            else
            {
                int8_t offset = getOffset();
                if ((offset / PAGE_SIZE) + 1 < getPagesCount())
                {
                    setOffset(offset + PAGE_SIZE);
                    m_slot = 0;
                    resume();
                }
            }
            return true;

        default:
            return false;
    }
}
