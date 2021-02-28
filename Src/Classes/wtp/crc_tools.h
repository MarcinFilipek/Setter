#ifndef CRC_TOOLS_H_
#define CRC_TOOLS_H_

#include "stdint.h"

uint32_t crc_tools_32_get_initial_value();
uint32_t crc_tools_32_get_residue();
uint32_t crc_tools_32_final_xor(uint32_t crc);
uint32_t crc_tools_32_calculate(uint8_t bytes[], uint16_t size, uint8_t complement);
uint32_t crc_tools_32_partial_calculate(uint32_t crc, uint8_t bytes[], uint16_t size);
void     crc_tools_32_crc_2_bytes_lsb_first(uint32_t crc, uint8_t bytes[]);
uint16_t crc_tools_ccitt_get_initial_value();
uint16_t crc_tools_ccitt_update(uint16_t crc, uint8_t byte);
uint16_t crc_tools_ccitt_calculate(uint8_t bytes[], uint16_t size);
uint16_t crc_tools_xmodem_update(uint16_t crc, uint8_t byte);
uint8_t crc_tools_ibutton_update(uint8_t crc, uint8_t byte);
uint8_t crc_tools_ibutton_get_initial_value();
uint8_t crc_tools_ibutton_calculate(uint8_t bytes[], uint8_t size);

#endif /* CRC_TOOLS_H_ */
