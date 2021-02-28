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
public:
	CScreenEnterCode(uint8_t num_digit): NUM_OF_EDIT_NUMBER(num_digit){
		m_widgetEditNumber = new CWidgetEditNumber[NUM_OF_EDIT_NUMBER];
	}
	virtual ~CScreenEnterCode(){
		delete m_widgetEditNumber;
	}
	const uint8_t NUM_OF_EDIT_NUMBER;
private:
    CWidgetButtonsBar m_widgetButtonsBar;
//    CWidgetEditNumber m_widgetEditNumber[NUM_OF_EDIT_NUMBER];
    CWidgetEditNumber* m_widgetEditNumber;
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
