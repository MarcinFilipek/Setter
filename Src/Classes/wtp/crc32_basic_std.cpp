#include "crc32_basic.h"


uint32_t crc32_basic_update(uint32_t crc, uint8_t byte)
{
    uint32_t mask;
    int8_t j;

    crc = crc ^ byte;
    for (j = 7; j >= 0; j--)
    {
        mask = -(crc & 1);
        crc = (crc >> 1) ^ (0xEDB88320UL & mask);
    }
    return crc;
}
