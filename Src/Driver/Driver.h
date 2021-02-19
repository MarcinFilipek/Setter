/*
 * Driver.h
 *
 *  Created on: Feb 12, 2021
 *      Author: marcin
 */

#ifndef DRIVER_DRIVER_H_
#define DRIVER_DRIVER_H_

#include "driverI2C.h"
#include "eeprom.h"
#include "CDeviceID.h"
#include "CRTCalendar.h"
#include "CSystem.h"
#include "CBacklightDriver.h"
#include "CModulatedBuzzer.h"
#include "CDriverBuzzerAsync.h"
#include "CDamperBoolInterface.h"
#include "CDigitalInput.h"

class Driver
{
public:
	Driver()
		{
		}
	virtual ~Driver()
	{
	}
	void init();
	static Driver& getInstance();
	CDriverI2C* getI2C(){ return &i2c; }
	CRTCalendar* getRtc(){ return &rtc; }
	CSystem::CDelayFunctions* getDelayFunctions(void)
	{
		return &delayFunctions;
	}
private:
	CDriverI2C i2c;
	Ceeprom eeprom;
	CDeviceID* deviceID;
	CRTCalendar rtc;
	CSystem::CDelayFunctions delayFunctions;
	CBacklightDriver backlightDriver;
	CModulatedBuzzer buzzerHrd;
	CDriverBuzzerAsync buzzerAsync;

	INoneVolatileMem* eepromPtr;
	CDigitalInput m_keyUp;
	CDamperBoolInterface m_damperBoolInterface;

	void initEeprom(void);
	void initRtc(void);
	void initBacklight(void);
	void initBuzzer(void);
};

#endif /* DRIVER_DRIVER_H_ */
