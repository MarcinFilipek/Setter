/*
 * CTimeFix.h
 *
 *  Created on: May 20, 2015
 *      Author: krzysiek
 */

#ifndef CTIMEFIX_H_
#define CTIMEFIX_H_

#include <time.h>

/**
 * Klasa rozwiązująca problem roku 2038. Przestanie działać w trakcie roku 2106.
 * Czas time_t jest traktowany jako zmienna bez znaku.
 * Daty przed rokiem 1970 nie są obsługiwane.
 */
class CTimeFix
{
public:
    /**
     * Poprawiona funkcja localtime.
     * @param __tp Wskaźnik na liczbę sekund od początku roku 1970.
     * @return Wskaźnik na strukturę tm.
     */
    static tm *localtimeFix(const time_t *__tp);
    /**
     * Poprawiona funkcja mktime.
     * @param __tp  Wskaźnik na strukturę tm.
     * @return Liczba sekund od roku 1970.
     */
    static time_t mktimeFix(tm *__tp);
};

#endif /* CTIMEFIX_H_ */
