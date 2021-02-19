/*
 * eeprom.h
 *
 *  Created on: 08-08-2012
 *      Author: moonwolf
 */

#ifndef __EEPROM_H__
#define __EEPROM_H__

#include "iNoneVolatileMem.h"
#include "driverI2C.h"

/**
 * \brief Klasa służąca do odczytu i zapisu zewnętrznej pamięci eeprom
 */

class Ceeprom : public INoneVolatileMem
{
public:
    Ceeprom();

    /**
     *
     * \param i2c wskaźnik na klasę obsługującą szynę danych (aktualnie tylko I2C)
     * \param deviceAddress adres urządzenia (EEPROMa)
     */
    void init(CDriverI2C* i2c, uint8_t deviceAddress);

    /**
     * \brief Zapis bloku danych
     * \param eepromAddress wskaźnik na adres w EEPROMie
     * \param dataBuffer wskaźnik na bufor danych do zapisu
     * \param dataLength długość bufora danych do zapisu
     * \return status operacji
     */
    uint32_t writeBlock(void* eepromAddress, void* dataBuffer, uint16_t dataLength);

    /**
     * \brief Odczyt bloku danych
     * \param eepromAddress wskaźnik na adres w EEPROMie
     * \param dataBuffer wskaźnik na bufor danych w kŧórym zostaną umieszczone dane odczytane z EEPROMa
     * \param dataLength długość bufora odczytywanych danych
     * \return status operacji
     */
    uint32_t readBlock(void* eepromAddress, void* dataBuffer, uint16_t dataLength);

    /**
     * \brief Zapis pojedyńczego bajtu
     * \param eepromAddress wskaźnik na zmienną w EEPROMie
     * \param data dana do zapisu
     * \return status operacji
     */
    uint32_t writeByte(void* eepromAddress, uint8_t data);

    /**
     * \brief Odczyt pojedyńczego bajtu
     * \param eepromAddress wskaźnik na zmienną w EEPROMie
     * \param data wskaźnik na zmienną w RAMie, w której zostanie umiszczona odczytana dana
     * \return status operacji
     */
    uint32_t readByte(void* eepromAddress, uint8_t* data);

private:
    CDriverI2C* i2c;
    uint8_t deviceAddress;
};

#endif /* CDRIVEREEPROM_H_ */
