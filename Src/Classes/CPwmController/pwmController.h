/*
 * pwmController.h
 *
 *  Created on: 16 gru 2014
 *      Author: damian
 *     Version: 1.0.0
 */
#ifndef CLASSES_PWMCONTROLLER_PWMCONTROLLER_H_
#define CLASSES_PWMCONTROLLER_PWMCONTROLLER_H_

#include <stdint.h>

#if !defined DEF_HAL_F1 && !defined DEF_HAL_F2 && !defined DEF_HAL_F4
    #define DEF_HAL_F2
#endif

#ifdef DEF_HAL_F1
	#include "stm32f1xx_hal.h"
	#include "stm32f1xx_hal_dma.h"
	#include "stm32f1xx_hal_gpio.h"
	#include "stm32f1xx_hal_tim.h"
#elif defined DEF_HAL_F2
	#include <stm32f2xx_hal_dma.h>
	#include <stm32f2xx_hal_gpio.h>
	#include <stm32f2xx_hal_tim.h>
	#include <stm32f2xx_hal.h>
#endif

/**
 * UWAGA do F1
 * W HALu od F1 nie ma czegoś takiego jak GPIO_struct.Alternate,
 * gdy chcesz użyc alternatywnego pinu do PWM - czytaj np. @ref __HAL_AFIO_REMAP_TIM2_PARTIAL_2() lub @ref __HAL_AFIO_REMAP_TIM2_PARTIAL_1() dla TIM2
 */

class CPwmController
{
    public:

        static const uint16_t DEFAULT_MAX_USER_PULSE_WIDTH_VALUE = 10000;

        /**
         * \brief Struktura zawierająca podstawowe dane timera, który będzie przekonfigurowywany, gdy
         * zajdzie potrzeba zmiany pwm dla podświetlenia ekranu
         */
        struct TInitStruct
        {
            TIM_TypeDef *TIMx; ///adres pod którym znajduje się timer
            uint8_t PWMChannel; ///numer kanału na który należy puścić sygnał pwm (Podawany jako liczba, czyli: 1, 2, 3 lub 4)
            uint16_t TIMx_OCPolarity; /// polaryzacja
            GPIO_TypeDef *port; ///port na którym znajduje się nóżka od podświetlenia
            uint16_t pin; /// pin na którym znajduje się nóżka od podświetlenia
            bool isAdvancedTimer; /// zbędne
        };

        CPwmController();
        /**
         * \param initStruct struktura inicjalizacyjna dla timera
         * \param pwmFrequency częstotliwość w Hz
         * \param systemClockFrequency częstotliwość zegara taktującego timer
         * \param maxPulseWidthValue maksymalna wartośc jaka reprezentuje 100%
         */
        void init(TInitStruct* initStruct, uint16_t pwmFrequency, uint32_t systemClockFrequency,
                uint16_t maxPulseWidthValue = DEFAULT_MAX_USER_PULSE_WIDTH_VALUE);
        /**
         * Do wywołania po zmianie częstotliwości zegara systemowego
         * \param systemClockFrequency częstotliwość zegara taktującego timer
         */
        void reInitSystemClock(uint32_t systemClockFrequency);
        /**
         *
         * \param value wartość od 0 do wartości zwracanej przez funkcję getPulseWidth()
         */
        void setPulseWidth(uint16_t value);
        uint16_t getPulseWidth();
        /**
         * \return maksymalna wartość jaka może być przekazana do funkcji setPulseWidth
         */
        uint16_t getMaxPulseWidth();

        void setFrequency(uint16_t frequency);

        TInitStruct* getInitStruct() { return &m_initStruct; }

    private:

        uint16_t m_userPulseWidth;
        uint16_t m_maxUserPulseWidthValue;
        uint16_t m_pwmPeriod;
        uint16_t m_pulseMaxWidth;
        uint16_t m_prescaler;
        uint32_t m_systemClockFrequency;

        TIM_HandleTypeDef m_htim;
        TInitStruct m_initStruct;

        void setPulseWidthInternal(uint16_t value);
        static uint32_t getAlternate(TIM_TypeDef *TIMx);
};

#endif /* CLASSES_PWMCONTROLLER_PWMCONTROLLER_H_ */
