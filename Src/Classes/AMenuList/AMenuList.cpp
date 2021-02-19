/*
 * AMenuList.cpp
 *
 *  Created on: Sep 30, 2015
 *      Author: krzysiek
 */

#include "AMenuList.h"

AMenuList::AMenuList(uint32_t title, const SMenuItem *menuItems, uint8_t menuItemsCount) :
        m_title(title), m_menuItemsCount(menuItemsCount)
{
    if (m_menuItemsCount > sizeof(m_menuItems) / sizeof(m_menuItems[0]))
    {
        m_menuItemsCount = sizeof(m_menuItems) / sizeof(m_menuItems[0]);
    }
    if (menuItems != NULL)
    {
        memcpy(m_menuItems, menuItems, m_menuItemsCount * sizeof(SMenuItem));
    }
    else
    {
        memset(m_menuItems, 0, m_menuItemsCount * sizeof(SMenuItem));
    }
}

uint32_t AMenuList::getTitle()
{
    return m_title;
}

AMenuList::SMenuItem *AMenuList::getMenuItem(int8_t index)
{
    return &m_menuItems[index];
}

uint8_t AMenuList::getMenuItemsCount()
{
    return m_menuItemsCount;
}

int16_t AMenuList::getItemIndex(AMenuList::SMenuItem *menuItem)
{
    for (int8_t i = 0; i < m_menuItemsCount; i++)
    {
        if (&m_menuItems[i] == menuItem)
        {
            return i;
        }
    }
    return -1;
}

void AMenuList::updateItem(SMenuItem *menuItem)
{
}
