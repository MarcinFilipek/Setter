/*
 * CGraphicFontSubtitlesTest.h
 *
 *  Created on: Oct 14, 2015
 *      Author: krzysiek
 */

#ifndef CGRAPHICFONTSUBTITLESTEST_H_
#define CGRAPHICFONTSUBTITLESTEST_H_

#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

/**
 * Klasa do testowania napisów, pozwala:
 * - określić czy napisy mieszczą się w wyznaczonych polach.
 * - sprawdzić czy wszystkie napisy mają zdefiniowane pola.
 * - czy są dostępne wymagane tłumaczenia.
 * Współpracuje z CGraphicFont i CTextResources.
 * Przed użyciem należy dodać #define SUBTITLES_TEST.
 * Klasa wykorzystuje konsole CrossStudio.
 */
class CGraphicFontSubtitlesTest
{
    friend class CGraphicFont;
    friend class CTextResources;

public:

    /**
     * Struktura informacji o pojedynczym tekście.
     */
    struct SItem
    {
        int32_t address;    //!< Adres w pamięci..
        int8_t fontID;      //!< ID czcionki.
        int16_t width;      //!< Szerokość dostępnego pola.
        int16_t height;     //!< Wysokość dostępnego pola.
        bool multiline;     //!< Czy napis jest wypisywany w wielu liniach.
        int8_t printCase;   //!< Odpowiednik TPrintCase z kalsy CGraphicFont.
    };

private:
    static const int16_t *m_languageVersions;
    static int16_t m_languageVersionsCount;
    static bool m_staticTest;
    static bool m_dynamicTest;
    static bool m_languageTest;
    static int16_t m_minX;
    static int16_t m_maxX;
    static int16_t m_minY;
    static int16_t m_maxY;
    static SItem m_dynamicItems[512];

public:

    /**
     * Ustawianie listy testowanych języków. Funkcje można pominąć, wtedy testowany będzie tylko bieżący język.
     * @param languageVersions Tablica języków.
     * @param languageVersionsCount Rozmiar tablicy języków.
     */
    static void setLanguageVersions(const int16_t *languageVersions, int16_t languageVersionsCount);

    /**
     * Test dynamiczny.
     * Funkcja włącza wypisywania informacji o tekstach które są wyświetlone poprzez klasę CGraphicFont.
     * Informacje są wypisywane w formacie zgodnym z SItem, można je łatwo zastosować do skonstruowania tablicy.
     * Dodatkowo opcjonalie wypisywane są informaje o brakujących tłumaczeniach.
     * @param languageTest Wypisywane informaji o brakujących tłumaczeniach.
     */
    static void startDynamicTest(bool languageTest = true);

    /**
     * Wyłączenie testu dynamicznego.
     */
    static void stopDynamicTest();

    /**
     * Przeprowadzenie testu dla wcześniej zdefiniowanych napisów. Sprawdza czy napisy mieszczą się w polach.
     * Strukture napisów można stworzyć korzystając informacji pochodzących z testu dynamicznego.
     * @param items Tablica z informacjami o tekstach.
     * @param itemsCount Rozmiar tablicy.
     */
    static void startStaticTest(const SItem *items, int16_t itemsCount);

private:
    static void getLabel(int32_t address, char *buffer, int16_t bufferSize);
    static bool updateDynamicBuffer(SItem *item);

private:
    static void drawImage(uint32_t address, int16_t x1, int16_t y1);
    static void drawText(int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint32_t stringAddress, uint16_t fontID,
            int8_t printCase, int8_t alignText, int8_t mulitiline);
    static void startSequentialRead(uint32_t address);
};

#endif /* CGRAPHICFONTSUBTITLESTEST_H_ */
