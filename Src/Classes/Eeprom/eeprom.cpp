/*
 * eeprom.cpp
 *
 *  Created on: 08-08-2012
 *      Author: moonwolf
 */

#include "eeprom.h"

Ceeprom::Ceeprom()
{
    i2c = NULL;
    deviceAddress = 0;
}

void Ceeprom::init(CDriverI2C* i2c, uint8_t deviceAddress)
{
    this -> i2c = i2c;
    this -> deviceAddress = deviceAddress;
}

uint32_t Ceeprom::writeBlock(void* eepromAddress, void *dataBuffer, uint16_t dataLength)
{
    i2c -> setAddrLen(2);
    return i2c -> writeBlock(deviceAddress, (uint16_t)(uint32_t) eepromAddress, dataBuffer, dataLength);
}

uint32_t Ceeprom::readBlock(void *eepromAddress, void *dataBuffer, uint16_t dataLength)
{
    i2c -> setAddrLen(2);
    return i2c -> readBlock(deviceAddress, (uint16_t)(uint32_t) eepromAddress, dataBuffer, dataLength);
}

uint32_t Ceeprom::writeByte(void* eepromAddress, uint8_t data)
{
    i2c -> setAddrLen(2);
    return i2c -> writeByte(deviceAddress, (uint16_t) (uint32_t) eepromAddress, data);
}

uint32_t Ceeprom::readByte(void* eepromAddress, uint8_t* data)
{
    i2c -> setAddrLen(2);
    return i2c -> readByte(deviceAddress, (uint16_t) (uint32_t) eepromAddress, data);
}
