/*
 * AMenuScreen.h
 *
 *  Created on: Oct 1, 2015
 *      Author: krzysiek
 */

#ifndef AMENUSCREEN_H_
#define AMENUSCREEN_H_

#include "AMenuList.h"

class AMenuScreen
{
    AMenuList *m_menuList;
    int8_t m_pageSize;
    int8_t m_offset;

protected:

    /**
     *
     * @param menuList
     * @param pageSize
     */
    AMenuScreen(AMenuList *menuList, int8_t pageSize);

    /**
     *
     * @param menuItem
     */
    void selectItem(AMenuList::SMenuItem *menuItem);

    /**
     *
     * @return
     */
    uint32_t getTitle();

    /**
     *
     * @param offset
     */
    void setOffset(int8_t offset);

    /**
     *
     * @return
     */
    int8_t getOffset();

    /**
     *
     * @return Liczba widocznych elementów.
     */
    int8_t getItemsCount();

    /**
     *
     * @return
     */
    int8_t getPagesCount();

    /**
     *
     * @return
     */
    int8_t getSlotsCount();

    /**
     *
     * @param slot
     * @return
     */
    AMenuList::SMenuItem *getItemAtSlot(int8_t slot);

    /**
     *
     * @param index Index elementu.
     * @return Element.
     */
    AMenuList::SMenuItem *getItemAtIndex(int8_t index);

    /**
     *
     * @param position Pozycja elementu.
     * @return Indeks elementu.
     */
    int8_t getItemIndex(int8_t position);

    /**
     *
     * @param index Indeks elementu.
     * @return Pozycja elementu.
     */
    int8_t getItemPosition(int8_t index);
};

#endif /* AMENUSCREEN_H_ */
