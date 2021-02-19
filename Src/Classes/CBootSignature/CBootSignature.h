/*
 * CBootSignature.h
 *
 *  Created on: Nov 17, 2015
 *      Author: krzysiek
 */

#ifndef CBOOTSIGNATURE_H_
#define CBOOTSIGNATURE_H_

#include "SVersion.h"

/**
 * Klasa odczytująca informacje zakodowane na końcu obszaru bootloadera.
 */
class CBootSignature
{
    static const uint32_t UNIQUE_ID_OFFSET;
    static const uint32_t FLASH_OFFSET = 0x08000000;

    static const uint32_t SIGNATURE = 0x21b70100;
    static const uint8_t ID_BOARD_VERSION = 1;
    static const uint8_t ID_BOARD_SUBVERSION = 2;
    static const uint8_t ID_CONTROLLER_VERSION = 3;
    static const uint8_t ID_FIRM = 4;
    static const uint8_t ID_BOOTLOADER_VERSION = 5;
    static const uint8_t ID_ADRES = 6;

    uint32_t m_appOffset;

    char stringBuff[5];

public:

    /**
     * Konstruktor.
     * @param appOffset Odstęp pomiędzy początkiem flasha a początkiem programu (maksymalny rozmiar bootloadera).
     */
    CBootSignature(uint32_t appOffset);

    /**
     * Sprawdzanie czy sygnatura jest dostępna.
     * @return
     */
    bool isSignatureAvailable();

    /**
     * Zwraca niestandardową wartość.
     * @param ID ID wartości, większe lub równe 8.
     * @return Wartość.
     */
    int32_t getCustomValue(uint8_t ID);

    /**
     * Zwraca wersje płytki.
     * @return Wersja płytki.
     */
    int32_t getBoardVersion();

    /**
     * Zwraca podwersje płytki.
     * @return Podwersja płytki.
     */
    int32_t getBoardSubversion();

    /**
     * Zwraca numer projektu.
     * @return Numer projektu.
     */
    int32_t getControllerVersion();

    /**
     * Zwraca numer firmy
     * @return Firma.
     */
    int32_t getFirm();

    /**
     * Zwraca wersje bootloadera.
     * @return Wersja bootloadera.
     */
    SVersion getBootloaderVersion();

    /**
     * Pobieranie unikatowego ID procesora.
     * @param buffer Bufor do którego zostanie wpisane ID procesora. Minimalny rozmiar do 12 bajtów.
     * @return Ilość bajtów wpisanych do bufora.
     */
    int8_t getChipID(uint8_t *buffer);


    /**
     * Kowersja wartości zapisanej jako 0-4 bajty na stringa.
     * @param Odczytana wartość
     * @return Wskaźnik do bufora zawierającego.
     */
    char* toString(uint32_t value);

    /**
     * Zwraca adres modulu zapisany w bootloaderze
     * @return adres
     */
    int32_t getAdres();
};

#endif /* CBOOTSIGNATURE_H_ */
