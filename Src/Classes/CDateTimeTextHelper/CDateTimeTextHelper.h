/*
 * CDateTimeTextHelper.h
 *
 *  Created on: 5 lip 2016
 *      Author: marmur
 */

#ifndef LIBRARIES_PROJECT_CDATETIMETEXTHELPER_CDATETIMETEXTHELPER_H_
#define LIBRARIES_PROJECT_CDATETIMETEXTHELPER_CDATETIMETEXTHELPER_H_

#include "CNapisy.h"

class CDateTimeTextHelper
{
public:

	static CNapisy::TTextId getLongDayNameText(uint8_t weekDay);
	static CNapisy::TTextId getShortDayNameText(uint8_t weekDay);

private:
	static CNapisy::TTextId getDayNameText(uint8_t weekDay, bool shortText);

};

#endif /* LIBRARIES_PROJECT_CDATETIMETEXTHELPER_CDATETIMETEXTHELPER_H_ */
