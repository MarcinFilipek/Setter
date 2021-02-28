/*
 * MotoCounterSetter.h
 *
 *  Created on: Dec 29, 2020
 *      Author: marcin
 */

#ifndef CLASSES_MOTOCOUNTERSETTER_MOTOCOUNTERSETTER_H_
#define CLASSES_MOTOCOUNTERSETTER_MOTOCOUNTERSETTER_H_

#include "IWtp3Device.h"

class MotoCounterSetter: public IWtp3Device
{
public:
	MotoCounterSetter(): counterAddress(0), newData(false)
	{
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
		return newData;
	}
	void createFrame(Wtp3Driver* driver);
	ERecFrameResult receiveFrame(Wtp3Driver* driver)
	{
		return REC_FRAME_NO_ANSWER;
	}
	void setCounterAddress(uint32_t adr);
private:
	uint32_t counterAddress;
	bool newData;
};

#endif /* CLASSES_MOTOCOUNTERSETTER_MOTOCOUNTERSETTER_H_ */
