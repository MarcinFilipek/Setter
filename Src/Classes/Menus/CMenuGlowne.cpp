/*
 * CMenuGlowne.cpp
 *
 *  Created on: 4 lip 2016
 *      Author: marmur
 */

#include "CMenuGlowne.h"
#include "CScreenMenu.h"
#include "CScreenEnterCode.h"
#include "SVersion.h"
#include "CGUI.h"
#include "Driver.h"

const AMenuList::SMenuItem CMenuGlowne::MENU_ITEMS[] =
{
		{CNapisy::IDT_PAROWANIE},
		{CNapisy::IDT_PRACA},
		{CNapisy::IDT_EDYTUJ},
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
	MotoCounterSetter* motoCounterSetter = Driver::getInstance().getDriverCommunication()->getMotoCounterSetter();
	switch (menuItem->text)
	{
	case CNapisy::IDT_PAROWANIE:
	{
		CScreenEnterCode* screen = new CScreenEnterCode(9);
		screen->init(CNapisy::IDT_ADRES);
		CContext::showScreen(screen);
		int32_t result = 0;
		if(screen->getResult(&result))
		{
			motoCounterSetter->setCounterAddress(result);
		}
		delete screen;
		break;
	}
	case CNapisy::IDT_PRACA:
	{
		CScreenEnterCode* screen = new CScreenEnterCode(3);
		screen->init(CNapisy::IDT_PRACA);
		CContext::showScreen(screen);
		int32_t result = 0;
		if(screen->getResult(&result))
		{
			motoCounterSetter->setNextInspection(result);
		}
		delete screen;
		break;
	}
	case CNapisy::IDT_EDYTUJ:
	{
		CScreenEnterCode* screen = new CScreenEnterCode(4);
		screen->init(CNapisy::IDT_EDYTUJ);
		CContext::showScreen(screen);
		int32_t result = 0;
		if(screen->getResult(&result))
		{
			motoCounterSetter->setCurrentCounter(result);
		}
		delete screen;
		break;
	}
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
