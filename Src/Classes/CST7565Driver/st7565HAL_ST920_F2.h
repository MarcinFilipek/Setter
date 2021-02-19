/*
 * st7565HAL_ST920_F2.h
 *
 *  Created on: Nov 3, 2015
 *      Author: krzysiek
 */

#ifndef ST7565HAL_ST920_F2_H_
#define ST7565HAL_ST920_F2_H_

#include "stm32f2xx_hal_cortex.h"
#include "stm32f2xx_hal_dma.h"
#include "stm32f2xx_hal_gpio.h"
#include "stm32f2xx_hal_rcc.h"
#include "stm32f2xx_hal_spi.h"

class CST7565HAL
{
    static SPI_HandleTypeDef m_hspi;
    static IRQn_Type m_IRQn;

public:
    static void halInit();

    static inline void halSelectChip()
    {
        if (m_IRQn != 0)
        {
            HAL_NVIC_DisableIRQ(m_IRQn);
        }
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_15, GPIO_PIN_RESET);
    }

    static inline void halDeselectChip()
    {
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_15, GPIO_PIN_SET);
        if (m_IRQn != 0)
        {
            HAL_NVIC_EnableIRQ(m_IRQn);
        }
    }

    static inline void halStartReset()
    {
        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_11, GPIO_PIN_RESET);
    }

    static inline void halStopReset()
    {
        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_11, GPIO_PIN_SET);
    }

    static inline bool halStartSendingCommand()
    {
        bool changeWasRequired = false;
        if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0) == GPIO_PIN_SET)
        {
            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, GPIO_PIN_RESET);
            changeWasRequired = true;
        }
        return changeWasRequired;
    }

    static inline bool halStartSendingData()
    {
        bool changeWasRequired = false;
        if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0) == GPIO_PIN_RESET)
        {
            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, GPIO_PIN_SET);
            changeWasRequired = true;
        }
        return changeWasRequired;
    }

    static inline bool halSendBytes(void* bytes, uint16_t size)
    {
        return (HAL_SPI_Transmit(&m_hspi, (uint8_t*) bytes, size, 50) == HAL_OK);
    }

public:

    /**
     * Ustawianie przerwania które będzie wyłączanie podczas komunikacji przez SPI.
     * @param IRQn
     */
    static void halSetIRQ(IRQn_Type IRQn);

    /**
     * Pobierania struktury SPI_HandleTypeDef.
     * @return
     */
    static SPI_HandleTypeDef *halGetSPIHandle();
};

#endif /* ST7565HAL_ST920_F2_H_ */
