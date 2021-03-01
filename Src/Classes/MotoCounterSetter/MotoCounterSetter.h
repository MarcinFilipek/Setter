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
		nextInspection.setCommand(1);
		currentCounter.setCommand(2);
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

	void setNextInspection(uint16_t value);
	void setCurrentCounter(uint16_t value);
private:
	uint32_t counterAddress;
	static const uint8_t NUM_OF_PARAMS = 2;
	ICommVar* parameters[NUM_OF_PARAMS];
	CommVar<uint16_t> nextInspection;
	CommVar<uint16_t> currentCounter;
};

#endif /* CLASSES_MOTOCOUNTERSETTER_MOTOCOUNTERSETTER_H_ */
