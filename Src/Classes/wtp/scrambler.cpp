#include "scrambler.h"


uint8_t scrambler_get_init_value()
{
    return 0x7F;
}

void scrambler_reset_state(scrambler_t *ob)
{
    ob->state = scrambler_get_init_value();
}

uint8_t scrambler_update(scrambler_t *ob, uint8_t byte)
{
    //7-bit scrambler, MSb (0b10000000 bit) not used

    //input: LSb first
    //state: LSb is x^-7 bit
    //right-shifting

    uint8_t mask;
    uint8_t i;

    for(i = 0; i < 8; i++)
    {
        mask = -((ob->state ^ (ob->state >> 3) ^ byte) & 0x01);
        ob->state = (ob->state >> 1) | (mask & 0x40);
        byte = (byte >> 1) | (mask & 0x80);
    }
    return byte;
}

uint8_t descrambler_update(scrambler_t *ob, uint8_t byte)
{
    //7-bit scrambler, MSb (0b10000000 bit) not used

    //input: LSb first
    //state: LSb is x^-7 bit
    //right-shifting

    uint8_t mask;
    uint8_t i;

    for(i = 0; i < 8; i++)
    {
        mask = -((ob->state ^ (ob->state >> 3) ^ byte) & 0x01);
        ob->state = (ob->state >> 1) | (-(byte & 0x01) & 0x40);
        byte = (byte >> 1) | (mask & 0x80);
    }
    return byte;
}
