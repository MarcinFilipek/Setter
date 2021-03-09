/*
 * CScreenDevice.cpp
 *
 *  Created on: 10 paz 2019
 *      Author: Michal Gieleciak
 */

#include "CScreenDevice.h"
#include "CMenuGlowne.h"
#include "CScreenMenu.h"
#include "CGUI.h"

CScreenDevice::CScreenDevice() : m_timer(CTimer::UNIT_MILISEC)
{
	m_currentPage = 0;
}

void CScreenDevice::onStart()
{
	m_linkStatus = 0;
}

void CScreenDevice::onResume()
{
    CScreen::onResume();

    draw();
    m_timer.startAligned(2000);
}

void CScreenDevice::update()
{
    if (m_timer.isElapsed())
    {
        resume();
    }

//    CScreenAlarm::updateShow(CGUI::getAlarmController()->getDriver());
}

void CScreenDevice::onPause()
{
    CScreen::onPause();
    finish();
}

void CScreenDevice::onStop()
{
}

bool CScreenDevice::onKey(int8_t keyCode, int8_t keyEvent)
{
    if (keyEvent == KEY_EVENT_UP)
    {
        return false;
    }

    switch (keyCode)
    {
        case KEY_CODE_MENU:
        {
            CMenuGlowne menuList;
            CScreenMenu screenMenu(&menuList);
            CContext::showScreen(&screenMenu);
        }
		return true;

        case KEY_CODE_EXIT:
        {
        }
		return true;

        case KEY_CODE_UP:
		{
			if(m_currentPage==39)
			{
				m_currentPage=0;
			}
			else
			{
				m_currentPage++;
			}
			onResume();

		}
        return true;

        case KEY_CODE_DOWN:
		{
			if(m_currentPage==0)
			{
				m_currentPage=39;
			}
			else
			{
				m_currentPage--;
			}

			onResume();
		}
        return true;

        default:
            return false;
    }
}

void CScreenDevice::draw()
{

//    IDateTime *dateTime = CGUI::getDateTime();

    CST7565Driver::suspendDrawing();
    CST7565Driver::clear();

//    drawHeader(dateTime);

//    char buffer[60];

//    SlaveCommunicator* slave = CGUI::getDriverCommunication()->getSlaveCommunicator();

//    uint16_t startHeight = 19;

    CST7565Driver::fill(1, 52, 126, 52, CST7565Driver::FILL_OPERATION_FILL);

//    char buffer1[32];
//    char m_buffer[32];
//    		CTextResources::copyTextToBuffer(buffer1, CNapisy::IDT_URZADZENIA, 32);
//            snprintf(m_buffer, sizeof(m_buffer), "%s (%d/%d)", buffer1, m_currentPage+1, DevicePool::MAX_DEVICES);
//
//    CGraphicFont::drawText( //
//            0,
//			53,
//			127,
//			63,
//			0,
//			m_buffer,
//            CFont::FONT_1,
//            CGraphicFont::PR_NORMAL,
//            CGraphicFont::AT_CENTER,
//            CGraphicFont::MULTILINE_OFF,
//            {CST7565Driver::BIT_OPERATION_OR});

//    int16_t rssi = CGUI::getDriverCommunication()->getRepeater()->getDevicePool()->getItem(m_currentPage)->getSignal(0);//slave->getRssi();
//    int16_t rssi = 85;
//    int8_t signal = 0;
//
//    if(rssi >= 85)
//    {
//    	signal = 4;
//    }
//    else if(rssi >= 60)
//    {
//    	signal = 3;
//    }
//    else if(rssi >= 40)
//    {
//    	signal = 2;
//    }
//    else if(rssi >= 15)
//    {
//    	signal = 1;
//    }

//    if(CGUI::getDriverCommunication()->getRepeater()->getDevicePool()->getItem(m_currentPage)->hasCommunicationTimeout())
//    {
//    	signal = 0;
//    }
//
//  if(CGUI::getDriverCommunication()->getRepeater()->getDevicePool()->getItem(m_currentPage)->getEndpointAddr(0)==0)
//    {
//        signal = 0;
//    }

//    for (int16_t i = 0; i < 4; i++)
//    {
//        int16_t x1 = 76 + 11 * i;
//        int16_t y1 = 40 - 9 * i;
//        int16_t x2 = x1 + 8;
//        int16_t y2 = 50;
//        if (i < signal)
//        {
//            CST7565Driver::fill(x1, y1, x2, y2, CST7565Driver::FILL_OPERATION_FILL);
//        }
//        else
//        {
//            CST7565Driver::drawRectangle(x1, y1, x2, y2);
//        }
//    }

//    updateLinkAnimation();
//
//    if(slave->hasCommunication())
//    {
//    	CST7565Driver::imgBitBlt(30, 35, CImgData::IMG_COMMUNICATION, CST7565Driver::BIT_OPERATION_OR);
//    }


    CST7565Driver::resumeDrawing();
}

void CScreenDevice::updateLinkAnimation(bool draw)
{
//    static const uint16_t COMMUNICATION[8] = {
//    	CImgData::IMG_COMMUNICATION_0,
//    	CImgData::IMG_COMMUNICATION_1,
//    	CImgData::IMG_COMMUNICATION_2,
//    	CImgData::IMG_COMMUNICATION_3,
//    	CImgData::IMG_COMMUNICATION_0,
//    	CImgData::IMG_COMMUNICATION_3,
//    	CImgData::IMG_COMMUNICATION_2,
//    	CImgData::IMG_COMMUNICATION_1,
//    };
//
//    static const uint16_t NOT_REGISTERED[2] = {
//    	CImgData::IMG_COMMUNICATION_EMPTY,
//		CImgData::IMG_NOT_REGISTERED
//    };
//
//    static const uint16_t NO_COMMUNICATION[2] = {
//		CImgData::IMG_COMMUNICATION_EMPTY,
//		CImgData::IMG_NO_COMMUNICATION
//    };


//    uint32_t status = CNapisy::IDT_PRACA;
//    if(CGUI::getDriverCommunication()->getRepeater()->getDevicePool()->getItem(m_currentPage)->getEndpointAddr(0)==0)
//    {
//  		status = CNapisy::IDT_NIEZAREJESTROWANY;
//    }
//    if(CGUI::getDriverCommunication()->getRepeater()->getDevicePool()->getItem(m_currentPage)->hasCommunicationTimeout())
//    {
//               status = CNapisy::IDT_BRAK_KOMUNIKACJI;
//    }

//    if(m_linkStatus != status)
//    {
//    	m_linkAnimationFrame = 0;
//    	m_linkStatus = status;
//    }
//
//    if(draw)
//    {
//        CST7565Driver::suspendDrawing();
//    	uint32_t img = CImgData::IMG_NULL;
//    	switch(m_linkStatus)
//    	{
//    		case CNapisy::IDT_NIEZAREJESTROWANY:
//    		{
//    			img = NOT_REGISTERED[m_linkAnimationFrame];
//    			if(m_linkAnimationFrame == 0)
//    			{
//    				m_linkAnimationFrame++;
//    			}
//    			else
//    			{
//    				m_linkAnimationFrame = 0;
//    			}
//    		}
//    		break;
//
//    		case CNapisy::IDT_BRAK_KOMUNIKACJI:
//    		{
//    			img = NO_COMMUNICATION[m_linkAnimationFrame];
//    			if(m_linkAnimationFrame == 0)
//    			{
//    				m_linkAnimationFrame++;
//    			}
//    			else
//    			{
//    				m_linkAnimationFrame = 0;
//    			}
//    		}
//    		break;
//
//    		case CNapisy::IDT_PRACA:
//    		{
//    			img = COMMUNICATION[m_linkAnimationFrame];
//    			if(m_linkAnimationFrame < 7)
//    			{
//    				m_linkAnimationFrame++;
//    			}
//    			else
//    			{
//    				m_linkAnimationFrame = 0;
//    			}
//    		}
//    		break;
//    	}
//
//        CGraphicFont::drawText( //
//                0,
//    			18,
//    			85,
//    			28,
//				status,
//    			0,
//                CFont::FONT_1,
//                CGraphicFont::PR_NORMAL,
//                CGraphicFont::AT_CENTER,
//                CGraphicFont::MULTILINE_CENTER,
//                {CST7565Driver::BIT_OPERATION_OR});
//    	CST7565Driver::imgBitBlt(25, 32, img, CST7565Driver::BIT_OPERATION_OR); //33x15
//        CST7565Driver::resumeDrawing();
//    }
}

void CScreenDevice::drawHeader(IDateTime *dateTime)
{
//    static const uint16_t FIRE[8] = {
//    		CImgData::IMG_HEATING_ANIM_1,
//			CImgData::IMG_HEATING_ANIM_2,
//			CImgData::IMG_HEATING_ANIM_3,
//			CImgData::IMG_HEATING_ANIM_4,
//			CImgData::IMG_HEATING_ANIM_5,
//			CImgData::IMG_HEATING_ANIM_4,
//			CImgData::IMG_HEATING_ANIM_3,
//			CImgData::IMG_HEATING_ANIM_2
//    };
//    static uint8_t animation;
//    char buffer[16];
//
//    CST7565Driver::suspendDrawing();
//
//    CST7565Driver::fill(1, 11, 126, 11, CST7565Driver::FILL_OPERATION_FILL);
//
//    animation++;
//
//    if (CGUI::getDriverPeripherals()->getRelay()->isOn())
//    {
//        CST7565Driver::imgBitBlt(2, 0, FIRE[animation % 8], CST7565Driver::BIT_OPERATION_OR);
//    }
//
//    if(CGUI::getDriverCommunication()->getSlaveCommunicator()->hasCommunication())
//    {
//        CST7565Driver::imgBitBlt(14, 0, CImgData::IMG_COMMUNICATION, CST7565Driver::BIT_OPERATION_OR);
//    }

//    snprintf(
//            buffer,
//            sizeof(buffer),
//            "%02d.%02d.%04d",
//            dateTime->getDay(),
//            dateTime->getMonth(),
//            dateTime->getYear());
//
//    CGraphicFont::drawText(
//            48,
//            2,
//            79,
//            11,
//            0,
//            buffer,
//            CFont::FONT_2,
//            CGraphicFont::PR_NORMAL,
//            CGraphicFont::AT_CENTER,
//            CGraphicFont::MULTILINE_OFF,
//            {CST7565Driver::BIT_OPERATION_XOR});
//
//	snprintf(buffer, sizeof(buffer), "%02d:%02d", dateTime->getHours(), dateTime->getMinutes());
//
//    CGraphicFont::drawText(
//            0,
//            1,
//            122,
//            10,
//            0,
//            buffer,
//            CFont::FONT_1,
//            CGraphicFont::PR_NORMAL,
//            CGraphicFont::AT_RIGHT,
//            CGraphicFont::MULTILINE_OFF,
//            {CST7565Driver::BIT_OPERATION_XOR});
//
//    CST7565Driver::resumeDrawing();
}

