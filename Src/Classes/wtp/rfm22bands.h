/*
 * rfm22bands.h
 *
 *  Created on: 31 paź 2013
 *      Author: Maciek
 */

#ifndef RFM22BANDS_H_
#define RFM22BANDS_H_

#include <stdint.h>
#include "rfm22_registers.h"

#define RFM22BANDS_FIRST_USER_CHANNEL               0U      /*don't change this*/
#define RFM22BANDS_LAST_USER_CHANNEL                55U     /*don't change this*/

#define RFM22BANDS_DEFAULT_CHANNEL              49          /*abs. default channel, use in rfm22callbacks.cpp only*/
#define RFM22BANDS_DEFAULT_POWER                RFM22_TX_POWER_17_DBM

//common
void    rfm22bands_init();
void    rfm22bands_set_user_channel(uint8_t channel);
int16_t rfm22bands_get_user_channel();
int16_t rfm22bands_get_default_user_channel();
void    rfm22bands_set_developer_channel(uint8_t channel);
int16_t rfm22bands_get_developer_channel();
int16_t rfm22bands_get_default_developer_channel();
void    rfm22bands_set_choose_channel();
void    rfm22bands_set_power(int16_t power);
int16_t rfm22bands_get_power();

#endif /* RFM22BANDS_H_ */
