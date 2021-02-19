/*
 * CDamperBoolInterface.h
 *
 *  Created on: Oct 7, 2015
 *      Author: krzysiek
 */

#ifndef CDAMPERBOOLINTERFACE_H_
#define CDAMPERBOOLINTERFACE_H_

#include "iBoolInterface.h"
#include "timer.h"

/**
 * Klasa tłumiąca drgania styków.
 */
class CDamperBoolInterface: public IBoolInterface
{
    static const int8_t MILLISECONDS = 20;

    IBoolInterface *m_boolInterface;
    CTimer m_timer;
    bool m_state;

public:

    /**
     * Inicjalizacja.
     * @param boolInterface Wskaźnik na wejście syganłu.
     */
    void init(IBoolInterface *boolInterface);

public:
    bool isOn();
};

#endif /* CDAMPERBOOLINTERFACE_H_ */
