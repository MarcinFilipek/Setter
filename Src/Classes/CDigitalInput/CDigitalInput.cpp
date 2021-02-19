/*
 * CDigitalInput.cpp
 *
 *  Created on: 27 cze 2016
 *      Author: marmur
 */

#include "CDigitalInput.h"

CDigitalInput::CDigitalInput() :
        m_GPIOx(NULL), m_GPIO_Pin(0)
{
}

void CDigitalInput::init(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, int8_t pushPull, bool invert)
{
    m_GPIOx = GPIOx;
    m_GPIO_Pin = GPIO_Pin;
    m_invert = invert;

    GPIO_InitTypeDef GPIO_InitStruct;

    GPIO_InitStruct.Pin = m_GPIO_Pin;
    GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;

    if (pushPull < 0)
        GPIO_InitStruct.Pull = GPIO_PULLDOWN;
    if (pushPull == 0)
        GPIO_InitStruct.Pull = GPIO_NOPULL;
    if (pushPull > 0)
        GPIO_InitStruct.Pull = GPIO_PULLUP;

    HAL_GPIO_Init(m_GPIOx, &GPIO_InitStruct);
}

bool CDigitalInput::isOn()
{
    return (HAL_GPIO_ReadPin(m_GPIOx, m_GPIO_Pin) == GPIO_PIN_SET) != m_invert;
}
