/*
 * CScreen.cpp
 *
 *  Created on: Oct 1, 2015
 *      Author: krzysiek
 */

#include "CScreen.h"
#include "CDateTimeTextHelper.h"

void CScreen::onResume()
{
    CContext::registerOnKeyListener(this);
    m_timer.start(60);
}

void CScreen::update()
{
    int32_t actionsCounter = CGUI::getInstance().getActionsCounter();
    if (m_actionsCounter != actionsCounter)
    {
        m_actionsCounter = actionsCounter;
        m_timer.start(m_timer.getOverallTime());
    }
    if (m_timer.isElapsed())
    {
        finish();
    }
}

void CScreen::onPause()
{
    CContext::unregisterOnKeyListener(this);
}

void CScreen::drawHeader(uint32_t title, bool thin)
{
    CST7565Driver::suspendDrawing();
    CST7565Driver::fill(0, 9, 127, 9, CST7565Driver::FILL_OPERATION_ERASE);
    if(!thin)
    {
        CST7565Driver::fill(0, 10, 127, 10, CST7565Driver::FILL_OPERATION_FILL);
    }
    drawRoundedRectangle(0, 0, 127, 8);
    CGraphicFont::drawText(
            2,
            0,
            126,
            9,
            title,
            0,
            CFont::FONT_2,
            CGraphicFont::PR_UPPER,
            CGraphicFont::AT_LEFT,
            CGraphicFont::MULTILINE_OFF,
            {CST7565Driver::BIT_OPERATION_XOR});
    CST7565Driver::resumeDrawing();
}

void CScreen::drawHeader(uint32_t title, int number, bool thin)
{
    CST7565Driver::suspendDrawing();
    CST7565Driver::fill(0, 9, 127, 9, CST7565Driver::FILL_OPERATION_ERASE);
    if(!thin)
    {
        CST7565Driver::fill(0, 10, 127, 10, CST7565Driver::FILL_OPERATION_FILL);
    }
    drawRoundedRectangle(0, 0, 127, 8);
    CGraphicFont::drawText(
            2,
            0,
            126,
            9,
            title,
            0,
            CFont::FONT_2,
            CGraphicFont::PR_UPPER,
            CGraphicFont::AT_LEFT,
            CGraphicFont::MULTILINE_OFF,
            {CST7565Driver::BIT_OPERATION_XOR});

	char buffer[10];

    snprintf(buffer, sizeof(buffer), "[%d]", number);

    CGraphicFont::drawText(
            2,
            0,
            126,
            9,
            0,
            buffer,
            CFont::FONT_2,
            CGraphicFont::PR_UPPER,
            CGraphicFont::AT_RIGHT,
            CGraphicFont::MULTILINE_OFF,
            {CST7565Driver::BIT_OPERATION_XOR});
    CST7565Driver::resumeDrawing();
}

void CScreen::drawHeader(IDateTime *dateTime)
{
    char buffer[16];

    CST7565Driver::suspendDrawing();
    CST7565Driver::fill(1, 10, 126, 10, CST7565Driver::FILL_OPERATION_FILL);

    CGraphicFont::drawText(
            1,
            1,
            24,
            10,
			CDateTimeTextHelper::getShortDayNameText( dateTime->getWeekDay() ),
            0,
            CFont::FONT_1,
            CGraphicFont::PR_NORMAL,
            CGraphicFont::AT_LEFT,
            CGraphicFont::MULTILINE_OFF,
            {CST7565Driver::BIT_OPERATION_XOR});

    snprintf(
            buffer,
            sizeof(buffer),
            "%02d.%02d.%02d",
            dateTime->getDay(),
            dateTime->getMonth(),
            dateTime->getYear() % 100);

    CGraphicFont::drawText(
            48,
            1,
            79,
            10,
            0,
            buffer,
            CFont::FONT_2,
            CGraphicFont::PR_NORMAL,
            CGraphicFont::AT_CENTER,
            CGraphicFont::MULTILINE_OFF,
            {CST7565Driver::BIT_OPERATION_XOR});

    snprintf(buffer, sizeof(buffer), "%02d:%02d", dateTime->getHours(), dateTime->getMinutes());

    CGraphicFont::drawText(
            0,
            1,
            126,
            10,
            0,
            buffer,
            CFont::FONT_1,
            CGraphicFont::PR_NORMAL,
            CGraphicFont::AT_RIGHT,
            CGraphicFont::MULTILINE_OFF,
            {CST7565Driver::BIT_OPERATION_XOR});

    CST7565Driver::resumeDrawing();
}

void CScreen::drawRoundedRectangle(int16_t x1, int16_t y1, int16_t x2, int16_t y2,
        CST7565Driver::TFillOperation fillOperation)
{
    CST7565Driver::suspendDrawing();
    CST7565Driver::fill(x1, y1 + 1, x1, y2 - 1, fillOperation);
    CST7565Driver::fill(x1 + 1, y1, x2 - 1, y2, fillOperation);
    CST7565Driver::fill(x2, y1 + 1, x2, y2 - 1, fillOperation);
    CST7565Driver::resumeDrawing();
}
