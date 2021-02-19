/*
 * CNapisy.h
 *
 *  Created on: Sep 29, 2015
 *      Author: krzysiek
 */

#ifndef CNAPISY_H_
#define CNAPISY_H_

#include <stdint.h>
#include <string.h>

class CNapisy
{
public:
    static const uint8_t FLASH_DATA[];

    static const int8_t JEZYK_POLSKI = 0;
    static const int8_t JEZYK_ANGIELSKI = 1;
    static const int8_t JEZYK_CZESKI = 2;
    static const int8_t JEZYK_SLOWACKI = 3;
    static const int8_t JEZYK_NIEMIECKI = 4;
    static const int8_t JEZYK_WEGIERSKI = 5;
    static const int8_t JEZYK_UKRAINSKI = 6;
    static const int8_t JEZYK_ROSYJSKI = 7;
    static const int8_t JEZYK_FRANCUSKI = 8;
    static const int8_t JEZYK_BULGARSKI = 9;
    static const int8_t JEZYK_LITEWSKI = 10;
    static const int8_t JEZYK_WLOSKI = 11;
    static const int8_t JEZYK_ESTONSKI = 12;
    static const int8_t JEZYK_LOTEWSKI = 13;
    static const int8_t JEZYK_SLOWENSKI = 14;
    static const int8_t JEZYK_HISZPANSKI = 15;
    static const int8_t JEZYK_SZWEDZKI = 16;
    static const int8_t JEZYK_FINSKI = 17;
    static const int8_t JEZYK_GRECKI = 18;
    static const int8_t JEZYK_RUMUNSKI = 19;
    static const int8_t JEZYK_NIDERLANDZKI = 20;
    static const int8_t JEZYK_DUNSKI = 21;
    static const int8_t JEZYK_SERBSKI = 22;
    static const int8_t JEZYK_ALBANSKI = 23;
    static const int8_t JEZYK_MACEDONSKI = 24;
    static const int8_t JEZYK_CHORWACKI = 25;
    static const int8_t JEZYK_CHINSKI = 26;
    static const int8_t JEZYK_MOLDAWSKI = 27;

public:
    typedef enum
    {
#include "textIdEnum.h"
    } TTextId;

public:
    static int8_t getLanguageVersion(uint16_t language);
};

#endif /* CNAPISY_H_ */
