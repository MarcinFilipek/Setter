#include "stdint.h"
#include "crc_tools.h"
#include "crc32_basic.h"

uint32_t crc_tools_32_get_initial_value()
{
    return 0xFFFFFFFF;
}

uint32_t crc_tools_32_get_residue()
{
    return 0xDEBB20E3;
}

uint32_t crc_tools_32_final_xor(uint32_t crc)
{
    return ~crc;
}

uint32_t crc_tools_32_calculate(uint8_t bytes[], uint16_t size, uint8_t complement)
{
    uint32_t crc = crc_tools_32_get_initial_value();

    crc = crc_tools_32_partial_calculate(crc, bytes, size);
    if(complement)
    {
        crc = crc_tools_32_final_xor(crc);
    }
    return crc;
}

uint32_t crc_tools_32_partial_calculate(uint32_t crc, uint8_t bytes[], uint16_t size)
{
    uint16_t i;

    for(i = 0; i < size; i++)
    {
        crc = crc32_basic_update(crc, bytes[i]);
    }
    return crc;
}

void crc_tools_32_crc_2_bytes_lsb_first(uint32_t crc, uint8_t bytes[])
{
    uint8_t i;

    for(i = 0; i < 4; i++)
    {
        bytes[i] = (uint8_t)crc;
        crc >>= 8;
    }
}

//uint32_t

//unsigned int crc32(unsigned char *message)
//{
//    int i, j;
//    unsigned int byte, crc, mask;
//
//    i = 0;
//    crc = 0xFFFFFFFF;
//    while (message[i] != 0) {
//        byte = message[i]; // Get next byte.
//        crc = crc ^ byte;
//        for (j = 7; j >= 0; j--) { // Do eight times.
//            mask = -(crc & 1);
//            crc = (crc >> 1) ^ (0xEDB88320 & mask);
//        }
//        i = i + 1;
//    }
//    return ~crc;
//}

uint16_t crc_tools_ccitt_get_initial_value()
{
    return 0xFFFF;
}

uint16_t crc_tools_ccitt_update(uint16_t crc, uint8_t byte)
{
    byte ^= (uint8_t) (crc & 0xFF);
    byte ^= byte << 4;

    return ((((uint16_t)byte << 8) | (uint8_t) (crc >> 8)) ^ (uint8_t)(byte >> 4)
            ^ ((uint16_t)byte << 3));
}

uint16_t crc_tools_ccitt_calculate(uint8_t bytes[], uint16_t size)
{
    uint16_t crc = crc_tools_ccitt_get_initial_value();
    uint16_t i;

    for(i = 0; i < size; i++)
    {
        crc = crc_tools_ccitt_update(crc, bytes[i]);
    }
    return crc;
}

uint16_t crc_tools_xmodem_update(uint16_t crc, uint8_t byte)
{
    int i;
    crc = crc ^ ((uint16_t) byte << 8);
    for (i = 0; i < 8; i++) {
        if (crc & 0x8000)
            crc = (crc << 1) ^ 0x1021;
        else
            crc <<= 1;
    }
    return crc;
}

uint8_t crc_tools_ibutton_update(uint8_t crc, uint8_t byte)
{
    uint8_t i;

    crc = crc ^ byte;
    for (i = 0; i < 8; i++)
    {
        if (crc & 0x01)
            crc = (crc >> 1) ^ 0x8C;
        else
            crc >>= 1;
    }

    return crc;
}

uint8_t crc_tools_ibutton_get_initial_value()
{
    return 0;
}

uint8_t crc_tools_ibutton_calculate(uint8_t bytes[], uint8_t size)
{
    uint8_t crc = crc_tools_ibutton_get_initial_value();
    uint8_t i;

    for (i = 0; i < size; i++)
    {
        crc = crc_tools_ibutton_update(crc, bytes[i]);
    }

    return crc;
}
