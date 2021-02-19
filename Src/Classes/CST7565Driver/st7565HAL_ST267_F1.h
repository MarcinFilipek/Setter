/*
 * Cst7565HAL.h
 *
 *  Created on: 28-04-2015
 *      Author: DamianP
 */

#ifndef CST7565HAL_H_
#define CST7565HAL_H_
#include "hal.h"
#include "CController.h"

#define ST7565_PORT_MOSI GPIOA
#define ST7565_BIT_MOSI GPIO_Pin_7

#define ST7565_PORT_SCK GPIOA
#define ST7565_BIT_SCK GPIO_Pin_5

#define ST7565_PORT_CS GPIOA
#define ST7565_BIT_CS GPIO_Pin_4

#define ST7565_PORT_RST GPIOC
#define ST7565_BIT_RST GPIO_Pin_4

#define ST7565_PORT_A0 GPIOC
#define ST7565_BIT_A0 GPIO_Pin_5

#define ST7565_SPI SPI1
#define ST7565_CHANNEL_SPI SPI1
#define ST7565_CHANNEL_RCC_SPI RCC_APB2Periph_SPI1

class CST7565HAL {
public:

	static inline void halInit() {
		GPIO_InitTypeDef GPIO_InitStructure;

		RCC_APB2PeriphClockCmd(ST7565_CHANNEL_RCC_SPI, ENABLE);

		//MOSI - wyjscie
		GPIO_StructInit(&GPIO_InitStructure);
		GPIO_InitStructure.GPIO_Pin = ST7565_BIT_MOSI;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
		//GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
		GPIO_Init(ST7565_PORT_MOSI, &GPIO_InitStructure);

		//SCK - wyjscie
		GPIO_StructInit(&GPIO_InitStructure);
		GPIO_InitStructure.GPIO_Pin = ST7565_BIT_SCK;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
		//GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
		GPIO_Init(ST7565_PORT_SCK, &GPIO_InitStructure);

		//CS - wyjscie
		GPIO_StructInit(&GPIO_InitStructure);
		GPIO_InitStructure.GPIO_Pin = ST7565_BIT_CS;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
		GPIO_Init(ST7565_PORT_CS, &GPIO_InitStructure);

		//RST - wyjscie
		GPIO_StructInit(&GPIO_InitStructure);
		GPIO_InitStructure.GPIO_Pin = ST7565_BIT_RST;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
		GPIO_Init(ST7565_PORT_RST, &GPIO_InitStructure);

		//A0 - wyjscie
		GPIO_StructInit(&GPIO_InitStructure);
		GPIO_InitStructure.GPIO_Pin = ST7565_BIT_A0;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
		GPIO_Init(ST7565_PORT_A0, &GPIO_InitStructure);

		SPI_StructInit(&m_hspi);

		//chipSelectEnable();
		GPIO_ResetBits(ST7565_PORT_CS, ST7565_BIT_CS);

		m_hspi.SPI_Direction = SPI_Direction_1Line_Tx;
		m_hspi.SPI_Mode = SPI_Mode_Master;
		m_hspi.SPI_DataSize = SPI_DataSize_8b;
		m_hspi.SPI_CPOL = SPI_CPOL_High;
		m_hspi.SPI_CPHA = SPI_CPHA_2Edge;
		m_hspi.SPI_NSS = SPI_NSS_Soft;
		m_hspi.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_8;
		m_hspi.SPI_FirstBit = SPI_FirstBit_MSB;

		SPI_Init(ST7565_CHANNEL_SPI, &m_hspi);
		SPI_Cmd(ST7565_CHANNEL_SPI, ENABLE);
		uint8_t data = 0;
		halDeselectChip();
		halSendBytes(&data, sizeof(data)); // wysłanie głupiego bajtu - pierwszy wysłany bajt jakoś przepada dziwnym sposobem
	}

	static inline void halSelectChip() {
		GPIO_ResetBits(ST7565_PORT_CS, ST7565_BIT_CS);
	}

	static inline void halDeselectChip() {
		GPIO_SetBits(ST7565_PORT_CS, ST7565_BIT_CS);
	}

	static inline void halStartReset() {
		GPIO_ResetBits(ST7565_PORT_RST, ST7565_BIT_RST);
	}

	static inline void halStopReset() {
		GPIO_SetBits(ST7565_PORT_RST, ST7565_BIT_RST);
	}

	static inline bool halStartSendingCommand() {
		bool changeWasRequired = false;
		if (GPIO_ReadInputDataBit(ST7565_PORT_A0, ST7565_BIT_A0) != Bit_RESET) {
			GPIO_ResetBits(ST7565_PORT_A0, ST7565_BIT_A0);
			changeWasRequired = true;
		}
		return changeWasRequired;
	}

	static inline bool halStartSendingData() {
		bool changeWasRequired = false;
		if (GPIO_ReadInputDataBit(ST7565_PORT_A0, ST7565_BIT_A0) == Bit_RESET) {
			GPIO_SetBits(ST7565_PORT_A0, ST7565_BIT_A0);
			changeWasRequired = true;
		}
		return changeWasRequired;
	}

	static inline bool halSendBytes(uint8_t* bytes, uint16_t size) {
		for (uint8_t n = 0; n < size; n++) {
			halSendData(bytes[n]);
		}

	}

	static inline void halSendData(uint8_t dana) {
		while (SPI_I2S_GetFlagStatus(ST7565_CHANNEL_SPI, SPI_I2S_FLAG_TXE)
				== RESET) {
		}
		SPI_I2S_SendData(ST7565_CHANNEL_SPI, dana);
		while (SPI_I2S_GetFlagStatus(ST7565_CHANNEL_SPI, SPI_I2S_FLAG_TXE)
				== RESET) {
		}
		while (SPI_I2S_GetFlagStatus(ST7565_CHANNEL_SPI, SPI_I2S_FLAG_BSY)
				== SET) {
		}
	}
private:

	static SPI_InitTypeDef m_hspi;
};

#endif /* CST7565HAL_H_ */
