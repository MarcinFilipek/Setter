/*
 * CKeyboard.h
 *
 *  Created on: Sep 30, 2015
 *      Author: krzysiek
 */

#ifndef CKEYBOARD_H_
#define CKEYBOARD_H_

#include "timer.h"
#include "iBoolInterface.h"
#include "IOnKeyListener.h"

/**
 * Klasa zarządzająca sprzętowymi przyciskami.
 */
class CKeyboard
{
    static const int8_t MAX_KEYS = 8;
    static const int8_t MAX_KEY_EVENTS = 8;

    bool m_keyLastState[MAX_KEYS];

    IBoolInterface *m_keys[MAX_KEYS];
    int8_t m_keyCodes[MAX_KEYS];
    uint16_t m_keyTime[MAX_KEYS];
    uint8_t m_keyRepeats[MAX_KEYS];
    int8_t m_keysCount;

    int8_t m_keyEventsKeyCode[MAX_KEY_EVENTS];
    int8_t m_keyEventsKeyEvent[MAX_KEY_EVENTS];

    CTimer m_timer;
    IOnKeyListener *m_onKeyListener;

public:

    /**
     * Konstruktor
     */
    CKeyboard();

    /**
     * Dodawanie nowego przycisku.
     * @param keyCode Kod przycisku. Podstawowe kody znajdują się w IOnKeyListener.
     * @param boolInterface Wskaźnik na źródło sygnału.
     */
    void addKey(int8_t keyCode, IBoolInterface *boolInterface);

    /**
     * Ustawianie klasy reagującej na zdarzenia związane z przyciskami.
     * Metoda służy tylko do obsługi buzzera, podświetlenia ekranu itp.
     * @param onKeyListener Obiekt klasy IOnKeyListener.
     */
    void setOnKeyListener(IOnKeyListener *onKeyListener);

public:

    /**
     * Metoda do zastosowania wewnętrznego.
     */
    void update();

    /**
     * Metoda do zastosowania wewnętrznego.
     */
    void callKeyEvents(IOnKeyListener *onKeyListener);

    /**
     * Metoda do zastosowania wewnętrznego.
     */
    void clearKeyEvents();
};

#endif /* CKEYBOARD_H_ */
