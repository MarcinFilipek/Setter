/*
 * IOnKeyListener.h
 *
 *  Created on: Sep 30, 2015
 *      Author: krzysiek
 */

#ifndef IONKEYLISTENER_H_
#define IONKEYLISTENER_H_

#include <stdint.h>

/**
 * Interfejs dla klas reagujących na zdarzenia związane z przyciskami sprzętowymi.
 */
class IOnKeyListener
{
public:
    static const int8_t KEY_CODE_MENU = 1;      ///< Kod przycisku MENU.
    static const int8_t KEY_CODE_EXIT = 2;      ///< Kod przycisku WYJŚCIE.
    static const int8_t KEY_CODE_UP = 3;        ///< Kod przycisku GÓRA.
    static const int8_t KEY_CODE_DOWN = 4;      ///< Kod przycisku DOL.

    static const int8_t KEY_EVENT_DOWN = 1;     ///< Zdarzenia naciścięcia przycisku.
    static const int8_t KEY_EVENT_UP = 2;       ///< Zdarzenia zwolnienia przycisku.
    static const int8_t KEY_EVENT_PRESSED = 3;  ///< Zdarzenia zwolnienia przycisku.

public:

    /**
     * Metoda wywoływana w ramach reakcji na zdarzenie związene z przyciskami sprzętowymi.
     * @param keyCode Kod przycisku.
     * @param keyEvent Zdarzenie.
     * @return True - zdarzenie obsłużone. Flase - zdarzenie zostanie przekazane dalej.
     */
    virtual bool onKey(int8_t keyCode, int8_t keyEvent) = 0;
};

#endif /* IONKEYLISTENER_H_ */
