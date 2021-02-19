/*
 * CTextResources.h
 *
 *  Created on: Mar 13, 2015
 *      Author: krzysiek
 */

#ifndef CTEXTRESOURCES_H_
#define CTEXTRESOURCES_H_

#include "CTextResourcesHAL.h"

/**
 * CTextResources
 */
class CTextResources: public CTextResourcesHAL
{
    static uint16_t m_languageVersion;
    static uint16_t m_defaultLanguageVersion;

public:

    /**
     * Ustawianie głównej wersji językowej w której będą zwracane napisy.
     * @param languageVersion
     */
    static void setLanguageVersion(uint16_t languageVersion);

    /**
     * Ustawianie zapasowej wersji językowej. Obowiązującej w przypadku braku napisu w głównej wersji językowej.
     * @param defaultLanguageVersion
     */
    static void setDefaultLanguageVersion(uint16_t defaultLanguageVersion);

    /**
     * Pobieranie głównej wersji językowej.
     * @return
     */
    static uint16_t getLanguageVersion();

    /**
     * Pobieranie zapasowej wersji językowej.
     * @return
     */
    static uint16_t getDefaultLanguageVersion();

    /**
     * Konwertowanie tekestu z formatu wchar na UTF-8
     * @param to
     * @param from
     * @return
     */
    static uint16_t copyUtfToWchar(wchar_t* to, const char* from);

    /**
     *
     * @param buff bufor znakow w kodowaniu utf
     * @return ilosc znakow w buforze  (nie jest rowna ilosci bajtow) nie uwzglenia terminujacego nulla
     */
    static uint16_t strlenUtf(const char* buff);

    /**
     * Odczytywanie teksyu do bufora wchar
     * @param outBuffer
     * @param strId
     * @param bufferSize
     * @return
     */
    static int16_t copyTextToBuffer(wchar_t *outBuffer, uint32_t strId, int16_t bufferSize);

    /**
     * Odczytywanie teksyu do bufora UTF-8
     * @param outBuffer
     * @param strId
     * @param bufferSize
     * @return
     */
    static int16_t copyTextToBuffer(char *outBuffer, uint32_t strId, int16_t bufferSize);

    static uint32_t startSequentialRead(uint32_t address);
protected:
    static int8_t readStringLength(uint32_t address, uint16_t *result);
    static uint32_t getCurrentLanguageStringAdress(uint32_t stringAddress);
};

#endif /* CTEXTRESOURCES_H_ */
