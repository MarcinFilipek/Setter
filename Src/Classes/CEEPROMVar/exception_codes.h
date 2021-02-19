/*
 * exception_codes.h
 *
 *  Created on: 3 gru 2013
 *      Author: sporysz
 */

#ifndef EXCEPTION_CODES_H_
#define EXCEPTION_CODES_H_


/**
 * \brief Typ deklarujący wszystkie możliwe kody sytuacji wyjątkowych.
 * \b Każdy element enuma należy udokumentować doxygenem.
 */
typedef enum
{
    EC_EEPROMVAR_HEAP_ALLOCATION_FAIL, ///< Błąd alokacji obieku CEEPROMVar na stercie, występuje przy używaniu klasy tablicowej CEEPROMArr.
    EC_EEPROMVAR_END_OF_BLOCK,         ///< Blok przydzielony w CEEPROMVarConf.h jest zbyt mały aby pomieścić wszystkie zmienne.
    EC_CTIMERS_TIMER_REG_ERROR,        ///< Błąd rejestracji timera.
    EE_MEMORYMANAGER_END_OF_BLOCK,     ///< Rozmiar ustalony poprzez #define CMEMORYMANAGER_SIZE jest zbyt mały.
    EE_REMOTEPARAMETER_RELATIONS_FAIL, ///< Błąd przypisywania parametrów, prawdopodobnie metoda addChild() został niepoprawnie zastosowania.
    EE_PARAMETERSMANAGER_FAIL,         ///< Błąd w menadżerze parametrów, prawdopodobnia próba dodania duplikat ID lub parametru.
}TExceptionCode;


#endif /* EXCEPTION_CODES_H_ */
