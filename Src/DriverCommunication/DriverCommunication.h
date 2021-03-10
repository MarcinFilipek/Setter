/*
 * DriverCommunication.h
 *
 *  Created on: Feb 21, 2021
 *      Author: marcin
 */

#ifndef DRIVERCOMMUNICATION_DRIVERCOMMUNICATION_H_
#define DRIVERCOMMUNICATION_DRIVERCOMMUNICATION_H_

#include "IUpdatable.h"
#include "MotoCounterSetter.h"
#include "wtp3driver.h"

class DriverCommunication: public IUpdatable
{
public:
	DriverCommunication(): address(1){}
	virtual ~DriverCommunication(){}
	void init();
	void update();
	MotoCounterSetter* getMotoCounterSetter()
	{
		return &motoCounterSetter;
	}
	uint32_t getAddress();
private:
	uint32_t address;
	MotoCounterSetter motoCounterSetter;
	IWtp3Device* wtp3Devices[1];
	Wtp3Driver wtp3Driver;

};

#endif /* DRIVERCOMMUNICATION_DRIVERCOMMUNICATION_H_ */
