/*
 * AScreen.h
 *
 *  Created on: Sep 30, 2015
 *      Author: krzysiek
 */

#ifndef ASCREEN_H_
#define ASCREEN_H_

#include "IUpdatable.h"
#include <stdint.h>
#include <stdlib.h>

/**
 * Abstrakcyjna klasa ekranu.
 */
class AScreen: public IUpdatable
{
public:

    /**
     * Powoduje zamknięcie ekranu.
     */
    void finish();

    /**
     * Powoduje ponowne wywołanie motody onResume.
     */
    void resume();

public:

    /**
     * Motoda wywoływana jako pierwsza, przed pojawianiem się ekranu.
     * Jest wywoływana tylko raz.
     * Należy w niej np. zainicjować zmienne.
     */
    virtual void onStart();

    /**
     * Motoda wywoływana podczas każdego wyświetlania ekranu. Np.
     * Należy w niej np. narysować stałe elementy grafiki.
     */
    virtual void onResume();

    /**
     * Metoda wywoływana każdorazowo kiedy ekran przestaje być widoczny.
     */
    virtual void onPause();

    /**
     * Motoda wywoływana jako ostatnia, przy zamknięciu ekranu.
     * Jest wywoływana tylko raz.
     */
    virtual void onStop();
};

#endif /* ASCREEN_H_ */
