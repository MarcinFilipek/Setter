/****************************
 * iTwoLogicalStatesHardware.h
 *
 *  Created on: 16-07-2010
 *      Author: DK
 ****************************/

#ifndef ITWOLOGICALSTATESHARDWARE_H_
#define ITWOLOGICALSTATESHARDWARE_H_

#include "iBoolInterface.h"

/**
 * Sluzy jako interfejs do zalaczania urzadzen dwustanowych. Jej glownym zadaniem
 * jest umozliwienie klasom niestatycznym na korzystanie z dobrodziejstw uzywania
 * wbudowanych adresow portow. Obiekt dziedziczacy po tej klasie bedzie mogl byc
 * przekazany do klasy, ktora bedzie uzywac tylko zalacz i wylacz oraz sprawdzac stan
 * konkretnego portu.
 * Zamiast tego mozna adresy przekazywac przez zmienne, ale to powoduje, ze
 * assembler nie pozwala na uzywanie instrukcji ustawiania pojedynczego bitu
 * i w efekcie nadpisuje caly port.
 */
class ITwoLogicalStatesHardware : public IBoolInterface
{
    public:
    
        void turnOn()
        {
            setState(true);
        }
    
        void turnOff()
        {
            setState(false);
        }
    
        virtual void setState(bool state) = 0;
};

#endif /* ITWOLOGICALSTATESHARDWARE_H_ */
