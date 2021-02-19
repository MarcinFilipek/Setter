/*
 * CGraphicFont.h
 *
 *  Created on: Mar 4, 2015
 *      Author: krzysiek
 */

#ifndef CGRAPHICFONT_H_
#define CGRAPHICFONT_H_

#include "CGraphicFontHAL.h"

#include <stdint.h>
#include <stdlib.h>

/**
 * Klasa do rysowania tekstu. W celu zastosowanie trzeba dopisać w projekcie dwie brakujące funkcje: drawImage() oraz getImageWidth().
 * Tablice znaków trzeba zdefiniować w projekcie i dodać przez funkcjue addFont()
 */
class CGraphicFont: public CGraphicFontHAL
{
public:

    /**
     * Określanie wielkości znaków.
     * W celu zastosowania należy w tablicy znaków umieścić małe i duże litery naprzemiennie (..., a, A, b, B, c, ...)
     */
    enum TPrintCase
    {
        PR_NORMAL, //!< PR_NORMAL
        PR_UPPER,  //!< PR_UPPER
        PR_LOWER,  //!< PR_LOWER
    };

    /**
     * Wyrównywanie tekstu
     */
    enum TAlignText
    {
        AT_LEFT,    //!< AT_LEFT
        AT_RIGHT,   //!< AT_RIGHT
        AT_CENTER,  //!< AT_CENTER
    };

    /**
     * Dzielenie tekstu na linie.
     * Jeżeli w tekście znajdują się znaki '|' to klasa wykorzystuje je jako miejsca podziału na linie.
     * W przeciwnym wypadku klasa sama dzieli tekst na line w miejscu spacji lub znaku '^'.
     */
    enum TMultiline
    {
        MULTILINE_OFF,      //!< Rysowanie w wielu liniach wyłączone.
        MULTILINE_ON,       //!< Rysowanie w wielu liniach włączone.
        MULTILINE_CENTER,   //!< Rysowanie w wielu liniach włączone, dodatkowo tekst jest wyśrodkowany w pionie.
        MULTILINE_SPACE_SEPARATOR,    //!< Rysowanie w wielu liniach włączone, wymuszone dzielenie tekstu przy kazdej spacji
    };

    /**
     * TImgCharMap
     */
    struct TImgCharMap
    {
        wchar_t charCode;       //!< Znak Unicode
        uint32_t imgAddress;    //!< Adres w pamięci stałej
    };

protected:
    static const uint16_t FONTS_LENGTH = 12;
#ifdef CGRAPHICFONT_STRING_BUFFER_SIZE
    static const uint16_t STRING_BUFFER_SIZE = CGRAPHICFONT_STRING_BUFFER_SIZE;
#else
    static const uint16_t STRING_BUFFER_SIZE = 256;
#endif

    struct SFont
    {
        const TImgCharMap *imgCharMap;
        uint16_t length;
        uint16_t fontID;
        uint16_t fontHeight;
        uint8_t spaceSize;
    };

    static SFont m_fonts[];

public:

    /**
     * Dodawanie czcionki.
     * @param fontID ID czcionki.
     * @param imgCharMap Tablica znaków.
     * @param length Rozmiar tablicy znaków.
     * @param fontHeight Wysokość czcionki.
     * @param spaceSize Odstęp pomiędzy znakami.
     */
    static void addFont(uint16_t fontID, const TImgCharMap *imgCharMap, uint16_t length, uint16_t fontHeight,
            uint8_t spaceSize);

    static int16_t getHeightMultilineText(int16_t posX1, int16_t posY1, int16_t posX2, int16_t posY2, uint32_t strId,
            const char* str, uint16_t fontID, TPrintCase printCase, TAlignText alignText, TMultiline mulitiline,
            const TColorDesc& COLOR);

    /**
     * Metoda rysująca tekst na ekranie.
     * @param x1 Współrzędna X1.
     * @param y1 Współrzędna Y1.
     * @param x2 Współrzędna X2, Parametr wymagany podczas wyrównywania do prawej lub do środka, oraz podczas pisania w wielu linijkach.
     * @param y2 Współrzędna Y2. Parametr wymagany podczas pisania w wielu linijkach.
     * @param stringAddress Adres adresu w pamięci stałej.
     * @param stringPtr Wskaźnik na ciąg znaków w pamięci procesora.
     * @param fontID ID czcionki.
     * @param printCase Wielkość znaków.
     * @param alignText Wyrównywanie tekstu.
     * @param mulitiline Pisanie w wielu linijkach.
     * @param COLOR Kolor.
     * @param jesli true to ignorujemy znaki ^ i | dzieki czemu mozna ladowac dowolne haslo do wifi
     */
    static void drawText(int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint32_t stringAddress, const char* stringPtr,
            uint16_t fontID, TPrintCase printCase, TAlignText alignText, TMultiline mulitiline,
            const TColorDesc& COLOR, bool escaping = false);

    /**
     * Pobieranie wysokości czcionki.
     * @param fontID ID czcionki.
     * @return Wysokość czcionki.
     */
    static int16_t getFontHeight(uint16_t fontID);

    /**
     * Pobieranie odstęp pomiędzy znakami.
     * @param fontID ID czcionki.
     * @return Odstęp pomiędzy znakami.
     */
    static int16_t getSpaceSize(uint16_t fontID);

    /**
     * Pobieranie szerokości napisu.
     * @param stringAddress Adres adresu w pamięci stałej.
     * @param stringPtr Wskaźnik na ciąg znaków w pamięci procesora.
     * @param fontID ID czcionki.
     * @param printCase Wielkość znaków.
     * @return Szerokość napisu.
     */
    static int16_t getTextWidth(uint32_t stringAddress, const char* stringPtr, uint16_t fontID, TPrintCase printCase);

    /**
     * Pobieranie szerokości znaku
     * @param charCode Znak.
     * @param fontID ID czcionki.
     * @param printCase Wielkość znaków.
     * @return Szerokość znaku.
     */
    static int16_t getCharWidth(wchar_t charCode, uint16_t fontID, TPrintCase printCase);

protected:
    static SFont *getFont(uint16_t fontID);

    static wchar_t convertChar(SFont *fontID, wchar_t charCode, TPrintCase printCase);
    static uint32_t getCharImgAddress(SFont *fontID, wchar_t charCode, bool hideHash = false);

    static int16_t drawTextInternall(int16_t posX, int16_t posY, uint32_t strId, const char* str, SFont *font,
            bool getLength, TPrintCase printCase, const TColorDesc& COLOR, bool escaping = false);

    static int16_t drawRamTextInternall(int16_t posX, int16_t posY, wchar_t* str, int16_t startIndex, int16_t endIndex,
            SFont *font, bool getLength, TPrintCase printCase, const TColorDesc& COLOR, bool escaping = false);

    static void drawTextMultiline(int16_t posX1, int16_t posY1, int16_t posX2, int16_t posY2, uint32_t strId,
            const char* str, SFont *font, TPrintCase printCase, TAlignText alignText, TMultiline mulitiline,
            const TColorDesc& COLOR);

    static void createLineBreaks(SFont *font, int16_t maxWidth, int16_t maxHeight, wchar_t* buffer,
            TPrintCase printCase);

    static int16_t getAlignTextPosX(int16_t windowX1, int16_t windowX2, int16_t textWidth, TAlignText alignText);

};

#endif /* CGRAPHICFONT_H_ */
