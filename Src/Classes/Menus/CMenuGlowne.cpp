/*
 * CMenuGlowne.cpp
 *
 *  Created on: 4 lip 2016
 *      Author: marmur
 */

#include "CMenuGlowne.h"
#include "CScreenMenu.h"
#include "SVersion.h"
#include "CGUI.h"

const AMenuList::SMenuItem CMenuGlowne::MENU_ITEMS[] =
{
	{CNapisy::IDT_INFORMACJA_O_PROGRAMIE},
};

CMenuGlowne::CMenuGlowne() :
        AMenuList(CNapisy::IDT_MENU, MENU_ITEMS, sizeof(MENU_ITEMS) / sizeof(MENU_ITEMS[0]))
{
}

void CMenuGlowne::updateItem(SMenuItem *menuItem)
{
	switch (menuItem->text)
	{
		default:
			break;
	}
}

void CMenuGlowne::onItemSelected(SMenuItem* menuItem)
{
	switch (menuItem->text)
	{
		default:
			break;
	}
}

void CMenuGlowne::update()
{
//	Communicator* repeater = CGUI::getDriverCommunication()->getRepeater();
//	if (repeater->getRegistration() != m_prevState)
//	{
//		m_prevState = repeater->getRegistration();
//	    CContext::finishScreen();
//	}
}
