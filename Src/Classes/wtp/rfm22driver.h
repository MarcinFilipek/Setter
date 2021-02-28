#ifndef RFM22DRIVER_H
#define RFM22DRIVER_H

#include <stdint.h>

//interrupt enable1
#define   RFM22DRIVER_IN1_FIFO_FLOW         (1 << 7)
#define   RFM22DRIVER_IN1_TX_FIFO_AL_FULL   (1 << 6)
#define   RFM22DRIVER_IN1_TX_FIFO_AL_EMPTY  (1 << 5)
#define   RFM22DRIVER_IN1_RX_FIFO_AL_FULL   (1 << 4)
#define   RFM22DRIVER_IN1_PACKET_SENT       (1 << 2)
#define   RFM22DRIVER_IN1_VALID_PACKET_REC  (1 << 1)

//interrupt enable2
#define   RFM22DRIVER_IN2_SYNC_WORD_DET     (1 << 7)
#define   RFM22DRIVER_IN2_RSSI              (1 << 4)
#define   RFM22DRIVER_IN2_WAKE_UP_TIMER     (1 << 3)

//Operating mode and function control 1
#define   RFM22DRIVER_OP1_SOFTWARE_RESET    (1 << 7)
#define   RFM22DRIVER_OP1_WAKE_UP_TIMER     (1 << 5)
#define   RFM22DRIVER_OP1_TX_ON             (1 << 3)
#define   RFM22DRIVER_OP1_RX_ON             (1 << 2)
#define   RFM22DRIVER_OP1_PLL_ON            (1 << 1)
#define   RFM22DRIVER_OP1_XTAL_ON           (1 << 0)

//Operating mode and function control 2
#define   RFM22DRIVER_OP2_LOW_DUTY_MODE     (1 << 2)
#define   RFM22DRIVER_OP2_RX_FIFO_CLEAR     (1 << 1)
#define   RFM22DRIVER_OP2_TX_FIFO_CLEAR     (1 << 0)

void      rfm22driver_init(uint8_t long_delay);
//void      rfm22driver_update();
void      rfm22driver_clear_fifo();
void      rfm22driver_interrupt_enable(uint8_t enable1, uint8_t enable2);

uint8_t   rfm22driver_trans_read(uint8_t address);
void      rfm22driver_trans_write(uint8_t address, uint8_t value);
void      rfm22driver_burst_read(uint8_t address, uint8_t length, uint8_t *values);
void      rfm22driver_burst_write(uint8_t address, uint8_t length, uint8_t *values);

uint8_t rfm22driver_compute_package_crc(uint8_t package[], uint8_t length);

#endif /*RFM22DRIVER_H*/
