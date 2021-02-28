/*
 * rfm22callbacks.h
 *
 *  Created on: 4 lis 2013
 *      Author: Maciek
 */

#ifndef RFM22CALLBACKS_H_
#define RFM22CALLBACKS_H_

#include <stdint.h>

/*** rfm22bands callbacks ***/
void    rfm22callbacks_set_channel(uint8_t channel);
uint8_t rfm22callbacks_get_channel();
void    rfm22callbacks_set_power(uint8_t power);
uint8_t rfm22callbacks_get_power();
void    rfm22callbacks_delay_ms(uint16_t ms);


#endif /* RFM22CALLBACKS_H_ */
