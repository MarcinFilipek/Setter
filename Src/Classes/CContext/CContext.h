/*
 * CContext.h
 *
 *  Created on: Sep 30, 2015
 *      Author: krzysiek
 */

#ifndef CCONTEXT_H_
#define CCONTEXT_H_

#include "IOnKeyListener.h"
#include "IUpdatable.h"
#include "AScreen.h"
#include "CKeyboard.h"

#include <string.h>

/**
 * Klasa zarządzająca wyświetlaniem ekranów.
 */
class CContext
{
    static const int8_t MAX_UPDATABLES = 16;
    static const int8_t MAX_ALWAYS_UPDATABLES = 1;
    static const int8_t MAX_SCREENS = 16;
    static const int8_t MAX_KEY_LISTENERS = 16;

    struct SScreenItem
    {
        AScreen *screen;
        int8_t state;
        bool finish;
    };

    static IUpdatable *m_updatables[];
    static IUpdatable *m_alwaysUpdatables[];
    static CKeyboard *m_keyboard;
    static bool m_redraw;
    static bool m_reinit;

    static SScreenItem m_screenItems[];
    static int8_t m_screenItemsCount;

    static IOnKeyListener *m_onKeyListeners[];

public:

#ifdef LOOPCOUNT
    static volatile uint32_t licz;
#endif

    /**
     * Dodanie klasy zawierającej pętle programu.
     * @param updatable Wskaźnik na obiekt klasy implementującej IUpdatable.
     * @param forceAlways flaga określająca czy obiekt ma byc zawsze updateowany, niezależnie od stanu CContext
     */
    static void addUpdatable(IUpdatable *updatable, bool forceAlways = false);

    /**
     * Usunięcie klasy zawierającej pętle programu.
     * @param updatable Wskaźnik na obiekt klasy implementującej IUpdatable.
     * @param fromAlways usuniecie obiektu z listy "always"
     */
    static void removeUpdatable(IUpdatable *updatable, bool fromAlways = false);

    /**
     * Dodanie klawiatury sprzętowej.
     * @param keyboard Wskaźnik na obiekt klawiatury sprzętowej.
     */
    static void setKeyboard(CKeyboard *keyboard);

    /**
     * Wyświetlenie nowego ekranu nad poprzednim ekranem.
     * @param screen Wskaźnik na obiekt ekranu.
     */
    static void showScreen(AScreen *screen);

    /**
     * Zamyka ekran.
     * @param screen Wskaźnik na obiekt ekranu lub NULL (powoduje zamknięcie ostatnio wyświetlonego ekranu).
     */
    static void finishScreen(AScreen *screen = NULL);

    /**
     * Wymusza reinicjalizację obecnie wyświetlanego ekranu
     */
    static void reinitScreen();

    /**
     * Wymusza odrysowanie ekranu.
     */
    static void redraw();

    /**
     * Rejestrowanie IOnKeyListener. Obiekty zarejestrowane później są wywoływane w pierwszej kolejności.
     * @param onKeyListener Wskaźnik na obiekt klasy IOnKeyListener.
     */
    static void registerOnKeyListener(IOnKeyListener *onKeyListener);

    /**
     * Odrejestrowywanie IOnKeyListener.
     * @param onKeyListener Wskaźnik na obiekt klasy IOnKeyListener.
     */
    static void unregisterOnKeyListener(IOnKeyListener *onKeyListener);
};

#endif /* CCONTEXT_H_ */
