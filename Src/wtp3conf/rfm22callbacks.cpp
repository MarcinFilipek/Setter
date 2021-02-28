/*
 * rfm22callbacks.cpp
 *
 *  Created on: 4 lis 2013
 *      Author: Maciek
 */

#include "rfm22callbacks.h"
#include "rfm22bands.h"
#include "hal.h"

/**
 * Modify this file to save data pernamently, e.g. in eeprom
 */

static const uint8_t rfm22callbacks_channel = RFM22BANDS_DEFAULT_CHANNEL;
static const uint8_t rfm22callbacks_power = RFM22BANDS_DEFAULT_POWER;

/*channel*/
/*--------------------------------------------------------------------*/
void rfm22callbacks_set_channel(uint8_t channel)
{

}

/*--------------------------------------------------------------------*/
uint8_t rfm22callbacks_get_channel()
{
    return rfm22callbacks_channel;
}

/*--------------------------------------------------------------------*/
void rfm22callbacks_set_power(uint8_t power)
{

}

/*--------------------------------------------------------------------*/
uint8_t rfm22callbacks_get_power()
{
    return rfm22callbacks_power;
}

/*--------------------------------------------------------------------*/
void rfm22callbacks_delay_ms(uint16_t ms)
{
    HAL_Delay(ms);
}
