/*
 * CModulatedBuzzer.h
 *
 *  Created on: 18 sie 2016
 *      Author: marmur
 */

#ifndef LIBRARIES_PROJECT_CMODULATEDBUZZER_CMODULATEDBUZZER_H_
#define LIBRARIES_PROJECT_CMODULATEDBUZZER_CMODULATEDBUZZER_H_

#include "iTwoLogicalStatesHardware.h"
#include "pwmController.h"

#include <stdio.h>

class CModulatedBuzzer: public ITwoLogicalStatesHardware
{
	private:
		CPwmController m_pwmController;

		uint16_t m_maxPulseWidth;
		uint16_t m_divider;

	public:
		CModulatedBuzzer();
		void init(CPwmController::TInitStruct* initStruct, uint16_t pwmFrequency, uint32_t systemClockFrequency, uint16_t maxPulseWidth = 1000);
		void setTone(uint16_t tone);
		void setPulseDivider(uint16_t divider);

	public:
		void setState(bool state);
		bool isOn();
};

#endif /* LIBRARIES_PROJECT_CMODULATEDBUZZER_CMODULATEDBUZZER_H_ */
