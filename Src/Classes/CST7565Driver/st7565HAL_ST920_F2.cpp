/*
 * st7565HAL_ST920_F2.cpp
 *
 *  Created on: Nov 3, 2015
 *      Author: krzysiek
 */

#include "st7565HAL_ST920_F2.h"

SPI_HandleTypeDef CST7565HAL::m_hspi;
IRQn_Type CST7565HAL::m_IRQn;

void CST7565HAL::halInit()
{
    __SPI1_CLK_ENABLE();
    __GPIOA_CLK_ENABLE();
    __GPIOB_CLK_ENABLE();

    GPIO_InitTypeDef GPIO_Init;

    GPIO_Init.Pin = GPIO_PIN_0 | GPIO_PIN_15;
    GPIO_Init.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_Init.Pull = GPIO_NOPULL;
    GPIO_Init.Speed = GPIO_SPEED_LOW;
    HAL_GPIO_Init(GPIOA, &GPIO_Init);

    GPIO_Init.Pin = GPIO_PIN_11;
    HAL_GPIO_Init(GPIOB, &GPIO_Init);

    GPIO_Init.Pin = GPIO_PIN_3 | GPIO_PIN_5;
    GPIO_Init.Mode = GPIO_MODE_AF_PP;
    GPIO_Init.Pull = GPIO_NOPULL;
    GPIO_Init.Speed = GPIO_SPEED_LOW;
    GPIO_Init.Alternate = GPIO_AF5_SPI1;
    HAL_GPIO_Init(GPIOB, &GPIO_Init);

    m_hspi.Instance = SPI1;
    m_hspi.Init.Mode = SPI_MODE_MASTER;
    m_hspi.Init.Direction = SPI_DIRECTION_2LINES;               // Inne urządzenia potrzebują transmisji obustronnej.
    m_hspi.Init.DataSize = SPI_DATASIZE_8BIT;
    m_hspi.Init.CLKPolarity = SPI_POLARITY_LOW;
    m_hspi.Init.CLKPhase = SPI_PHASE_1EDGE;
    m_hspi.Init.NSS = SPI_NSS_SOFT;
    m_hspi.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_16;
    m_hspi.Init.FirstBit = SPI_FIRSTBIT_MSB;
    m_hspi.Init.TIMode = SPI_TIMODE_DISABLED;
    m_hspi.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLED;
    m_hspi.Init.CRCPolynomial = SPI_CRCPR_CRCPOLY;              // potrzebne przy full assert
    HAL_SPI_Init(&m_hspi);

    uint8_t data = 0;
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_15, GPIO_PIN_SET);
    halSendBytes(&data, sizeof(data)); // wysłanie głupiego bajtu - pierwszy wysłany bajt jakoś przepada dziwnym sposobem
}

void CST7565HAL::halSetIRQ(IRQn_Type IRQn)
{
    m_IRQn = IRQn;
}

SPI_HandleTypeDef *CST7565HAL::halGetSPIHandle()
{
    return &m_hspi;
}
