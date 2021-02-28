/*
 * rfm22profiles.h
 *
 *  Created on: 4 lis 2013
 *      Author: Maciek
 */

#ifndef RFM22PROFILES_H_
#define RFM22PROFILES_H_

#include <stdint.h>


typedef struct
{
    //carrier freqency
    uint8_t reg75;
    uint8_t reg76;
    uint8_t reg77;

    //tx data rate
    uint8_t reg6E;
    uint8_t reg6F;
    uint8_t reg70;
    uint8_t reg58;  /*ignored*/

    //tx frequency deviation
    uint8_t reg72;
    uint8_t reg71;

    //rx (G)FSK and OOK
    uint8_t reg1C;
    uint8_t reg20;
    uint8_t reg21;
    uint8_t reg22;
    uint8_t reg23;
    uint8_t reg24;
    uint8_t reg25;
    uint8_t reg1F;
    uint8_t reg69;

    //rx (G)FSK
    uint8_t reg1D;
    uint8_t reg1E;
    uint8_t reg2A;

    //rx OOK
    uint8_t reg2C;
    uint8_t reg2D;
    uint8_t reg2E;
} rfm22profiles_regs_t;

void rfm22profiles_fill_standard_profile(rfm22profiles_regs_t *regs);

#endif /* RFM22PROFILES_H_ */

