/*
 * eepromFlashSignature.cpp
 *
 *  Created on: 04-07-2012
 *      Author: Marcin Sporysz
 *     Version: 1.0.1
 *
 * change log
 * - 1.0.2 - 18.06.2016
 *     - dodanie obsługi procesorów F4
 */

#ifndef _FLASHSIGNATURE_H_
#define _FLASHSIGNATURE_H_

#include <stdint.h>

/**
 * \brief Klasa umożliwiająca sprawdzenie czy program został uruchomiony po raz pierwszy po programowaniu mikrokontrolera
 */

class CFlashSignature
{
	static const volatile __attribute__ ((section (".text"), used)) uint16_t SIGNATURE;

public:

    /**
     * \brief  Rezultat operacji resetowania.
     */
    enum TFlashUpdResult
    {
        TFUR_SUCCESS,   //!< TFUR_SUCCESS Zapis się powiódł
        TFUR_ERROR,     //!< TFUR_ERROR Błąd zapisu, wymaga dokładniejszego zabadania debuggerem.
        TFUR_ALREADY_SET     //!< TFUR_ALREADY_SET Sygnatura jest juz zresetowana.
    };

    /**
     * \brief Metoda zwraca true jesli sygnatura ma wartość domyślną (lub inną niż 0).
     */
    static bool isFristRun();

    /**
     * \brief Resetuje sygnaturę we flashu.
     * \retval Zwraca błąd typu FLASH_Status jeśli zapis do flasha się nie powdiódł lub zmienna jest już zresetowana.
     */
    static TFlashUpdResult setSignature();

};

#endif //_FLASHSIGNATURE_H_
