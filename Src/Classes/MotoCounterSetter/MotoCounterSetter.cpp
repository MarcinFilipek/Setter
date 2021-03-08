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
}

void MotoCounterSetter::createFrame(Wtp3Driver* driver)
{
	driver->startFrame(counterAddress, 0x01, 0x01);
	for (uint8_t i = 0; i < NUM_OF_PARAMS; i++)
	{
		if (parameters[i]->isNewValue())
		{
			uint8_t command = parameters[i]->getCommand();
			uint8_t size = parameters[i]->getSize();
			uint8_t* dataPtr = parameters[i]->getData();
			driver->addLongCommand(command, size, dataPtr);
			parameters[i]->clear();
		}
	}
	driver->endFrame();
}

void MotoCounterSetter::setNextInspection(uint32_t value)
{
	nextInspection.setData(value);
}

void MotoCounterSetter::setCurrentCounter(uint32_t value)
{
	currentCounter.setData(value);
}
