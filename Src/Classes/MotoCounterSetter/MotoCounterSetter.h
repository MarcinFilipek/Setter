/*
 * MotoCounterSetter.h
 *
 *  Created on: Dec 29, 2020
 *      Author: marcin
 */

#ifndef CLASSES_MOTOCOUNTERSETTER_MOTOCOUNTERSETTER_H_
#define CLASSES_MOTOCOUNTERSETTER_MOTOCOUNTERSETTER_H_

#include "IWtp3Device.h"
#include "ICommVar.h"
#include "CommVar.h"

class MotoCounterSetter: public IWtp3Device
{
public:
	MotoCounterSetter(): counterAddress(123)
	{
		initialization.setCommand(CounterCommand::INITIALIZATION);
		nextInspection.setCommand(CounterCommand::SET_NEXT_INSPECTION);
		currentCounter.setCommand(CounterCommand::SET_CURRENT_COUNTER);
		parameters[0] = &initialization;
		parameters[1] = &nextInspection;
		parameters[2] = &currentCounter;
	}
	virtual ~MotoCounterSetter()
	{
	}
	void init()
	{
	}
	void update()
	{
	}
	uint16_t getDeviceNumber()
	{
		return 1;
	}
	bool sendNeeded()
	{
		for(uint8_t i =0; i<NUM_OF_PARAMS; i++)
		{
			if(parameters[i]->isNewValue())
			{
				return true;
			}
		}
		return false;
	}
	void createFrame(Wtp3Driver* driver);
	ERecFrameResult receiveFrame(Wtp3Driver* driver);
	void setCounterAddress(uint32_t adr);
	uint32_t getCounterAddress();

	void setNextInspection(uint32_t value);
	uint32_t getNextInspection();
	void setCurrentCounter(uint32_t value);
	uint32_t getCurrentCounter();
private:
	uint32_t counterAddress;
	static const uint8_t NUM_OF_PARAMS = 3;
	ICommVar* parameters[NUM_OF_PARAMS];
	CommVar<uint32_t> initialization;
	CommVar<uint32_t> nextInspection;
	CommVar<uint32_t> currentCounter;

	void handlePackage(uint8_t command, uint32_t data);
	void sendInitPackage();
};

#endif /* CLASSES_MOTOCOUNTERSETTER_MOTOCOUNTERSETTER_H_ */
