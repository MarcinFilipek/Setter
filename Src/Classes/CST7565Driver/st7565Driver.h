/*
 * st7565Driver.h
 *
 *  Created on: 30 sty 2015
 *      Author: damian
 *     Version: 1.0.0
 */
#ifndef CLASSES_ST7565DRIVER_ST7565DRIVER_H_
#define CLASSES_ST7565DRIVER_ST7565DRIVER_H_

#include "iDelay.h"

#if defined SSD1963HAL_ST480_F2
#include "st7565HAL_ST480_F2.h"
#elif defined ST7565_ST267_F1
#include "st7565HAL_ST267_F1.h"
#elif defined ST7565_ST461_F1
#include "st7565HAL_ST461_F1.h"
#elif defined ST7565_ST920_F2
#include "st7565HAL_ST920_F2.h"
#elif defined ST7565_ST980_F1
#include "st7565HAL_ST980_F1.h"
#else
#error Brak definicji warstwy HAL!
#endif

#if defined SSD1963HAL_FLASH_IMG_DATA
#include "st7565HAL_Flash_ImgData.h"
#else
#include "st7565HAL_Flash_Custom.h"
#endif

/**
 * Klasa obsługująca wyświetlacz ST7565
 *
 * Klasa wykorzystuje bufor danych odwzorowujący dane w następujący sposób:
 *
 *     Tablica danych:
 *     [A0]01234567,[A1]01234567,[A2]01234567,...,[A127]01234567,[B0]01234567,[B1]01234567...,[H127]01234567
 *
 *     Wyświetlacz:
 *     +-------------...------+
 *     | [ A0 ][ A1 ]...[A127]|
 *     |   0     0        0   |
 *     |   1     1        1   |
 *     |   2     2        2   |
 *     |   3     3        3   |
 *     |   4     4        4   |
 *     |   5     5        5   |
 *     |   6     6        6   |
 *     |   7     7        7   |
 *     | [ B0 ][ B1 ]...[B127]|
 *     |   0     0        0   |
 *     |   1     1        1   |
 *     |   2     2        2   |
 *     |   3     3        3   |
 *     |   4     4        4   |
 *     |   5     5        5   |
 *     |   6     6        6   |
 *     |   7     7        7   |
 *     :   :     :    :   :   :
 *     | [ H0 ][ H1 ]...[H127]|
 *     :   :     :    :   :   :
 *     +-------------...------+
 *
 */
class CST7565Driver : public CST7565HAL, public CST7565_Hal_Flash
{
    public:

        static const int16_t LCD_WIDTH = 128;
        static const int16_t LCD_HEIGHT = 64;

        enum TBitOperation
        {
            BIT_OPERATION_AND,
            BIT_OPERATION_OR,
            BIT_OPERATION_XOR,
        };

        enum TFillOperation
        {
            FILL_OPERATION_FILL,
            FILL_OPERATION_ERASE,
            FILL_OPERATION_NEGATE,
        };

        enum TLCDCommand
        { //dla zachowania jasnosci po angielsku by latwiej bylo odnalezc w manualu wyswietlacza
            cmd_display_off            = 0xae,
            cmd_display_on             = 0xaf,

            cmd_set_disp_start_line    = 0x40,
            cmd_set_page               = 0xb0,

            cmd_set_column_upper       = 0x10,
            cmd_set_column_lower       = 0x00,

            cmd_set_adc_normal         = 0xa0,
            cmd_set_adc_reverse        = 0xa1,

            cmd_set_disp_normal        = 0xa6,
            cmd_set_disp_reverse       = 0xa7,

            cmd_set_allpts_normal      = 0xa4,
            cmd_set_allpts_on          = 0xa5,
            cmd_set_bias_9             = 0xa2,
            cmd_set_bias_7             = 0xa3,

            cmd_rmw                    = 0xe0,
            cmd_rmw_clear              = 0xee,
            cmd_internal_reset         = 0xe2,
            cmd_set_com_normal         = 0xc0,
            cmd_set_com_reverse        = 0xc8,
            cmd_set_power_control      = 0x28,
            cmd_set_resistor_ratio     = 0x20,
            cmd_set_volume_first       = 0x81,
            cmd_set_volume_second      = 0x0,
            cmd_set_static_off         = 0xac,
            cmd_set_static_on          = 0xad,
            cmd_set_static_reg         = 0x0,
            cmd_set_booster_first      = 0xf8,
            cmd_set_booster_234        = 0x0,
            cmd_set_booster_5          = 0x1,
            cmd_set_booster_6          = 0x3,
            cmd_nop                    = 0xe3,
            cmd_test                   = 0xf0
        };

        static void init(IDelayFunctions* delays, bool displayRotated = false);
        static void drawRectangle(int16_t x1, int16_t y1, int16_t x2, int16_t y2);
        static void imgBitBltCenterBox(int16_t imgX1, int16_t imgY1, int16_t imgX2, int16_t imgY2,
                const uint16_t imgAddress, TBitOperation bitOperation);
        static void imgBitBlt(int16_t imgX, int16_t imgY, const uint16_t imgAddress, TBitOperation bitOperation);
        static void fill(int16_t imgX1, int16_t imgY1, int16_t imgX2, int16_t imgY2, TFillOperation fillOperation);
        static void reinit();
        static void clear();

        static void ustawKontrast(uint8_t value);

        static void suspendDrawing()
        {
            if (m_iSuspendLayout < 127)
                ++m_iSuspendLayout;
        }

        static void resumeDrawing();

        static bool isSuspended() { return m_iSuspendLayout > 0; }
        static uint8_t* getBuforEkranu() { return bufor_ekranu; }

    private:

        enum TImageLine
        {
            IML_FIRST, // piersza kolumna która nie zaczyna się w poczatku batju
            IML_MIDDLE, // lini, które w całych 8 itach zawierają obrazek
            IML_LAST, // linie z niekompletną ilością bitów obrazka
        };

        static IDelayFunctions* m_delay;
        static uint8_t bufor_ekranu[];
        static uint8_t m_contrast;

        static int8_t m_iSuspendLayout;

        static int16_t m_iSuspendedAreaX1;
        static int16_t m_iSuspendedAreaY1;
        static int16_t m_iSuspendedAreaX2;
        static int16_t m_iSuspendedAreaY2;

        static bool m_displayRotated;

        static void startSendingCommands();
        static void startSendingData();
        static void sendCommand(uint8_t command);
        static void sendCommands(uint8_t* commands, uint16_t size);
        static void sendDataValue(uint8_t dataValue);
        static void sendDataValues(uint8_t* dataValues, uint16_t size);
        static void writeDataFromMemory();
        static void drawBufferLine(int16_t byteLine, int16_t fromX, int16_t toX);
        static bool readSequenctialImgHeaderData(int16_t* outWidth, int16_t* outHeight);
        static uint8_t getImgByteHeight(int16_t imgHeight);
        static uint8_t getOffsetImgByteHeight(int16_t imgHeight, uint8_t yoffset);
        static uint8_t getDrawingSteps(int16_t imgHeight, int16_t imgWidth);
        static uint8_t getImgData(uint16_t imgAddress, uint16_t offset);
        static void setSuspendedArea(int16_t x1, int16_t y1, int16_t x2, int16_t y2);
        static uint8_t uaktualnijBajt(uint8_t oryginal, uint8_t newValue, uint8_t bitMask);
        static void reinitInternal(bool initial);
};

#endif /* CLASSES_ST7565DRIVER_ST7565DRIVER_H_ */
