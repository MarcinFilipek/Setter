/*
 * CWidgetEditNumber.h
 *
 *  Created on: Oct 12, 2015
 *      Author: krzysiek
 */

#ifndef CWIDGETEDITNUMBER_H_
#define CWIDGETEDITNUMBER_H_

#include "IOnKeyListener.h"

class CWidgetEditNumber: public IOnKeyListener
{
public:
    static const int8_t FLAG_SHOW_ZEROS = 0x01;
    static const int8_t FLAG_SHOW_SIGN = 0x02;

private:
    uint8_t m_x;
    uint8_t m_y;
    int32_t m_value;
    int32_t m_min;
    int32_t m_max;
    int8_t m_digitsNumber;
    int8_t m_flags;
    bool m_focus;
    bool m_redraw;

public:
    void init(uint8_t x, uint8_t y, int32_t value, int32_t min, int32_t max, int8_t digitsNumber, int8_t flags);
    void setFocus(bool focus);
    bool getFocus();
    int32_t getValue();
    void update();
    void redraw();

public:
    bool onKey(int8_t keyCode, int8_t keyEvent);

private:
    void draw();
};

#endif /* CWIDGETEDITNUMBER_H_ */
