/*
 * iDelay.h
 *
 *  Created on: 07-07-2011
 *      Author: Damian
 */

#ifndef IDELAY_H_
#define IDELAY_H_

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * \brief Klasa abstrakcyjna, którą należy dodać do klasy implementującej funkcje opóźnień. Dzięki
 * temu można przekazywać ją do wielu innych klas wykorzystujących opóźnienia.
 *
 * Używając tej klasy w crossworks należy zdefiniować funkcję
 * \code
 * extern "C" void __cxa_pure_virtual()
 * {
 *     while (1);
 * }
 * \encode
 */
class IDelayFunctions
{
    public:

        virtual ~IDelayFunctions() {}

        virtual void delayms(uint16_t ms) = 0;
        virtual void delayus(uint16_t ns) = 0;
};

#endif /* IDELAY_H_ */
