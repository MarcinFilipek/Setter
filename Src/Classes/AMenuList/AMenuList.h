/*
 * AMenuList.h
 *
 *  Created on: Sep 30, 2015
 *      Author: krzysiek
 */

#ifndef AMENULIST_H_
#define AMENULIST_H_

#include <stdint.h>
#include <string.h>

class AMenuList
{
public:
    struct SMenuItem
    {
        uint32_t text;
        uint32_t icon;
        bool selectable :1;
        bool selected :1;
        bool hidden :1;
    };

private:
    uint32_t m_title;
    SMenuItem m_menuItems[32];
    uint8_t m_menuItemsCount;

public:
    AMenuList(uint32_t title, const SMenuItem *menuItems, uint8_t menuItemsCount);
    uint32_t getTitle();
    SMenuItem *getMenuItem(int8_t index);
    uint8_t getMenuItemsCount();
    int16_t getItemIndex(SMenuItem *menuItem);

public:
    virtual void updateItem(SMenuItem *menuItem);
    virtual void onItemSelected(SMenuItem *menuItem) = 0 ;
};

#endif /* AMENULIST_H_ */
