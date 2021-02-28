#ifndef RFM22_PORTS_H_
#define RFM22_PORTS_H_

//#include "uc.h"
//include header for uint8_t and similar types
#include <stdint.h>

#define RFM22PORTS_RESET_SDN    1
#define RFM22PORTS_RESET_VCC    2
#define RFM22PORTS_RESET_SOFT   3

//SPI
void rfm22ports_deinitSPI();
void rfm22ports_initSPI();
//void rfm22ports_setMOSI(uint8_t value);
//void rfm22ports_setSCK(uint8_t value);
//void rfm22ports_setSS(uint8_t value);
//uint8_t rfm22ports_isMISOActive();

void rfm22ports_initVccPort();
void rfm22ports_setVcc(uint8_t value);
void rfm22ports_initSDNPort();
void rfm22ports_setSDN(uint8_t value);
uint8_t rfm22ports_getResetMethod();
void rfm22ports_initIntPort();
void rfm22ports_activateInt();
void rfm22ports_deactivateInt();
void rfm22ports_clearIntFlag();
uint8_t rfm22ports_isINTActive();

//KOMUNIKACJA PRZEZ SPI
#define RFM22_WRITE_FLAG                     0x80U
#define RFM22_READ_FLAG                      0x00U

uint8_t rfm22ports_trans(uint8_t address, uint8_t value);
void rfm22ports_burst(uint8_t address, uint8_t length, uint8_t *values);

#define rfm22ports_trans_read(address)                                rfm22ports_trans(RFM22_READ_FLAG | (address), 0)
#define rfm22ports_trans_write(address, value)                        rfm22ports_trans(RFM22_WRITE_FLAG | (address), value)
#define rfm22ports_burst_read(address, length, values)                rfm22ports_burst(RFM22_READ_FLAG | (address), length, values)
#define rfm22ports_burst_write(address, length, values)               rfm22ports_burst(RFM22_WRITE_FLAG | (address), length, values)

#endif /* RFM22_PORTS_H_ */
