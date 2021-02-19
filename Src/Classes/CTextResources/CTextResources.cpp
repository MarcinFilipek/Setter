/*
 * CTextResources.cpp
 *
 *  Created on: Mar 13, 2015
 *      Author: krzysiek
 */

#include "CTextResources.h"
#ifdef SUBTITLES_TEST
#include "CGraphicFontSubtitlesTest.h"
#endif

uint16_t CTextResources::m_languageVersion;
uint16_t CTextResources::m_defaultLanguageVersion;

void CTextResources::setLanguageVersion(uint16_t languageVersion)
{
    m_languageVersion = languageVersion;
}

void CTextResources::setDefaultLanguageVersion(uint16_t defaultLanguageVersion)
{
    m_defaultLanguageVersion = defaultLanguageVersion;
}

uint16_t CTextResources::getLanguageVersion()
{
    return m_languageVersion;
}

uint16_t CTextResources::getDefaultLanguageVersion()
{
    return m_defaultLanguageVersion;
}

uint16_t CTextResources::copyUtfToWchar(wchar_t* to, const char* from)
{
    uint16_t cnt = 0;
    uint16_t c1, c2, c3, c4;

    while (*from)
    {
        if ((*from & 0x80) == 0)
        {
            *to = *from++;
        }
        else
            if ((*from & 0xe0) == 0xc0)
            {
                c1 = *from++; //& 0x1f;
                c2 = *from++; //& 0x3f;
                *to = (c1 << 8) | c2;

                //           gdyby zapisc czcoinki w foracie L('a') w prawidlowym formacie wchar to uzyc tego
                //             c1 = *from++ & 0x1f;
                //             c2 = *from++ & 0x3f;
                //             *to = (c1 << 6) | c2;

            }
            //         sizeof( wchar_t ) > 2
            else if ((*from & 0xf0) == 0xe0)
            {

                 c1 = *from++;
                 c2 = *from++;
                 c3 = *from++;
                 *to = (c1 << 16) | (c2 << 8) | c3;

//           gdyby zapisc czcoinki w foracie L('a') w prawidlowym formacie wchar to uzyc tego
//                   if (len < 3)
//                     break;          /* drop trailing incomplete char */
//                 c1 = *from++ & 0x0f;
//                 c2 = *from++ & 0x3f;
//                 c3 = *from++ & 0x3f;
//                 *to = (c1 << 12) | (c2 << 6) | c3;
//                 len -= 3;
            }
            else if ((*from & 0xf8) == 0xf0)
            {

                 c1 = *from++;
                 c2 = *from++;
                 c3 = *from++;
                 c4 = *from++;
                 *to = (c1 << 24) | (c2 << 16) | (c3 << 8) | c4;

//           gdyby zapisc czcoinki w foracie L('a') w prawidlowym formacie wchar to uzyc tego
//             if (len < 4)
//                 break;          /* drop trailing incomplete char */
//                 c1 = *from++ & 0x07;
//                 c2 = *from++ & 0x3f;
//                 c3 = *from++ & 0x3f;
//                 c4 = *from++ & 0x3f;
//                 *to = (c1 << 18) | (c2 << 12) | (c3 << 6) | c4;
//             len -= 4;
            }
            else
            {
                *to = *from++;
            }
        to++;
        cnt++;
    }
    *to = 0;
    return cnt - 1;
}

int16_t CTextResources::copyTextToBuffer(wchar_t *outBuffer, uint32_t strId, int16_t bufferSize)
{
    int16_t index = 0;
    uint16_t stringLength = 0;
    uint8_t buf, c2, c3, c4;
    int16_t cout = 0;

    uint32_t address = startSequentialRead(strId);
    address += readStringLength(address, &stringLength);

    if (stringLength > (bufferSize - 1))
    {
        stringLength = bufferSize - 1;
    }

    while (cout < stringLength)
    {
        readData(address, &buf, sizeof(buf));
        address += sizeof(buf);
        //Znak ma jeden znak
        if ((buf & 0x80) == 0)
        {
            outBuffer[index] = (wchar_t) buf;
            cout += 1;
        }
        else
            //Znak ma dwa znaki
            if ((buf & 0xe0) == 0xc0)
            {
                readData(address, &c2, sizeof(c2));
                address += sizeof(c2);
                outBuffer[index] = (((uint16_t) buf) << 8) | c2;
                cout += 2;
            }
            //Znak ma trzy znaki
            else
                if ((buf & 0xf0) == 0xe0)
                {
                    readData(address, &c2, sizeof(c2));
                    address += sizeof(c2);
                    readData(address, &c3, sizeof(c3));
                    address += sizeof(c3);
                    outBuffer[index] = (((uint16_t) buf) << 16) | (((uint16_t) c2) << 8 ) | c3;
                    cout += 3;
                }
                //Znak ma cztery znaki
                else
                    if ((buf & 0xf8) == 0xf0)
                    {
                        readData(address, &c2, sizeof(c2));
                        address += sizeof(c2);
                        readData(address, &c3, sizeof(c3));
                        address += sizeof(c3);
                        readData(address, &c4, sizeof(c4));
                        address += sizeof(c4);
                        outBuffer[index] = (((uint16_t) buf) << 24) | (((uint16_t) c2) << 16 ) | (((uint16_t) c3) << 8 ) | c4;
                        cout += 4;
                    }

        index++;
    }
    outBuffer[index] = 0;
    outBuffer[bufferSize - 1] = 0;

    if (index > 0)
    {
        return index - 1;
    }
    else
    {
        return 0;
    }
}

int16_t CTextResources::copyTextToBuffer(char *outBuffer, uint32_t strId, int16_t bufferSize)
{
    uint16_t stringLength = 0;
    uint32_t address = CTextResources::startSequentialRead(strId);
    address += readStringLength(address, &stringLength);

    if (stringLength > (bufferSize - 1))
    {
        stringLength = bufferSize - 1;
    }

    readData(address, outBuffer, stringLength);
    outBuffer[stringLength] = 0;

    return stringLength;
}

uint32_t CTextResources::getCurrentLanguageStringAdress(uint32_t stringAddress)
{
	for (int16_t i = 0; i < m_languageVersion; i++)
	{
		uint16_t currentStringLength = 0;
		stringAddress += readStringLength(stringAddress, &currentStringLength);
		stringAddress += currentStringLength;
	}
	return stringAddress;
}

uint32_t CTextResources::startSequentialRead(uint32_t address)
{
#ifdef SUBTITLES_TEST
    CGraphicFontSubtitlesTest::startSequentialRead(address);
#endif

    uint32_t stringAddress = address;
    uint16_t stringLength = 0;

	stringAddress = getCurrentLanguageStringAdress(stringAddress);

    readStringLength(stringAddress, &stringLength);

    if (stringLength == 0)
    {
        stringAddress = address;

        for (int16_t i = 0; i < m_defaultLanguageVersion; i++)
        {
            stringAddress += readStringLength(stringAddress, &stringLength);
            stringAddress += stringLength;
        }

        readStringLength(stringAddress, &stringLength);

        if (stringLength == 0)
        {
            stringAddress = address;
        }
    }

    return stringAddress;
}

int8_t CTextResources::readStringLength(uint32_t address, uint16_t *result)
{
    uint8_t stringLength[2];
    readData(address, &stringLength[0], sizeof(stringLength[0]));
    if (stringLength[0] < 255)
    {
        *result = stringLength[0];
        return 1;
    }
    else
    {
        readData(address + sizeof(stringLength[0]), stringLength, sizeof(stringLength));
        *result = (stringLength[0] * 256) + stringLength[1];
        return 3;
    }
}

uint16_t CTextResources::strlenUtf(const char* buff)
{
    uint16_t cnt = 0;
    uint16_t inc = 0;

	while (*buff)
	{
		if ((*buff & 0x80) == 0)
		{
			inc = 1;
		}
		else if ((*buff & 0xe0) == 0xc0)
		{
			inc = 2;
		}
		else if ((*buff & 0xf0) == 0xe0)
		{
			inc = 3;
		}
		else if ((*buff & 0xf8) == 0xf0)
		{
			inc = 4;
		}
		buff += inc;
		cnt ++;
	}
    return cnt;
}
