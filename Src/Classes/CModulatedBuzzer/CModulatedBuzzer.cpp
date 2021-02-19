/*
 * CModulatedBuzzer.cpp
 *
 *  Created on: 18 sie 2016
 *      Author: marmur
 */

#include "CModulatedBuzzer.h"


CModulatedBuzzer::CModulatedBuzzer()
{
	m_divider = 2;
	m_maxPulseWidth = 1000;
}

void CModulatedBuzzer::init(CPwmController::TInitStruct* initStruct, uint16_t pwmFrequency, uint32_t systemClockFrequency, uint16_t maxPulseWidth)
{
	m_maxPulseWidth = maxPulseWidth;
	m_pwmController.init(initStruct, pwmFrequency, systemClockFrequency, maxPulseWidth);
}

void CModulatedBuzzer::setTone(uint16_t tone)
{
	m_pwmController.setFrequency(tone);
}


void CModulatedBuzzer::setPulseDivider(uint16_t divider)
{
	if(divider > 0)
	{
		m_divider = divider;
	}
}

void CModulatedBuzzer::setState(bool state)
{
	if(state)
	{
		m_pwmController.setPulseWidth(m_maxPulseWidth/m_divider);
	}
	else
	{
		m_pwmController.setPulseWidth(0);
	}
}

bool CModulatedBuzzer::isOn()
{
	return m_pwmController.getPulseWidth() != 0;
}
