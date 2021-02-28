/*
 * MotoCounterSetter.cpp
 *
 *  Created on: Dec 29, 2020
 *      Author: marcin
 */

#include "MotoCounterSetter.h"

void MotoCounterSetter::setCounterAddress(uint32_t adr)
{
	counterAddress = adr;
	newData = true;
}

void MotoCounterSetter::createFrame(Wtp3Driver* driver)
{
	driver->startFrame(counterAddress, 0x01, 0x01);
	driver->addShortCommand(33, 55);
	driver->endFrame();
	newData = false;
}

