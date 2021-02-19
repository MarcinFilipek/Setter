/*
 * st7565HAL_Flash_Custom.h
 *
 *  Created on: Sep 22, 2015
 *      Author: krzysiek
 */

#ifndef ST7565HAL_FLASH_CUSTOM_H_
#define ST7565HAL_FLASH_CUSTOM_H_

#include <stdint.h>
#include <string.h>

class CST7565_Hal_Flash
{
    static uint32_t m_address;

public:
    static void flashStartReadSequentialBytes(uint32_t address);
    static void flashReadSequentialBytes(uint8_t* outData, uint16_t dataSize);
    static void flashEndReadSequentialBytes();
};

#endif /* ST7565HAL_FLASH_CUSTOM_H_ */

