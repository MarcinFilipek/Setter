/*
 * pwmController.cpp
 *
 *  Created on: 16 gru 2014
 *      Author: damian
 *     Version: 1.0.0
 */
#include "pwmController.h"

//--------------------------------------------------------------------------------------------------
CPwmController::CPwmController()
//--------------------------------------------------------------------------------------------------
{
    m_userPulseWidth = 0;
    m_maxUserPulseWidthValue = DEFAULT_MAX_USER_PULSE_WIDTH_VALUE;
    m_pwmPeriod = 0;
    m_pulseMaxWidth = 0;
    m_prescaler = 0;
    m_systemClockFrequency = 0;
}

//--------------------------------------------------------------------------------------------------
void CPwmController::init(TInitStruct* initStruct, uint16_t pwmFrequency, uint32_t systemClockFrequency,
        uint16_t maxPulseWidthValue)
//--------------------------------------------------------------------------------------------------
{
    m_pwmPeriod = pwmFrequency;
    m_systemClockFrequency = systemClockFrequency;
    m_maxUserPulseWidthValue = maxPulseWidthValue;

    if (initStruct != &m_initStruct)
    {
        m_initStruct.PWMChannel = initStruct->PWMChannel;
        m_initStruct.TIMx = initStruct->TIMx;
        m_initStruct.TIMx_OCPolarity = initStruct->TIMx_OCPolarity;
        m_initStruct.pin = initStruct->pin;
        m_initStruct.port = initStruct->port;
    }

    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.Pin = m_initStruct.pin;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_LOW;

#ifdef DEF_HAL_F2
    GPIO_InitStruct.Alternate = getAlternate(m_initStruct.TIMx);
#endif
    HAL_GPIO_Init(m_initStruct.port, &GPIO_InitStruct);

    reInitSystemClock(systemClockFrequency);
}

//--------------------------------------------------------------------------------------------------
void CPwmController::reInitSystemClock(uint32_t systemClockFrequency)
//--------------------------------------------------------------------------------------------------
{
    uint16_t dzielnik = 100;
    m_systemClockFrequency = systemClockFrequency;
    m_prescaler = dzielnik - 1;
    m_pulseMaxWidth = (m_systemClockFrequency / m_pwmPeriod / dzielnik);

    m_htim.Instance = m_initStruct.TIMx;
    m_htim.Init.Prescaler = m_prescaler;
    m_htim.Init.CounterMode = TIM_COUNTERMODE_UP;
    m_htim.Init.Period = m_pulseMaxWidth - 1;
    m_htim.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    m_htim.Init.RepetitionCounter = 0;
    HAL_TIM_PWM_Init(&m_htim);

    TIM_OC_InitTypeDef sConfigOC;

    sConfigOC.OCMode = TIM_OCMODE_PWM1;
    sConfigOC.OCPolarity = m_initStruct.TIMx_OCPolarity;
    sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;

    //----------- ustawienia nie ważne dla wywoływanego trybu
    sConfigOC.OCNIdleState = TIM_OCNIDLESTATE_RESET;
    sConfigOC.OCIdleState = TIM_OCIDLESTATE_RESET;
    sConfigOC.OCNPolarity = TIM_OCNPOLARITY_HIGH;
    //-----------

    HAL_TIM_PWM_ConfigChannel(&m_htim, &sConfigOC, (m_initStruct.PWMChannel - 1) << 2);
    HAL_TIM_PWM_Start(&m_htim, (m_initStruct.PWMChannel - 1) << 2);

    setPulseWidthInternal(0);
}

//--------------------------------------------------------------------------------------------------
void CPwmController::setPulseWidth(uint16_t value)
//--------------------------------------------------------------------------------------------------
{
    if (value > m_maxUserPulseWidthValue)
    {
        value = m_maxUserPulseWidthValue;
    }

    m_userPulseWidth = value;

    uint16_t newComputedValue = (uint32_t) m_userPulseWidth * (uint32_t) m_pulseMaxWidth
            / (uint32_t) m_maxUserPulseWidthValue;

    setPulseWidthInternal(newComputedValue);
}

//--------------------------------------------------------------------------------------------------
uint16_t CPwmController::getPulseWidth()
//--------------------------------------------------------------------------------------------------
{
    return m_userPulseWidth;
}

//--------------------------------------------------------------------------------------------------
uint16_t CPwmController::getMaxPulseWidth()
//--------------------------------------------------------------------------------------------------
{
    return m_maxUserPulseWidthValue;
}

//--------------------------------------------------------------------------------------------------
void CPwmController::setFrequency(uint16_t frequency)
//--------------------------------------------------------------------------------------------------
{
	if(m_pwmPeriod != frequency)
	{
		m_pwmPeriod = frequency;
		reInitSystemClock(m_systemClockFrequency);
	}
}

//--------------------------------------------------------------------------------------------------
void CPwmController::setPulseWidthInternal(uint16_t value)
//--------------------------------------------------------------------------------------------------
{
    __HAL_TIM_SetCompare(&m_htim, (m_initStruct.PWMChannel - 1) << 2, value);
}

uint32_t CPwmController::getAlternate(TIM_TypeDef *TIMx)
{
#ifdef DEF_HAL_F2
    if (TIMx == TIM1)
        return GPIO_AF1_TIM1;

    if (TIMx == TIM2)
        return GPIO_AF1_TIM2;

    if (TIMx == TIM3)
        return GPIO_AF2_TIM3;

    if (TIMx == TIM4)
        return GPIO_AF2_TIM4;

    if (TIMx == TIM5)
        return GPIO_AF2_TIM5;

    if (TIMx == TIM8)
        return GPIO_AF3_TIM8;

    if (TIMx == TIM9)
        return GPIO_AF3_TIM9;

    if (TIMx == TIM10)
        return GPIO_AF3_TIM10;

    if (TIMx == TIM11)
        return GPIO_AF3_TIM11;
#endif

    return 0;
}
