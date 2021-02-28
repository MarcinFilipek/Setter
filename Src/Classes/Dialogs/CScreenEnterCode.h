/*
 * CScreenEnterCode.h
 *
 *  Created on: Oct 12, 2015
 *      Author: krzysiek
 */

#ifndef CSCREENENTERCODE_H_
#define CSCREENENTERCODE_H_

#include "CScreen.h"
#include "CWidgetButtonsBar.h"
#include "CWidgetEditNumber.h"

class CScreenEnterCode: public CScreen
{
public:;
	static const uint8_t NUM_OF_EDIT_NUMBER = 9;
private:
    CWidgetButtonsBar m_widgetButtonsBar;
    CWidgetEditNumber m_widgetEditNumber[NUM_OF_EDIT_NUMBER];
    uint32_t m_title;
    int8_t m_pointer;
    bool m_result;

public:
    void init(uint32_t title);
    bool getResult(int32_t *result);

public:
    void onStart();
    void onResume();
    void update();
    void onPause();

public:
    bool onKey(int8_t keyCode, int8_t keyEvent);

};

#endif /* CSCREENENTERCODE_H_ */
