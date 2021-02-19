/*
 * iNoneVolatileMem.h
 *
 *  Created on: 24-08-2011
 *      Author: Damian
 * Modified by: MoonWolf
 */

#ifndef INONEVOLATILEMEM_H_
#define INONEVOLATILEMEM_H_

#include <stdio.h>
#include <stdlib.h> 
#include <stdint.h>

/**
 * \brief Klasa abstrakcyjna, która ma być bazą dla pamięci nieulotnych. Można pod nią podpinać rózne
 * rozwiązania dzięki czemu wykorzystujące ją klasy bedą mogły w sposób niezauważalny zostać przeniesione
 * na całkiem inną pamięć nieulotną.
 */
class INoneVolatileMem
{
public:
    /**
     * \brief Funkcja służąca do zapisu bloku danych do pamięci nieulotnej
     *
     * \param address adres w pamięci nieulotnej od którego zaczyna się dana, która będzie nadpisywana
     * \param dataBuffer wskaźnik na zmienną którą mamy zapisać do pamięci
     * \param dataLength wielkość zmiennej
     */
    virtual uint32_t writeBlock(void* address, void* dataBuffer, uint16_t dataLength) = 0;
    /**
     * \brief Funkcja do odczytu bloku danych z pamięci nieulotnej do pamięci RAM
     *
     * \param address adres w pamięci nieulotnej spod którego ma zostać odcczytany blok danych
     * \param dataBuffer wskaźnik zmiennej w RAMie do której ma być wpisany blok danych
     * \param datalength wielkość zmiennej
     */
    virtual uint32_t readBlock(void* address, void* dataBuffer, uint16_t dataLength) = 0;

    /**
     * \brief Zapis pojedyńczego bajtu
     * \param address wskaźnik na zmienną w pamięci nieulotnej
     * \param data dana do zapisu
     * \return status operacji
     */
    virtual uint32_t writeByte(void* address, uint8_t data) = 0;

    /**
     * \brief Odczyt pojedyńczego bajtu
     * \param address wskaźnik na zmienną w pamięci nieulotnej
     * \param data wskaźnik na zmienną w RAMie, w której zostanie umiszczona odczytana dana
     * \return status operacji
     */
    virtual uint32_t readByte(void* address, uint8_t* data ) = 0;

    virtual ~INoneVolatileMem() {}
};

#endif /* INONEVOLATILEMEM_H_ */
