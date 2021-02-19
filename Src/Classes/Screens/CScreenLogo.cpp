/*
 * CScreenLogo.cpp
 *
 *  Created on: Oct 16, 2015
 *      Author: krzysiek
 */

#include "CScreenLogo.h"
#include "common.h"
//#include "CScreenTest.h"

void CScreenLogo::init(bool timeout)
{
    m_timeout = timeout;
}

void CScreenLogo::onStart()
{
    if (m_timeout)
    {
        m_timer.start(10);
    }
    m_easterEggCounter = 0;
}

void CScreenLogo::onResume()
{
    CScreen::onResume();

    draw();
}

void CScreenLogo::update()
{
    if (m_timer.isElapsed())
    {
        finish();
    }
}

void CScreenLogo::onPause()
{
    CScreen::onPause();
}

void CScreenLogo::onStop()
{
}

bool CScreenLogo::onKey(int8_t keyCode, int8_t keyEvent)
{
    if (keyEvent == KEY_EVENT_UP)
    {
        return false;
    }

    switch (keyCode)
    {
        case KEY_CODE_MENU:
        case KEY_CODE_EXIT:
    		m_easterEggCounter = 0;
            finish();
            return true;

        case KEY_CODE_DOWN:
        {
//        	if(m_easterEggCounter == 3)
//        	{
//            	CScreenTest screen;
//                CContext::showScreen(&screen);
//        	}
//        	if(m_easterEggCounter == 10)
//        	{
//        		CGUI::getMelodyPlayer()->play(CMelodyPlayer::MACIEK_SONG, sizeof(CMelodyPlayer::MACIEK_SONG)/sizeof(CMelodyPlayer::MACIEK_SONG[0]));
//        	}
//        	else if(m_easterEggCounter == 11)
//        	{
//        		CGUI::getMelodyPlayer()->play(CMelodyPlayer::MARIO_BROS, sizeof(CMelodyPlayer::MARIO_BROS)/sizeof(CMelodyPlayer::MARIO_BROS[0]));
//        	}
//        	else if(m_easterEggCounter == 12)
//        	{
//        		CGUI::getMelodyPlayer()->play(CMelodyPlayer::MARIO_BROS_UNDERWORLD, sizeof(CMelodyPlayer::MARIO_BROS_UNDERWORLD)/sizeof(CMelodyPlayer::MARIO_BROS_UNDERWORLD[0]));
//        	}
    		m_easterEggCounter = 0;
        }
        return true;

        case KEY_CODE_UP:
        {
        	m_easterEggCounter++;
        }
        return true;

        default:
            return false;
    }
}

void CScreenLogo::draw()
{
    CST7565Driver::suspendDrawing();
    CST7565Driver::clear();

    int32_t firmID = FIRMA_ELIAS;

    char buffer[16];

    CImgData::TImgAddress logo = CImgData::IMG_LOGO_TECH;
    uint8_t posY = 15;

    if(firmID == FIRMA_ELIAS)
    {
    	logo = CImgData::IMG_LOGO_ELIAS_DUZE;
    	posY = 5;
    }

	CST7565Driver::imgBitBltCenterBox(0, posY, 127, 0, logo, CST7565Driver::BIT_OPERATION_OR);

	CST7565Driver::fill(0, 47, 127, 47, CST7565Driver::FILL_OPERATION_FILL);

    	snprintf(buffer, sizeof(buffer), "RP-5");

	CGraphicFont::drawText( //
			20,
			51,
			50,
			60,
			0,
			buffer,
			CFont::FONT_1,
			CGraphicFont::PR_NORMAL,
			CGraphicFont::AT_CENTER,
			CGraphicFont::MULTILINE_OFF,
			{CST7565Driver::BIT_OPERATION_OR});

	sprintf(buffer, "%d.%d.%d",1, 2, 3);

	CGraphicFont::drawText(
			55,
			51,
			127,
			60,
			0,
			buffer,
			CFont::FONT_1,
			CGraphicFont::PR_NORMAL,
			CGraphicFont::AT_CENTER,
			CGraphicFont::MULTILINE_OFF,
			{CST7565Driver::BIT_OPERATION_OR});

    CST7565Driver::resumeDrawing();
}
