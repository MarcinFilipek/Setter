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
	initialization.forceSend();
}

uint32_t MotoCounterSetter::getCounterAddress()
{
	return counterAddress;
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
			uint8_t* dataPtr = parameters[i]->getDataPtr();
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

uint32_t MotoCounterSetter::getNextInspection()
{
	return nextInspection.getData();
}

void MotoCounterSetter::setCurrentCounter(uint32_t value)
{
	currentCounter.setData(value);
}

uint32_t MotoCounterSetter::getCurrentCounter()
{
	return currentCounter.getData();
}

ERecFrameResult MotoCounterSetter::receiveFrame(Wtp3Driver* driver)
{
	uint8_t command = 0;
	uint32_t data = 0;
	while(driver->hasNextCmd())
	{
		driver->readNextCmd(&command, (uint8_t*)&data);
		handlePackage(command, data);
	}
	return REC_FRAME_NO_ANSWER;
}

void MotoCounterSetter::handlePackage(uint8_t command, uint32_t data)
{
	command-=128;
	switch(command)
	{
	case CounterCommand::SET_CURRENT_COUNTER:
	{
		currentCounter.setData(data, false);
		break;
	}
	case CounterCommand::SET_NEXT_INSPECTION:
		nextInspection.setData(data, false);
		break;
	default:
		break;
	}
}

void MotoCounterSetter::sendInitPackage()
{

}
