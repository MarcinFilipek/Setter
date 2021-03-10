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
	MotoCounterSetter(): counterAddress(0)
	{
		nextInspection.setCommand(CounterCommand::NEXT_INSPECTION);
		currentCounter.setCommand(CounterCommand::SET_CURRENT_COUNTER);
		parameters[0] = &nextInspection;
		parameters[1] = &currentCounter;
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
	ERecFrameResult receiveFrame(Wtp3Driver* driver)
	{
		return REC_FRAME_NO_ANSWER;
	}
	void setCounterAddress(uint32_t adr);
	uint32_t getCounterAddress();

	void setNextInspection(uint32_t value);
	void setCurrentCounter(uint32_t value);
private:
	uint32_t counterAddress;
	static const uint8_t NUM_OF_PARAMS = 2;
	ICommVar* parameters[NUM_OF_PARAMS];
	CommVar<uint32_t> nextInspection;
	CommVar<uint32_t> currentCounter;
};

#endif /* CLASSES_MOTOCOUNTERSETTER_MOTOCOUNTERSETTER_H_ */
