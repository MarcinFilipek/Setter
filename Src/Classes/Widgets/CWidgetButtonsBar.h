/*
 * CWidgetButtonsBar.h
 *
 *  Created on: Oct 2, 2015
 *      Author: krzysiek
 */

#ifndef CWIDGETBUTTONSBAR_H_
#define CWIDGETBUTTONSBAR_H_

#include "IOnKeyListener.h"

class CWidgetButtonsBar: public IOnKeyListener
{
public:
    static const uint32_t ITEMS_CONFIRM_CANCEL[];
    static const uint32_t ITEMS_CONFIRM_CANCEL_EXIT[];
    static const uint32_t ITEMS_YES_NO[];
    static const uint32_t ITEMS_OK[];
    static const uint32_t ITEMS_ABORT[];
    static const uint32_t ITEMS_DELETE_CANCEL[];
    static const uint32_t ITEMS_EXIT_DELETE[];
    static const uint32_t ITEMS_EXIT_MORE_DELETE[];

private:
    uint8_t m_x;
    uint8_t m_y;
    uint8_t m_distance;
    uint8_t m_itemsNumber;
    const uint32_t *m_items;
    uint8_t m_selectedItem;
    bool m_center;
    bool m_focus;
    bool m_result;
    bool m_redraw;
    bool m_topLine;

public:
    void init(uint8_t x, uint8_t y, const uint32_t *items, int8_t itemsNumber, bool focus = false);
    void setFocus(bool focus);
    bool getFocus();
    bool getResult(int8_t *result);
    void update();
    void redraw();
    void setTopLine(bool visible);
    void setCenter(bool enabled);
    void setPosition(uint8_t x, uint8_t y);

public:
    bool onKey(int8_t keyCode, int8_t keyEvent);

private:
    void draw();
    int16_t getTextWidth(int8_t item);
};

#endif /* CWIDGETBUTTONSBAR_H_ */
