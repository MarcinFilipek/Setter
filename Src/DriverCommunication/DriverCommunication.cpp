/*
 * DriverCommunication.cpp
 *
 *  Created on: Feb 21, 2021
 *      Author: marcin
 */

#include "DriverCommunication.h"
#include "wtp_address_gen.h"
#include "CContext.h"

void DriverCommunication::init()
{
	wtp3Devices[0] = &motoCounterSetter;
	wtp_address_gen_init();
	uint32_t address = wtp_address_gen_get_address();
	wtp3Driver.init(wtp3Devices, 1, address, 1, RECEIVE_MODE_AFTER_TX, 170);
	CContext::addUpdatable(this);
}

void DriverCommunication::update()
{
	wtp3Driver.update();
}

