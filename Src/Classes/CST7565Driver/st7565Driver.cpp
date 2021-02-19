/*
 * st7565Driver.cpp
 *
 *  Created on: 30 sty 2015
 *      Author: damian
 *     Version: 1.0.0
 */
#include "st7565Driver.h"

IDelayFunctions* CST7565Driver::m_delay = NULL;
uint8_t CST7565Driver::bufor_ekranu[LCD_WIDTH * LCD_HEIGHT / 8];
uint8_t CST7565Driver::m_contrast = 50;

int8_t CST7565Driver::m_iSuspendLayout = 0;

bool CST7565Driver::m_displayRotated = false;

int16_t CST7565Driver::m_iSuspendedAreaX1 = -1;
int16_t CST7565Driver::m_iSuspendedAreaY1 = -1;
int16_t CST7565Driver::m_iSuspendedAreaX2 = -1;
int16_t CST7565Driver::m_iSuspendedAreaY2 = -1;

void CST7565Driver::init(IDelayFunctions* delays, bool displayRotated)
{
    m_delay = delays;

    m_displayRotated = displayRotated;

    halInit();
    reinitInternal(true);
}

void CST7565Driver::reinit()
{
    reinitInternal(false);
}

void CST7565Driver::reinitInternal(bool initial)
{
    halSelectChip();
    halStartReset();
    m_delay->delayms(initial ? 10 : 1);
    halStopReset();

    m_delay->delayms(initial ? 10 : 1);

    uint8_t rozkazy[] = {
        cmd_set_bias_9,
		cmd_set_adc_reverse,
		cmd_set_com_normal,
        cmd_set_disp_start_line,
        cmd_set_power_control | 0x4,
    };

    if(m_displayRotated)
    {
    	rozkazy[1] = cmd_set_adc_normal;
    	rozkazy[2] = cmd_set_com_reverse;
    }

    sendCommands(rozkazy, sizeof(rozkazy));

    if (initial)
    {
        m_delay->delayms(50);
    }

    sendCommand(cmd_set_power_control | 0x6);

    if (initial)
    {
        m_delay->delayms(50);
    }

    sendCommand(cmd_set_power_control | 0x7);

    if (initial)
    {
        m_delay->delayms(10);
    }

    uint8_t rozkazy2[] = {
        cmd_set_resistor_ratio | 0x5,
        cmd_display_on,
        cmd_set_allpts_normal,
    };
    sendCommands(rozkazy2, sizeof(rozkazy2));


    ustawKontrast(m_contrast);
    sendCommand(cmd_rmw);
}

void CST7565Driver::ustawKontrast(uint8_t value)
{
    m_contrast = value;
    uint8_t rozkazy[] = {
        cmd_set_volume_first,
        (uint8_t) (cmd_set_volume_second | (value & 0x3f)),
    };

    sendCommands(rozkazy, sizeof(rozkazy));
}

void CST7565Driver::fill(int16_t imgX1, int16_t imgY1, int16_t imgX2, int16_t imgY2, TFillOperation fillOperation)
{
    if (imgX2 >= LCD_WIDTH)
    {
        imgX2 = LCD_WIDTH - 1;
    }

    if (imgY2 >= LCD_HEIGHT)
    {
        imgY2 = LCD_HEIGHT - 1;
    }

    if (imgX1 > imgX2 || imgY1 > imgY2)
    {
        return;
    }

    uint8_t yb1 = imgY1 / 8;
    uint8_t yb2 = imgY2 / 8;
    uint8_t modyfikacja1;
    uint8_t modyfikacja2;
    uint8_t *adr_byte_bufora;
///----------------------------------------------------------

    /* Check the parameters */
    //assert_param((x1 >=0) && (x2 < LCD_SZEROKOSC) && (y1 >=0) && (y2 < LCD_WYSOKOSC) );
    if (imgX1 >= LCD_WIDTH)
    {
        imgX1 = LCD_WIDTH - 1;
    }

    if (imgX2 >= LCD_WIDTH)
    {
        imgX2 = LCD_WIDTH - 1;
    }

    if (imgX1 > imgX2)
    {
        imgX1 = imgX2;
    }

    if (imgY1 >= LCD_HEIGHT)
    {
        imgY1 = LCD_HEIGHT - 1;
    }

    if (imgY2 >= LCD_HEIGHT)
    {
        imgY2 = LCD_HEIGHT - 1;
    }

    if (imgY1 > imgY2)
    {
        imgY1 = imgY2;
    }

    if (m_iSuspendLayout > 0)
    {
        setSuspendedArea(imgX1, imgY1, imgX2, imgY2);
    }

    for (uint8_t y = yb1; y <= yb2; y++)
    {
        modyfikacja1 = 0;
        modyfikacja2 = 0;

        if (yb1 == yb2)
        {
            for (uint8_t i = imgY1 % 8; i <= imgY2 % 8; i++)
            {
                modyfikacja1 += (1 << i);
            }
            modyfikacja2 = modyfikacja1;
        }
        else
        {
            if (y == yb1) // (zwykle) modyfikujemy tylko czesc bajtu w ktorym znajduje sie y1
            {
                for (uint8_t i = imgY1 % 8; i <= 8; i++)
                {
                    modyfikacja1 += (1 << i);
                }
            }

            if (y == yb2) // (zwykle) modyfikujemy tylko czesc bajtu w ktorym znajduje sie y2
            {
                for (uint8_t i = 0; i <= imgY2 % 8; i++)
                {
                    modyfikacja2 += (1 << i);
                }
            }
        }

        ///----------------------------------------------------------

        for (uint8_t x = imgX1; x <= imgX2; x++)
        {
            adr_byte_bufora = bufor_ekranu + (y * LCD_WIDTH) + x;

            switch (fillOperation)
            {
                case FILL_OPERATION_FILL:
                    if (y == yb1)
                    {
                        *adr_byte_bufora |= modyfikacja1;
                    }

                    if (y == yb2)
                    {
                        *adr_byte_bufora |= modyfikacja2;
                    }

                    if (y != yb1 && y != yb2)
                    {
                        *adr_byte_bufora = 0xff;
                    }

                    break;

                case FILL_OPERATION_ERASE:
                    if (y == yb1)
                    {
                        *adr_byte_bufora &= ~modyfikacja1;
                    }

                    if (y == yb2)
                    {
                        *adr_byte_bufora &= ~modyfikacja2;
                    }

                    if (y != yb1 && y != yb2)
                    {
                        *adr_byte_bufora = 0x0;
                    }

                    break;

                case FILL_OPERATION_NEGATE:
                    if (y == yb1)
                    {
                        *adr_byte_bufora ^= modyfikacja1;
                    }

                    if (y == yb2)
                    {
                        *adr_byte_bufora ^= modyfikacja2;
                    }

                    if (y != yb1 && y != yb2)
                    {
                        *adr_byte_bufora = ~(*adr_byte_bufora);
                    }

                    break;
            }
        }

        if (m_iSuspendLayout == 0)
        {
            drawBufferLine(y, imgX1, imgX2);
        }
    }
}

void CST7565Driver::drawRectangle(int16_t x1, int16_t y1, int16_t x2, int16_t y2)
{
    fill(x1, y1, x2, y1, CST7565Driver::FILL_OPERATION_FILL);
    fill(x1, y2, x2, y2, CST7565Driver::FILL_OPERATION_FILL);
    fill(x1, y1, x1, y2, CST7565Driver::FILL_OPERATION_FILL);
    fill(x2, y1, x2, y2, CST7565Driver::FILL_OPERATION_FILL);
}

void CST7565Driver::clear()
{
    fill(0, 0, LCD_WIDTH - 1, LCD_HEIGHT - 1, FILL_OPERATION_ERASE);
}

void CST7565Driver::imgBitBltCenterBox(int16_t imgX1, int16_t imgY1, int16_t imgX2, int16_t imgY2,
        const uint16_t imgAddress, TBitOperation bitOperation)
{
    int16_t imgWidth = 0;
    int16_t imgHeight = 0;

    flashStartReadSequentialBytes(imgAddress);
    readSequenctialImgHeaderData(&imgWidth, &imgHeight);
//    flashEndReadSequentialBytes();


    if (imgX2 > 0)
    {
        int16_t boxWidth = imgX2 - imgX1 + 1;
        if (imgWidth < boxWidth)
        {
            imgX1 += (boxWidth - imgWidth) / 2;
        }
    }

    if (imgY2 > 0)
    {
        int16_t boxHeight = imgY2 - imgY1 + 1;
        if (imgHeight < boxHeight)
        {
            imgY1 += (boxHeight - imgHeight) / 2;
        }
    }

    //lcd::rysuj_bitmape(imgX1, imgY1, (CImgData::TImgAddress) imgAddress, operacja);

    int16_t illegalX = (int16_t)LCD_WIDTH;
    int16_t illegalY = (int16_t)LCD_HEIGHT;

    if (imgX1 >= illegalX || imgY1 >= illegalY)
    {
        return;
    }

    uint8_t wiersz = imgY1 / 8;
    uint8_t* adres_w_buforze = bufor_ekranu + (wiersz * LCD_WIDTH) + imgX1;
    uint8_t ybit = imgY1 % 8;

    uint8_t max_wierszy = getImgByteHeight(imgHeight);
    uint8_t max_wierszy_do_narysowania = getOffsetImgByteHeight(imgHeight, imgY1);
    uint8_t max_kolumn = imgWidth;
    uint8_t dane = 0;
    uint8_t newVal = 0;
    TImageLine imgLine = IML_FIRST;

    uint8_t firstRowMask = (0xFF << ybit);
    uint8_t bajtyKoncowe = ((imgY1 + imgHeight) % 8);
    uint8_t lastRowMask = (0xFF >> (8 - bajtyKoncowe));
    lastRowMask = (lastRowMask > 0 ? lastRowMask : 0xFF);

//    Przyjrzeć się, czy ostatni linia jest dobrze maskowana i czy nie trzeba njpierw odwrócić jakoś tego maskowania
//    Wygląda na to, że bajty są rysowane na ekranie w odwrotną stronę niż się wydawało i tak trzeba je także w pamięci maskować

    if (max_wierszy == max_wierszy_do_narysowania && max_wierszy == 1)
    {
        firstRowMask = (firstRowMask & lastRowMask);
    }

    uint8_t middleMask = 0xFF;
    uint8_t actualMask = 0xFF;

    if ((int16_t)max_kolumn + (int16_t)imgX1 > illegalX)
    {
        max_kolumn = illegalX - (int16_t)imgX1;
    }

    if ((int16_t)max_wierszy_do_narysowania + (int16_t)wiersz > illegalY / 8)
    {
        max_wierszy_do_narysowania = (illegalY / 8) - (int16_t)wiersz;
        lastRowMask = 0xFF;
    }

    if (m_iSuspendLayout > 0)
    {
        setSuspendedArea(imgX1, imgY1, imgX1 + max_kolumn - 1, imgY1 + imgHeight - 1);
    }

    uint8_t rozkazy[] = {
        cmd_set_page,
        (uint8_t) (cmd_set_column_lower | (imgX1 & 0xf)),
        (uint8_t) (cmd_set_column_upper | ((imgX1 >> 4) & 0xf)),
    };

//    for (uint8_t w = 0; w < max_wierszy_do_narysowania; ++w)
//    {
//        if (m_iSuspendLayout == 0)
//        {
//            rozkazy[0] = (cmd_set_page | wiersz);
//            sendCommands(rozkazy, sizeof(rozkazy));
//            ++wiersz;
//        }
//
//        if (w == 0)
//        {
//            imgLine = IML_FIRST;
//            actualMask = firstRowMask;
//        }
//        else if (w == max_wierszy_do_narysowania - 1)
//        {
//            imgLine = IML_LAST;
//            actualMask = lastRowMask;
//        }
//        else
//        {
//            imgLine = IML_MIDDLE;
//            actualMask = middleMask;
//        }
//
//        for (uint8_t k = 0; k < max_kolumn; ++k)
//        {
//            if (imgLine == IML_FIRST)
//            {
//                dane = (getImgData(imgAddress, k * max_wierszy + w) << ybit);
//            }
//            else
//            {
//                dane = (getImgData(imgAddress, k * max_wierszy + w) << ybit)
//                            | ((getImgData(imgAddress, k * max_wierszy + (w - 1))) >> (8 - ybit));
//            }
//
//            newVal = *adres_w_buforze;
//            switch (bitOperation)
//            {
//                case BIT_OPERATION_OR:
//                    newVal |= dane;
//                    break;
//
//                case BIT_OPERATION_AND:
//                    newVal = dane;
//                    break;
//
//                case BIT_OPERATION_XOR:
//                    newVal ^= dane;
//                    break;
//            }
//
//            *adres_w_buforze = uaktualnijBajt(*adres_w_buforze, newVal, actualMask);
//
//            if (m_iSuspendLayout == 0)
//            {
//                sendDataValue(*adres_w_buforze);
//
//                //TODO: można to przerobić w taki sposób, żeby była możliwość wykorzystania funkcji rysującej całą linię - szybsza obsługa
//            }
//            adres_w_buforze++;
//        }
//        adres_w_buforze += (LCD_WIDTH - max_kolumn);
//    }


    //#####################################################
    //przerobka na takie rysowanie kolejnych bajtow na ekranie jak sa zapisane w pamieci

    uint8_t wierszPrev = wiersz;
    uint8_t danePrev = 0;
    int16_t adresPrev = -1;

    for (uint8_t k = 0; k < max_kolumn; ++k)
    {
    	uint8_t w = 0;

        for (w = 0; w < max_wierszy_do_narysowania; ++w)
        {
        	adres_w_buforze = bufor_ekranu + (wiersz * LCD_WIDTH) + k + imgX1;

            if (m_iSuspendLayout == 0)
            {
                rozkazy[0] = (cmd_set_page | wiersz);
                rozkazy[1] = (cmd_set_column_lower | ((k + imgX1) & 0xf)),
                rozkazy[2] = (cmd_set_column_upper | (((k + imgX1) >> 4) & 0xf)),
                sendCommands(rozkazy, sizeof(rozkazy));
            }

            ++wiersz;

            if (w == 0)
            {
                imgLine = IML_FIRST;
                actualMask = firstRowMask;
            }
            else if (w == max_wierszy_do_narysowania - 1)
            {
                imgLine = IML_LAST;
                actualMask = lastRowMask;
            }
            else
            {
                imgLine = IML_MIDDLE;
                actualMask = middleMask;
            }

            int16_t adress = k * max_wierszy + w;
            uint8_t daneTmp = 0;

            if(adresPrev != adress)
            {
            	adresPrev = adress;
            	daneTmp = (getImgData(imgAddress, adress));
            }
            else
            {
            	daneTmp = danePrev;
            }


			if (imgLine == IML_FIRST)
			{
//				uint8_t daneTmp = (getImgData(imgAddress, k * max_wierszy + w));
				danePrev = daneTmp;

				dane = (daneTmp << ybit);
			}
			else
			{
//				uint8_t daneTmp = (getImgData(imgAddress, k * max_wierszy + w));


				dane = (daneTmp << ybit)
							| ((danePrev) >> (8 - ybit));

				danePrev = daneTmp;
			}

			newVal = *adres_w_buforze;
			switch (bitOperation)
			{
				case BIT_OPERATION_OR:
					newVal |= dane;
					break;

				case BIT_OPERATION_AND:
					newVal = dane;
					break;

				case BIT_OPERATION_XOR:
					newVal ^= dane;
					break;
			}

			*adres_w_buforze = uaktualnijBajt(*adres_w_buforze, newVal, actualMask);

			if (m_iSuspendLayout == 0)
			{
				sendDataValue(*adres_w_buforze);

				//TODO: można to przerobić w taki sposób, żeby była możliwość wykorzystania funkcji rysującej całą linię - szybsza obsługa
			}
        }

        wiersz = wierszPrev;
    }

	flashEndReadSequentialBytes();
}

uint8_t CST7565Driver::uaktualnijBajt(uint8_t oryginal, uint8_t newValue, uint8_t bitMask)
{
    return ((oryginal & ~bitMask) | (newValue & bitMask));
}

void CST7565Driver::imgBitBlt(int16_t imgX, int16_t imgY, const uint16_t imgAddress, TBitOperation bitOperation)
{
    imgBitBltCenterBox(imgX, imgY, 0, 0, imgAddress, bitOperation);
}

void CST7565Driver::setSuspendedArea(int16_t x1, int16_t y1, int16_t x2, int16_t y2)
{
    if (x1 < m_iSuspendedAreaX1 || m_iSuspendedAreaX1 < 0)
    {
        if (x1 < 0)
            x1 = 0;
        m_iSuspendedAreaX1 = x1;
    }
    if (y1 < m_iSuspendedAreaY1 || m_iSuspendedAreaY1 < 0)
    {
        if (y1 < 0)
            y1 = 0;
        m_iSuspendedAreaY1 = y1;
    }
    if (x2 > m_iSuspendedAreaX2 || m_iSuspendedAreaX2 < 0)
    {
        if (x2 >= (int16_t)LCD_WIDTH)
            x2 = LCD_WIDTH - 1;
        m_iSuspendedAreaX2 = x2;
    }
    if (y2 > m_iSuspendedAreaY2 || m_iSuspendedAreaY2 < 0)
    {
        if (y2 >= (int16_t)LCD_HEIGHT)
            y2 = LCD_HEIGHT - 1;
        m_iSuspendedAreaY2 = y2;
    }
}

void CST7565Driver::resumeDrawing()
{
    if (m_iSuspendLayout > 0)
    {
        --m_iSuspendLayout;

        writeDataFromMemory();
    }
}

//------------------------------------------------------------------------------
void CST7565Driver::writeDataFromMemory()
//------------------------------------------------------------------------------
{
    if ((m_iSuspendLayout == 0) && (m_iSuspendedAreaY1 != -1))
    {
        int16_t actualY = 0;
        int8_t byteIndex1 = m_iSuspendedAreaY1 / 8;
        int8_t byteIndex2 = m_iSuspendedAreaY2 / 8;

        for (actualY = byteIndex1; (int16_t) actualY <= byteIndex2; actualY++)
        {
            drawBufferLine(actualY, m_iSuspendedAreaX1, m_iSuspendedAreaX2);
        }

        m_iSuspendedAreaX1 = -1;
        m_iSuspendedAreaY1 = -1;
        m_iSuspendedAreaX2 = -1;
        m_iSuspendedAreaY2 = -1;
    }
}

void CST7565Driver::drawBufferLine(int16_t byteLine, int16_t fromX, int16_t toX)
{
    uint8_t rozkazy[] = {
        (uint8_t) (cmd_set_page | byteLine),
        (uint8_t) (cmd_set_column_lower | (fromX & 0xf)),
        (uint8_t) (cmd_set_column_upper | ((fromX >> 4) & 0xf)),
    };

    sendCommands(rozkazy, sizeof(rozkazy));

    sendDataValues(&bufor_ekranu[(byteLine * LCD_WIDTH) + fromX], toX - fromX + 1);
}

void CST7565Driver::startSendingCommands()
{
    if (halStartSendingCommand())
    {
        m_delay->delayus(1);
    }
}

void CST7565Driver::startSendingData()
{
    if (halStartSendingData())
    {
        m_delay->delayus(1);
    }
}

void CST7565Driver::sendCommand(uint8_t command)
{
    startSendingCommands();
    halSelectChip();
    halSendBytes(&command, sizeof(command));
    halDeselectChip();
}

void CST7565Driver::sendCommands(uint8_t* commands, uint16_t size)
{
    startSendingCommands();
    halSelectChip();
    halSendBytes(commands, size);
    halDeselectChip();
}

void CST7565Driver::sendDataValue(uint8_t dataValue)
{
    startSendingData();
    halSelectChip();
    halSendBytes(&dataValue, sizeof(dataValue));
    halDeselectChip();
}

void CST7565Driver::sendDataValues(uint8_t* dataValues, uint16_t size)
{
    startSendingData();
    halSelectChip();
    halSendBytes(dataValues, size);
    halDeselectChip();
}

bool CST7565Driver::readSequenctialImgHeaderData(int16_t* outWidth, int16_t* outHeight)
{
    uint8_t imgHeaderData[2];
    flashReadSequentialBytes(imgHeaderData, sizeof(imgHeaderData));

    int16_t imgWidth = imgHeaderData[0];
    int16_t imgHeight = imgHeaderData[1];

    bool poprawnyNaglowek = imgWidth <= LCD_WIDTH && imgHeight <= LCD_HEIGHT;

    *outWidth = imgWidth;
    *outHeight = imgHeight;

    return poprawnyNaglowek;
}

uint8_t CST7565Driver::getImgData(uint16_t imgAddress, uint16_t offset)
{
    uint8_t outData;
//    flashStartReadSequentialBytes(imgAddress + offset + 2);
    flashReadSequentialBytes(&outData, sizeof(outData));
//    flashEndReadSequentialBytes();
    return outData;
}

uint8_t CST7565Driver::getImgByteHeight(int16_t imgHeight)
{
    if (imgHeight < 8)
    {
        return 1;
    }
    else if (imgHeight % 8)
    {
        return (imgHeight / 8) + 1;
    }
    else
    {
        return imgHeight / 8;
    }
}

uint8_t CST7565Driver::getOffsetImgByteHeight(int16_t imgHeight, uint8_t yoffset)
{
    uint8_t hpx = imgHeight + (yoffset % 8);

    if (hpx < 8)
    {
        return 1;
    }
    else if (hpx % 8)
    {
        return (uint8_t) (hpx / 8) + 1;
    }
    else
    {
        return hpx / 8;
    }

}

uint8_t CST7565Driver::getDrawingSteps(int16_t imgHeight, int16_t imgWidth)
{
    return imgHeight + (imgWidth / 8);
}
