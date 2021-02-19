/*
 * CScreen.h
 *
 *  Created on: Oct 1, 2015
 *      Author: krzysiek
 */

#ifndef GUI_CSCREEN_H_
#define GUI_CSCREEN_H_

#include "CGraphicFont.h"
#include "st7565Driver.h"

#include "AScreen.h"
#include "CContext.h"
#include "IOnKeyListener.h"

#include "CGUI.h"
#include "CImgData.h"
#include "CNapisy.h"
#include "CFont.h"

class CScreen: public AScreen, protected IOnKeyListener
{
    CTimer m_timer;
    int32_t m_actionsCounter;

public:
    void onResume();
    void update();
    void onPause();

public:
    static void drawHeader(uint32_t title, bool thin = false);
    static void drawHeader(uint32_t title, int number, bool thin = false);
    static void drawHeader(IDateTime *dateTime);
    static void drawRoundedRectangle(int16_t x1, int16_t y1, int16_t x2, int16_t y2,
            CST7565Driver::TFillOperation fillOperation = CST7565Driver::FILL_OPERATION_FILL);
};

#endif /* GUI_CSCREEN_H_ */
