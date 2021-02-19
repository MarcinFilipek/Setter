/*
 * iinterruptupdatable.h
 *
 *  Created on: 21-02-2012
 *      Author: Damian
 */

#ifndef IINTERRUPTUPDATABLE_H_
#define IINTERRUPTUPDATABLE_H_

#include <stdint.h>

/**
 * \brief Pomocnicza klasa abstrakcyjna, która ma za zadanie być pomocą przy konstruowaniu klas,
 * które będą potrzebowały np. odliczania czasu.
 */
class IInterruptUpdatable
{
    public:

        virtual ~IInterruptUpdatable() {};

        /**
         * \brief Funkcja, która ma być wywoływana z przerwania z określoną częstotliwością.
         * \param [in] updateFrequency ilość wywołań tej funkcji na sekundę
         */
        virtual void updateFromInterrupt(uint16_t updateFrequency) = 0;
};

#endif /* IINTERRUPTUPDATABLE_H_ */
