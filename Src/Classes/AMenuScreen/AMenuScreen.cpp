/*
 * AMenuScreen.cpp
 *
 *  Created on: Oct 1, 2015
 *      Author: krzysiek
 */

#include "AMenuScreen.h"

AMenuScreen::AMenuScreen(AMenuList *menuList, int8_t pageSize) :
        m_menuList(menuList), m_pageSize(pageSize), m_offset(0)
{
}

void AMenuScreen::selectItem(AMenuList::SMenuItem *menuItem)
{
    m_menuList->onItemSelected(menuItem);
}

uint32_t AMenuScreen::getTitle()
{
    return m_menuList->getTitle();
}

void AMenuScreen::setOffset(int8_t offset)
{
    m_offset = offset;
}

int8_t AMenuScreen::getOffset()
{
    return m_offset;
}

int8_t AMenuScreen::getItemsCount()
{
    uint8_t count = 0;
    for (int32_t i = 0; i < m_menuList->getMenuItemsCount(); i++)
    {
        if (getItemAtIndex(i)->hidden == false)
        {
            count++;
        }
    }
    return count;
}

int8_t AMenuScreen::getPagesCount()
{
    return (getItemsCount() + (m_pageSize - 1)) / m_pageSize;
}

int8_t AMenuScreen::getSlotsCount()
{
    int8_t count = getItemsCount() - m_offset;
    return count < m_pageSize ? count : m_pageSize;
}

AMenuList::SMenuItem *AMenuScreen::getItemAtSlot(int8_t slot)
{
    return getItemAtIndex(getItemIndex(m_offset + slot));
}

AMenuList::SMenuItem *AMenuScreen::getItemAtIndex(int8_t index)
{
    AMenuList::SMenuItem *menuItem = m_menuList->getMenuItem(index);
    m_menuList->updateItem(menuItem);
    return menuItem;
}

int8_t AMenuScreen::getItemIndex(int8_t position)
{
    uint8_t index = position;
    for (int8_t i = 0; i <= position; i++)
    {
        if (getItemAtIndex(i)->hidden)
        {
            index++;
            position++;
        }
    }
    return index;
}

int8_t AMenuScreen::getItemPosition(int8_t index)
{
    uint8_t position = index;
    for (int8_t i = 0; i < index; i++)
    {
        if (getItemAtIndex(index)->hidden)
        {
            position--;
        }
    }
    return position;
}
