/*
 * CScreenMenu.h
 *
 *  Created on: Sep 30, 2015
 *      Author: krzysiek
 */

#ifndef CSCREENMENU_H_
#define CSCREENMENU_H_

#include "CScreen.h"
#include "AMenuScreen.h"

#include "timer.h"

class CScreenMenu: public CScreen, AMenuScreen
{
    static const int8_t TIMEOUT = 60;
    static const int8_t PAGE_SIZE = 4;

    bool m_timeout;
    int8_t m_slot;

public:
    CScreenMenu(AMenuList *menuList);
    void setTimeout(bool timeout);

public:
    void onStart();
    void onResume();
    void update();
    void onPause();

public:
    bool onKey(int8_t keyCode, int8_t keyEvent);
};

#endif /* CSCREENMENU_H_ */
