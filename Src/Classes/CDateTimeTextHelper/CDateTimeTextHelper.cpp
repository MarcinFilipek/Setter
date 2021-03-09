/*
 * CDateTimeTextHelper.cpp
 *
 *  Created on: 5 lip 2016
 *      Author: marmur
 */

#include "CDateTimeTextHelper.h"

CNapisy::TTextId CDateTimeTextHelper::getLongDayNameText(uint8_t weekDay)
{
	return getDayNameText(weekDay, false);
}

CNapisy::TTextId CDateTimeTextHelper::getShortDayNameText(uint8_t weekDay)
{
	return getDayNameText(weekDay, true);
}

CNapisy::TTextId CDateTimeTextHelper::getDayNameText(uint8_t weekDay, bool shortText)
{
    switch(weekDay)
    {
//		case 0:
//			return shortText ? CNapisy::IDT_NIEDZIELA_SKROT : CNapisy::IDT_NIEDZIELA;
//		case 1:
//			return shortText ? CNapisy::IDT_PONIEDZIALEK_SKROT : CNapisy::IDT_PONIEDZIALEK;
//		case 2:
//			return shortText ? CNapisy::IDT_WTOREK_SKROT : CNapisy::IDT_WTOREK;
//		case 3:
//			return shortText ? CNapisy::IDT_SRODA_SKROT : CNapisy::IDT_SRODA;
//		case 4:
//			return shortText ? CNapisy::IDT_CZWARTEK_SKROT : CNapisy::IDT_CZWARTEK;
//		case 5:
//			return shortText ? CNapisy::IDT_PIATEK_SKROT : CNapisy::IDT_PIATEK;
//		case 6:
//			return shortText ? CNapisy::IDT_SOBOTA_SKROT : CNapisy::IDT_SOBOTA;
		default:
			return CNapisy::IDT_NULL;
    }
	return CNapisy::IDT_NULL;
}
