/*
 * rfm22profiles.c
 *
 *  Created on: 4 lis 2013
 *      Author: Maciek
 */

#include <stdint.h>
#include <string.h>
#include "rfm22profiles.h"

#ifndef dim
    #define dim(x) (sizeof(x)/sizeof(x[0]))
#endif


/*
 * Internal profiles
 * Modify these definitions to place profiles in flash or eeprom
 */

static const rfm22profiles_regs_t rfm22profiles_standard_profile =
{
        0x73, 0x26, 0x20,         //carrier frequency
        0x0A, 0x3D, 0x0C, 0x80,   //tx data rate
        0x30, 0x23,               //tx frequency deviation
        0x05, 0x64, 0x01, 0x47, 0xAE, 0x03, 0x6C, 0x03, 0x60,     //rx (G)FSK and OOK
        0x40, 0x0A, 0x28,         //rx (G)FSK
        0x28, 0x1F, 0x27,         //rx OOK
};

//private functions
void rfm22profiles_internal2external_profile(const rfm22profiles_regs_t *intPr, rfm22profiles_regs_t *extPr);


/*
 * Modify to copy profiles correctly from flash or eeprom
 * Copies profile from pernament memory to ram
 *
 * param intPr    pointer to rfm22profiles_regs_t located in pernament memory, ex. eeprom
 * param extPr    pointer to ram
 */
void rfm22profiles_internal2external_profile(const rfm22profiles_regs_t *intPr, rfm22profiles_regs_t *extPr)
{
	memcpy(extPr, intPr, sizeof(rfm22profiles_regs_t));
}

/**
 * Don't modify funtions below
 */

void rfm22profiles_fill_standard_profile(rfm22profiles_regs_t *regs)
{
    rfm22profiles_internal2external_profile(&rfm22profiles_standard_profile, regs);
}


