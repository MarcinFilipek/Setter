/*
 * CGUI.h
 *
 *  Created on: 27 cze 2016
 *      Author: marmur
 */

#ifndef CGUI_H_
#define CGUI_H_

#include "CBacklightDriver.h"
#include "iDateTime.h"
#include "iDelay.h"
#include "IBuzzer.h"
#include "common.h"

#include "CDeviceID.h"
#include "CDigitalInput.h"
#include "CContext.h"
#include "CKeyboard.h"
#include "CDamperBoolInterface.h"
#include "IUpdatable.h"

#include "CEEPROMVar.h"

class CGUI: IOnKeyListener, IUpdatable
{
public:
    static const int32_t CODE_TEST = 102;
    static const int32_t CODE_SERVICE = 5162;
    static const int32_t CODE_UNLOCK = 6969;
    static const int32_t CODE_REPEATER = 110;
    static const int32_t CODE_NULL_PROTECTION = 3336;
    static const int32_t CODE_SIGNATURE_TECH = 9991;
    static const int32_t CODE_SIGNATURE_ELIAS = 9992;
    static const int32_t CODE_SIGNATURE_ACCEPT = 5151;

private:

    CKeyboard m_keyboard;
    CDigitalInput m_keyUp;
    CDigitalInput m_keyDown;
    CDigitalInput m_keyMenu;
    CDigitalInput m_keyExit;
    CDamperBoolInterface m_damperBoolInterface[4];

    CEEPROMVar<int8_t> 	m_language;
    CEEPROMVar<uint8_t> m_contrast;

    CDeviceID *m_deviceID;
    IDateTime *m_dateTime;
    CBacklightDriver *m_backlightDriver;
    IBuzzer *m_buzzer;

    SVersion m_softwareVersion;

    int32_t m_actionsCounter;

private:
    CGUI();

public:
    static CGUI& getInstance();
	CDeviceID *getDeviceID();
	IDateTime *getDateTime();
	CBacklightDriver *getBacklightDriver();
	IBuzzer *getBuzzer();
	SVersion *getSoftwareVersion();

public:
    void init(IDelayFunctions* delayFunctions, CDeviceID *deviceID, IDateTime *dateTime,
            CBacklightDriver *backlightDriver, IBuzzer *buzzer);
    void show();

    int8_t  getLanguage();
    void	setLanguage(int8_t language);

    uint8_t getContrast();
    void	setContrast(uint8_t contrast);

    int32_t getActionsCounter();

    void setDefautls();

public:
    bool onKey(int8_t keyCode, int8_t keyEvent);

public:
    void update();
};

#endif /* CGUI_H_ */
