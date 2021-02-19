/*
 * CGUI.cpp
 *
 *  Created on: 27 cze 2016
 *      Author: marmur
 */

#include "CGUI.h"

#include "st7565Driver.h"
#include "CTextResources.h"
#include "CTimeFix.h"
#include "CGraphicFontSubtitlesTest.h"

#include "CFont.h"
#include "CNapisy.h"

#include "CScreenLogo.h"
#include "CScreenDevice.h"


CGUI::CGUI() : m_softwareVersion(1,0,5)
{
}

CGUI& CGUI::getInstance()
{
	static CGUI instance;
    return instance;
}

CDeviceID *CGUI::getDeviceID()
{
    return m_deviceID;
}

IDateTime *CGUI::getDateTime()
{
    return m_dateTime;
}

CBacklightDriver *CGUI::getBacklightDriver()
{
    return m_backlightDriver;
}

IBuzzer *CGUI::getBuzzer()
{
    return m_buzzer;
}

SVersion *CGUI::getSoftwareVersion()
{
	return &m_softwareVersion;
}


void CGUI::init(IDelayFunctions* delayFunctions, CDeviceID *deviceID, IDateTime *dateTime,
        CBacklightDriver *backlightDriver, IBuzzer *buzzer)
{
    m_deviceID = deviceID;
    m_dateTime = dateTime;
    m_backlightDriver = backlightDriver;
    m_buzzer = buzzer;

    m_contrast.initVar(36);

    CST7565Driver::init(delayFunctions, true);
    CST7565Driver::clear();
    CST7565Driver::ustawKontrast(m_contrast);

    CFont::init();

    m_keyUp.init(GPIOC, GPIO_PIN_5, 1, true);
    m_keyDown.init(GPIOB, GPIO_PIN_1, 1, true);
    m_keyMenu.init(GPIOA, GPIO_PIN_7, 1, true);
    m_keyExit.init(GPIOB, GPIO_PIN_2, 1, true);

    m_damperBoolInterface[0].init(&m_keyUp);
    m_damperBoolInterface[1].init(&m_keyDown);
    m_damperBoolInterface[2].init(&m_keyMenu);
    m_damperBoolInterface[3].init(&m_keyExit);

    m_keyboard.addKey(IOnKeyListener::KEY_CODE_UP, &m_damperBoolInterface[0]);
    m_keyboard.addKey(IOnKeyListener::KEY_CODE_DOWN, &m_damperBoolInterface[1]);
    m_keyboard.addKey(IOnKeyListener::KEY_CODE_MENU, &m_damperBoolInterface[2]);
    m_keyboard.addKey(IOnKeyListener::KEY_CODE_EXIT, &m_damperBoolInterface[3]);
    m_keyboard.setOnKeyListener(this);

    CContext::setKeyboard(&m_keyboard);
    CContext::addUpdatable(this);

    CTextResources::setLanguageVersion(CNapisy::getLanguageVersion( m_language ));
    CContext::redraw();

}

void CGUI::show()
{
    CScreenLogo screenLogo;
    screenLogo.init(true);
    CContext::showScreen(&screenLogo);
    CST7565Driver::clear();
	while (true)
	{
		CScreenDevice screen;
		CContext::showScreen(&screen);
	}
}

int8_t CGUI::getLanguage()
{
	return m_language.getValue();
}

void CGUI::setLanguage(int8_t language)
{
	m_language.setValue( language );
	CTextResources::setLanguageVersion(CNapisy::getLanguageVersion( language ));
}

uint8_t CGUI::getContrast()
{
	return m_contrast.getValue();
}

void CGUI::setContrast(uint8_t contrast)
{
	m_contrast.setValue( contrast );
    CST7565Driver::ustawKontrast(m_contrast);
}

int32_t CGUI::getActionsCounter()
{
    return m_actionsCounter;
}

void CGUI::setDefautls()
{
	setContrast(36);
	m_backlightDriver->setNormalBrightness(CBacklightDriver::DEFAULT_NORMAL_BRIGHTNESS);
	m_backlightDriver->setDimBrightness(CBacklightDriver::DEFAULT_DIM_BRIGHTNESS);
	m_backlightDriver->setFadeTime(CBacklightDriver::DEFAULT_FADE_TIME);
	m_backlightDriver->setLightSensor(CBacklightDriver::DEFAULT_LIGHT_SENSOR);
}

bool CGUI::onKey(int8_t keyCode, int8_t keyEvent)
{
    m_actionsCounter++;

    m_backlightDriver->update(true, false, 0);

    if (keyEvent != IOnKeyListener::KEY_EVENT_DOWN)
    {
        return false;
    }

    m_buzzer->beep(5);

    return true;
}

void CGUI::update()
{
}

