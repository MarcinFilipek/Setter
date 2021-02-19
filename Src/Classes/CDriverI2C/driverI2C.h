/*
 * CDriverI2C.h
 *
 *  Created on: 14 sty 2015
 *      Author: Sebastian
 *     Version: 1.0.1
 *
 *
 * change log
 * - 1.0.0
 *     - wersja podstawowa
 * - 1.0.1 - 18.06.2016
 *     - dodanie obsługi procesorów F4
 */

#ifndef CDRIVERI2C_H_
#define CDRIVERI2C_H_

#include <stdint.h>

#if !defined DEF_HAL_F1 && !defined DEF_HAL_F2 && !defined DEF_HAL_F4
    #define DEF_HAL_F2
#endif

#ifdef DEF_HAL_F1
	#include "stm32f1xx_hal.h"
    #include "stm32f1xx_hal_dma.h"
    #include "stm32f1xx_hal_i2c.h"
    #include "stm32f1xx_hal_gpio.h"
    #include "stm32f1xx_hal_rcc.h"
#elif defined DEF_HAL_F2
    #include "stm32f2xx_hal_dma.h"
    #include "stm32f2xx_hal_i2c.h"
    #include "stm32f2xx_hal_gpio.h"
    #include "stm32f2xx_hal_rcc.h"
#elif defined DEF_HAL_F4
    #include "stm32f4xx_hal_dma.h"
    #include "stm32f4xx_hal_i2c.h"
    #include "stm32f4xx_hal_gpio.h"
    #include "stm32f4xx_hal_rcc.h"
#endif

/*
 * UWAGA DO STM32F1 - brakuje obsługi DMA i odczyt w pewnym momencie wstrzymuje przerwania w celu uniknięcia
 * błędu procesora
 */
class CDriverI2C
{
public:
	struct TI2CInitParams
	{
		I2C_TypeDef* I2Cx;
		uint32_t ClockSpeed;
		uint32_t OwnAddress;
		uint32_t AddressingMode;
		uint32_t SDAPin;
		GPIO_TypeDef* SDAPort;
		uint32_t SCKPin;
		GPIO_TypeDef* SCKPort;
#ifdef DEF_HAL_F1
		DMA_Channel_TypeDef* DMARx;
		DMA_Channel_TypeDef* DMATx;
		IRQn_Type DMARxIRQ;
		IRQn_Type DMATxIRQ;
#endif
	};
	void init(TI2CInitParams * paramI2c, uint16_t pageSize);
	/**
	 * \brief Zapis bloku danych
	 * \param slaveAddressWrite adres urządzenia
	 * \param address adres docelowy w urządzeniu
	 * \param dataBuffer wskaźnik na bufor danych do zapisu
	 * \param dataLength długość bufora danych do zapisu
	 * \return status operacji
	 */
	uint32_t writeBlock(uint8_t slaveAddressWrite, uint16_t address, void *dataBuffer, uint16_t dataLength);

	uint32_t updateBlock(uint8_t slaveAddressWrite, uint16_t address, void *dataBuffer, uint16_t dataLength);

	/**
	 * \brief Odczyt bloku danych
	 * \param slaveAddressRead adres urządzenia
	 * \param address adres docelowy w urządzeniu
	 * \param dataBuffer wskaźnik na bufor danych w którym zostaną umieszczone odczytanme dane
	 * \param dataLength długość bufora danych
	 * \return status operacji
	 */
	uint32_t readBlock(uint8_t slaveAddressRead, uint16_t address, void *dataBuffer, uint16_t dataLength);

	/**
	 * \brief Zapis pojedyńczego bajtu
	 * \param slaveAddressWrite adres urządzenia
	 * \param address adres docelowy w urządzeniu
	 * \param data dana do zapisu
	 * \return status operacji
	 */
	uint32_t writeByte(uint8_t slaveAddressWrite, uint16_t address, uint8_t data);

	uint32_t updateByte(uint8_t slaveAddressWrite, uint16_t address, uint8_t data);

	/**
	 * \brief Odczyt pojedyńczego bajtu
	 * \param slaveAddressRead adres urządzenia
	 * \param address adres w urządzeniu spod którego zostanie dokonany odczyt
	 * \param data adres zmiennej w której zostanie umieszczona odczytana dana
	 * \return status operacji
	 */
	uint32_t readByte(uint8_t slaveAddressRead, uint16_t address, uint8_t* data);

	/**
	 * \brief Metoda ustawia długość przesyłanego do slave'a adresu w urządzeniu do zapisu bądź odczytu danych. Należy ustawić przed próbą komunikacji z urządzeniem.
	 * \param addrLen adres jedno- lub dwubajtowy
	 */
	void setAddrLen(uint8_t addrLen);
	/**
	 * \brief Metoda ustawia Timeout pojedynczych operacji oczekiwania na flagi biblioteki Hal
	 * \param Timeout czas w ms
	 */
	void setHalTimeout(uint32_t Timeout);

#ifdef DEF_HAL_F1
	void DMARxIrqHandler();
	void DMATxIrqHandler();
#endif

private:
	I2C_HandleTypeDef hi2c;
	uint16_t m_pageSize;
	uint8_t m_internalAdressLenght;
	uint32_t m_HALtimeout;

#ifdef DEF_HAL_F1
	DMA_HandleTypeDef m_dma_RX;
	DMA_HandleTypeDef m_dma_TX;
#endif

};

#endif /* CDRIVERI2C_H_ */
