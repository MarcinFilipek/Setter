/*
 * CTextResourcesHAL.h
 *
 *  Created on: Nov 18, 2015
 *      Author: krzysiek
 */

#ifndef CTEXTRESOURCESHAL_H_
#define CTEXTRESOURCESHAL_H_

#include <stdint.h>

/**
 * Klasa do samodzielnej implementacji.
 */
class CTextResourcesHAL
{
public:

    /**
     * Pobieranie danych z pamięci (np. flash)
     * @param address Adres w pamięci w której są przechowywanie napisy.
     * @param buffer Bufor do którego należy skopiować dane.
     * @param size Ilość bajtów do skopiowania.
     */
    static void readData(uint32_t address, void *buffer, int16_t size);
};

#endif /* CTEXTRESOURCESHAL_H_ */
