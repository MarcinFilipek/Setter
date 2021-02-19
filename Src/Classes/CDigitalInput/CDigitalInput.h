/*
 * CDigitalInput.h
 *
 *  Created on: 27 cze 2016
 *      Author: marmur
 */

#ifndef CDIGITALINPUT_H_
#define CDIGITALINPUT_H_

#include "iBoolInterface.h"

#if !defined DEF_HAL_L0 && !defined DEF_HAL_F1
    #define DEF_HAL_F1
#endif

#ifdef DEF_HAL_F1
	#include "stm32f1xx.h"
	#include "stm32f1xx_hal_gpio.h"
#elif defined(DEF_HAL_L0)
	#include "stm32l0xx_hal.h"
#endif

#include <stdio.h>

class CDigitalInput: public IBoolInterface
{
    GPIO_TypeDef *m_GPIOx;
    uint16_t m_GPIO_Pin;
    bool m_invert;

public:
    CDigitalInput();
    void init(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, int8_t pushPull = 0, bool invert = false);
    bool isOn();
};

#endif /* CDIGITALINPUT_H_ */
