/*
 * CScreenDevice.h
 *
 *  Created on: 10 paz 2019
 *      Author: Michal Gieleciak
 */

#ifndef GUI_SCREENS_CSCREENDEVICE_H_
#define GUI_SCREENS_CSCREENDEVICE_H_

#include "CScreen.h"
#include "timer.h"

class CScreenDevice: public CScreen
{
	CTimer m_timer;

	public:
		CScreenDevice();

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

	private:
	    void updateLinkAnimation(bool draw = true);
	    uint8_t m_linkAnimationFrame;
	    uint32_t m_linkStatus;
	    static void drawHeader(IDateTime *dateTime);

	    uint8_t m_currentPage;
};

#endif /* GUI_SCREENS_CSCREENDEVICE_H_ */
