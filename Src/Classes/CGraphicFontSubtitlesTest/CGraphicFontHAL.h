/*
 * CGraphicFontHAL.h
 *
 *  Created on: Nov 18, 2015
 *      Author: krzysiek
 */

#ifndef CGRAPHICFONTHAL_H_
#define CGRAPHICFONTHAL_H_

/**
 * Klasa do samodzielnej implementacji.
 */
#include "TColorDesc.h"

class CGraphicFontHAL
{
public:

    /**
     * Rysowanie pojedynczego znaku na ekranie.
     * @param address Adres obrazka.
     * @param x1 Współrzędna X1.
     * @param y1 Współrzędna Y1.
     * @param COLOR Kolor.
     */
    static void drawImage(uint32_t address, int16_t x1, int16_t y1, const TColorDesc& COLOR);

    /**
     * Pobieranie szerokości znaku.
     * @param address Adres obrazka.
     * @return Szerokość obrazka
     */
    static uint16_t getImageWidth(uint32_t address);
};

#endif /* CGRAPHICFONTHAL_H_ */
