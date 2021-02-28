#ifndef WTP3_RFM22FRAME_H_
#define WTP3_RFM22FRAME_H_

#include <stdint.h>
#include "prot3buff.h"

typedef enum {FRS_IDLE, FRS_TX, FRS_RX_WAIT, FRS_RX} rfm22frame_state_t;

#define RFM22FRAME_TX_ALMOST_EMPTY_THRESHOLD                                31
#define RFM22FRAME_RX_ALMOST_FULL_THRESHOLD                                 32

void rfm22frame_init(uint8_t long_delay, uint16_t (*package_size_getter)(), uint16_t package_size_threshold);
prot3buff_t *rfm22frame_get_tx_buff();
prot3buff_t *rfm22frame_get_rx_buff();
rfm22frame_state_t rfm22frame_get_state();
uint8_t rfm22frame_is_tx_error();
uint8_t rfm22frame_is_rx_error();
uint8_t rfm22frame_is_rx_callback_error();
uint8_t rfm22frame_is_general_error();
void rfm22frame_clear_error_flags();
void rfm22frame_clear_tx_error_flags();
void rfm22frame_clear_rx_error_flags();
void rfm22frame_clear_rx_callback_error_flags();
void rfm22frame_clear_general_error_flags();
uint8_t rfm22frame_get_signal_strength();

void rfm22frame_update();
void rfm22frame_start_tx();
void rfm22frame_start_rx_waiting(uint8_t low_duty_cycle_mode);
void rfm22frame_stop_rx_waiting();

/**
 *  @brief   Interrupt routine
 *
 *  Configure interrupt as falling edge. Clear interrupt flag in uC after calling this function
 */
void rfm22frame_isr();

#endif /* WTP3_RFM22FRAME_H_ */
