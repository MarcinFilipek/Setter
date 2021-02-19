/*
 * CScreenLogo.h
 *
 *  Created on: Oct 16, 2015
 *      Author: krzysiek
 */

#ifndef CSCREENLOGO_H_
#define CSCREENLOGO_H_

#include "CScreen.h"

class CScreenLogo: public CScreen
{
    CTimer m_timer;
    bool m_timeout;

    uint8_t m_easterEggCounter;

public:
    void init(bool timeout);

public:
    void onStart();
    void onResume();
    void update();
    void onPause();
    void onStop();

public:
    bool onKey(int8_t keyCode, int8_t keyEvent);

private:
    void draw();
};

#endif /* CSCREENLOGO_H_ */
