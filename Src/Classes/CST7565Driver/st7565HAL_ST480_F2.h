/*
 * st7565HAL_ST480_F2.h
 *
 *  Created on: 30 sty 2015
 *      Author: damian
 *     Version: 1.0.0
 */
#ifndef CLASSES_ST7565DRIVER_ST7565HAL_ST480_F2_H_
#define CLASSES_ST7565DRIVER_ST7565HAL_ST480_F2_H_

#include <stdint.h>
#include "stm32f2xx_hal_dma.h"
#include "stm32f2xx_hal_spi.h"
#include "stm32f2xx_hal_gpio.h"
#include "stm32f2xx_hal_rcc.h"

#define ST7565_PORT_MOSI GPIOB
#define ST7565_BIT_MOSI GPIO_PIN_15

#define ST7565_PORT_SCK GPIOB
#define ST7565_BIT_SCK GPIO_PIN_13

#define ST7565_PORT_CS GPIOB
#define ST7565_BIT_CS GPIO_PIN_12

#define ST7565_PORT_RST GPIOB
#define ST7565_BIT_RST GPIO_PIN_5

#define ST7565_PORT_A0 GPIOD
#define ST7565_BIT_A0 GPIO_PIN_7

#define ST7565_SPI SPI2

class CST7565HAL
{
    public:

        static inline void halInit()
        {
            __SPI2_CLK_ENABLE();
            GPIO_InitTypeDef GPIO_InitStruct;

            __GPIOH_CLK_ENABLE();
            __GPIOB_CLK_ENABLE();
            __GPIOD_CLK_ENABLE();

            /*Configure GPIO pins : PB12 PB5 */
            GPIO_InitStruct.Pin = ST7565_BIT_CS;
            GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
            GPIO_InitStruct.Pull = GPIO_NOPULL;
            GPIO_InitStruct.Speed = GPIO_SPEED_LOW;
            HAL_GPIO_Init(ST7565_PORT_CS, &GPIO_InitStruct);

            GPIO_InitStruct.Pin = ST7565_BIT_RST;
            HAL_GPIO_Init(ST7565_PORT_RST, &GPIO_InitStruct);

            /*Configure GPIO pin : PD7 */
            GPIO_InitStruct.Pin = ST7565_BIT_A0;
            HAL_GPIO_Init(ST7565_PORT_A0, &GPIO_InitStruct);

            GPIO_InitStruct.Pin = ST7565_BIT_SCK;
            GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
            GPIO_InitStruct.Pull = GPIO_NOPULL;
            GPIO_InitStruct.Speed = GPIO_SPEED_LOW;
            GPIO_InitStruct.Alternate = GPIO_AF5_SPI2;
            HAL_GPIO_Init(ST7565_PORT_SCK, &GPIO_InitStruct);

            GPIO_InitStruct.Pin = ST7565_BIT_MOSI;
            HAL_GPIO_Init(ST7565_PORT_MOSI, &GPIO_InitStruct);

            m_hspi.Instance = ST7565_SPI;
            m_hspi.Init.Mode = SPI_MODE_MASTER;
            m_hspi.Init.Direction = SPI_DIRECTION_1LINE;
            m_hspi.Init.DataSize = SPI_DATASIZE_8BIT;
            m_hspi.Init.CLKPolarity = SPI_POLARITY_HIGH;
            m_hspi.Init.CLKPhase = SPI_PHASE_2EDGE;
            m_hspi.Init.NSS = SPI_NSS_SOFT;
            m_hspi.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_16;
            m_hspi.Init.FirstBit = SPI_FIRSTBIT_MSB;
            m_hspi.Init.TIMode = SPI_TIMODE_DISABLED;
            m_hspi.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLED;
            m_hspi.Init.CRCPolynomial = SPI_CRCPR_CRCPOLY;              // potrzebne przy full assert
            HAL_SPI_Init(&m_hspi);
            uint8_t data = 0;
            halDeselectChip();
            halSendBytes(&data, sizeof(data)); // wysłanie głupiego bajtu - pierwszy wysłany bajt jakoś przepada dziwnym sposobem
        }

        static inline void halSelectChip()
        {
            HAL_GPIO_WritePin(ST7565_PORT_CS, ST7565_BIT_CS, GPIO_PIN_RESET);
        }

        static inline void halDeselectChip()
        {
            HAL_GPIO_WritePin(ST7565_PORT_CS, ST7565_BIT_CS, GPIO_PIN_SET);
        }

        static inline void halStartReset()
        {
            HAL_GPIO_WritePin(ST7565_PORT_RST, ST7565_BIT_RST, GPIO_PIN_RESET);
        }

        static inline void halStopReset()
        {
            HAL_GPIO_WritePin(ST7565_PORT_RST, ST7565_BIT_RST, GPIO_PIN_SET);
        }

        static inline bool halStartSendingCommand()
        {
            bool changeWasRequired = false;
            if (HAL_GPIO_ReadPin(ST7565_PORT_A0, ST7565_BIT_A0) == GPIO_PIN_SET)
            {
                HAL_GPIO_WritePin(ST7565_PORT_A0, ST7565_BIT_A0, GPIO_PIN_RESET);
                changeWasRequired = true;
            }
            return changeWasRequired;
        }

        static inline bool halStartSendingData()
        {
            bool changeWasRequired = false;
            if (HAL_GPIO_ReadPin(ST7565_PORT_A0, ST7565_BIT_A0) == GPIO_PIN_RESET)
            {
                HAL_GPIO_WritePin(ST7565_PORT_A0, ST7565_BIT_A0, GPIO_PIN_SET);
                changeWasRequired = true;
            }
            return changeWasRequired;
        }

        static inline bool halSendBytes(void* bytes, uint16_t size)
        {
            return (HAL_SPI_Transmit(&m_hspi, (uint8_t*) bytes, size, 50) == HAL_OK);
        }

    private:

        static SPI_HandleTypeDef m_hspi;
};

#endif /* CLASSES_ST7565DRIVER_ST7565HAL_ST480_F2_H_ */
