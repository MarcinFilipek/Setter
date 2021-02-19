/*
 * CGraphicFontSubtitlesTest.cpp
 *
 *  Created on: Oct 14, 2015
 *      Author: krzysiek
 */

#include "CGraphicFontSubtitlesTest.h"
#include "CGraphicFont.h"
#include "CTextResources.h"

const int16_t *CGraphicFontSubtitlesTest::m_languageVersions;
int16_t CGraphicFontSubtitlesTest::m_languageVersionsCount;
bool CGraphicFontSubtitlesTest::m_staticTest;
bool CGraphicFontSubtitlesTest::m_dynamicTest;
bool CGraphicFontSubtitlesTest::m_languageTest;
int16_t CGraphicFontSubtitlesTest::m_minX;
int16_t CGraphicFontSubtitlesTest::m_maxX;
int16_t CGraphicFontSubtitlesTest::m_minY;
int16_t CGraphicFontSubtitlesTest::m_maxY;
CGraphicFontSubtitlesTest::SItem CGraphicFontSubtitlesTest::m_dynamicItems[512];

void CGraphicFontSubtitlesTest::setLanguageVersions(const int16_t *languageVersions, int16_t languageVersionsCount)
{
    m_languageVersions = languageVersions;
    m_languageVersionsCount = languageVersionsCount;
}

void CGraphicFontSubtitlesTest::startDynamicTest(bool languageTest)
{
    m_dynamicTest = true;
    m_languageTest = languageTest;
}

void CGraphicFontSubtitlesTest::stopDynamicTest()
{
    m_dynamicTest = false;
    m_languageTest = false;
}

void CGraphicFontSubtitlesTest::startStaticTest(const SItem* items, int16_t itemsCount)
{
    bool dynamicTest = m_dynamicTest;
    bool languageTest = m_languageTest;
    m_dynamicTest = false;
    m_staticTest = true;
    m_languageTest = true;

    int16_t languageVersionTmp = CTextResources::getLanguageVersion();

    for (int16_t i = 0; (i < m_languageVersionsCount) || (i == 0); i++)
    {
        if (i < m_languageVersionsCount)
        {
            CTextResources::setLanguageVersion(m_languageVersions[i]);
        }

        for (int16_t j = 0; j < itemsCount; j++)
        {
            m_minX = 8192;
            m_maxX = -8192;
            m_minY = 8192;
            m_maxY = -8192;

            CGraphicFont::drawText(
                    0,
                    0,
                    items[j].width - 1,
                    items[j].height - 1,
                    items[j].address,
                    0,
                    items[j].fontID,
                    (CGraphicFont::TPrintCase) items[j].printCase,
                    CGraphicFont::AT_LEFT,
                    items[j].multiline ? CGraphicFont::MULTILINE_ON : CGraphicFont::MULTILINE_OFF,
                    {0});

            m_maxY += CGraphicFont::getFontHeight(items[j].fontID);

            int width = m_maxX - m_minX + 1;
            int height = m_maxY - m_minY + 1;
            char buffer[64];
            buffer[0] = 0;

            do
            {
                if ((items[j].width <= 1) && (items[j].width <= 1))
                {
                    if (i == 0)
                    {
                        strcpy(buffer, "Brak szerokości i wysokości");
                    }
                    break;
                }

                if (items[j].width <= 1)
                {
                    if (i == 0)
                    {
                        strcpy(buffer, "Brak szerokości");
                    }
                    break;
                }

                if (items[j].height <= 1)
                {
                    if (i == 0)
                    {
                        strcpy(buffer, "Brak wysokości");
                    }
                    break;
                }

                if (width > items[j].width)
                {

                    sprintf(buffer, "Szerokość przekroczona %d > %d", width, items[j].width);
                    break;
                }

                if (height > items[j].height)
                {
                    sprintf(buffer, "Wysokość przekroczona %d > %d", height, items[j].height);
                    break;
                }
            }
            while (false);

            if (buffer[0] != 0)
            {
                char label[256];
                getLabel(items[j].address, label, sizeof(label));
            }
        }
    }

    if (m_languageVersionsCount > 0)
    {
        CTextResources::setLanguageVersion(languageVersionTmp);
    }

    m_dynamicTest = dynamicTest;
    m_staticTest = false;
    m_languageTest = languageTest;
}

void CGraphicFontSubtitlesTest::getLabel(int32_t address, char *buffer, int16_t bufferSize)
{
    bool languageTest = m_languageTest;
    m_languageTest = false;
    uint16_t languageVersionTmp = CTextResources::getLanguageVersion();
    CTextResources::setLanguageVersion(0);
    CTextResources::copyTextToBuffer(buffer, address, bufferSize);
    CTextResources::setLanguageVersion(languageVersionTmp);
    m_languageTest = languageTest;
}

bool CGraphicFontSubtitlesTest::updateDynamicBuffer(SItem *item)
{
    int16_t bufferSize = sizeof(m_dynamicItems) / sizeof(m_dynamicItems[0]);
    for (int16_t i = 0; i < bufferSize; i++)
    {
        if (memcmp(&m_dynamicItems[i], item, sizeof(SItem)) == 0)
        {
            return false;
        }
    }
    for (int16_t i = 0; i < bufferSize; i++)
    {
        bool zero = (m_dynamicItems[i].address == 0) && (m_dynamicItems[i].width == 0)
                && (m_dynamicItems[i].height == 0);

        if (zero)
        {
            memcpy(&m_dynamicItems[i], item, sizeof(SItem));
            return true;
        }
    }

    return true;

}

void CGraphicFontSubtitlesTest::drawImage(uint32_t address, int16_t x1, int16_t y1)
{
    if (m_staticTest)
    {
        if (m_minX > x1)
        {
            m_minX = x1;
        }

        if (m_maxX < x1 + CGraphicFont::getImageWidth(address) - 1)
        {
            m_maxX = x1 + CGraphicFont::getImageWidth(address) - 1;
        }

        if (m_minY > y1)
        {
            m_minY = y1;
        }

        if (m_maxY < y1 - 1)
        {
            m_maxY = y1 - 1;
        }
    }
}

void CGraphicFontSubtitlesTest::drawText(int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint32_t stringAddress,
        uint16_t fontID, int8_t printCase, int8_t alignText, int8_t mulitiline)
{
    if (m_dynamicTest && (stringAddress != 0))
    {
        SItem item;
        memset(&item, 0, sizeof(item));
        item.address = stringAddress;
        item.fontID = fontID;
        item.width = x2 - x1 + 1;
        item.height = y2 - y1 + 1;
        item.multiline = mulitiline;
        item.printCase = printCase;
        if (updateDynamicBuffer(&item))
        {
            char label[256];
            getLabel(item.address, label, sizeof(label));
        }
    }
}

void CGraphicFontSubtitlesTest::startSequentialRead(uint32_t address)
{
    if ((m_staticTest || m_dynamicTest) && m_languageTest)
    {
        uint32_t stringAddress = address;
        uint8_t stringLength[2];

        int16_t languageVersion = CTextResources::getLanguageVersion();
        for (int16_t i = 0; ((i < m_languageVersionsCount) && m_dynamicTest) || ((i == 0) && m_staticTest); i++)
        {
            if (m_dynamicTest)
            {
                languageVersion = m_languageVersions[i];
            }

            for (int16_t i = 0; i < languageVersion; i++)
            {
                CTextResources::readData(stringAddress, &stringLength[0], sizeof(stringLength[0]));

                if (stringLength[0] < 255)
                {
                    stringAddress += stringLength[0] + 1;
                }
                else
                {
                    CTextResources::readData(address + sizeof(stringLength[0]), stringLength, sizeof(stringLength));
                    stringAddress += (stringLength[0] * 256) + stringLength[1] + 3;
                }
            }

            CTextResources::readData(stringAddress, &stringLength, sizeof(stringLength));

            if (stringLength == 0)
            {
                char label[256];
                getLabel(address, label, sizeof(label));
            }
        }
    }
}
