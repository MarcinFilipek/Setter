#ifndef FRAME_TOOLS_H_
#define FRAME_TOOLS_H_

#include "stdint.h"

/**
 * LSB - LSB byte first
 * MSB - MSB byte first
 *
 * nbit comp - n-bit 2's complement where n is 1..16 bits. In int16_t 15th bit is sign bit
 *             and here nth bit becomes sign bit
 */

void frame_tools_uint32_to_bytes_LSB(uint32_t value, uint8_t bytes[]);
uint32_t frame_tools_bytes_LSB_to_uint32(uint8_t bytes[]);

void frame_tools_uint16_to_bytes_LSB(uint16_t value, uint8_t bytes[]);
uint16_t frame_tools_bytes_LSB_to_uint16(uint8_t bytes[]);

void frame_tools_uint16_to_bytes_MSB(uint16_t value, uint8_t bytes[]);
uint16_t frame_tools_bytes_MSB_to_uint16(uint8_t bytes[]);

uint16_t frame_tools_int16_to_nbit_compl(int16_t value, uint8_t nbits);
int16_t frame_tools_nb_compl_to_int16(uint16_t value, uint8_t nbits);

void frame_tools_rotate_uint16_t(uint16_t *value);
void frame_tools_rotate_int16_t(int16_t *value);
void frame_tools_rotate_uint32_t(uint32_t *value);
void frame_tools_rotate_int32_t(int32_t *value);

#endif /* FRAME_TOOLS_H_ */
