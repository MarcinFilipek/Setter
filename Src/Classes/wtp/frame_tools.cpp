#include "frame_tools.h"


void frame_tools_uint32_to_bytes_LSB(uint32_t value, uint8_t bytes[])
{
    int8_t i;

    for(i = 0; i < 4; i++)
    {
        bytes[i] = (uint8_t)value;
        value >>= 8;
    }
}

uint32_t frame_tools_bytes_LSB_to_uint32(uint8_t bytes[])
{
    int8_t i;
    uint32_t result = 0;

    for(i = 3; i >= 0; i--)
    {
        result <<= 8;
        result |= bytes[i];
    }
    return result;
}

void frame_tools_uint16_to_bytes_LSB(uint16_t value, uint8_t bytes[])
{
    bytes[0] = (uint8_t)value;
    bytes[1] = (uint8_t)(value >> 8);
}

uint16_t frame_tools_bytes_LSB_to_uint16(uint8_t bytes[])
{
    uint16_t result;

    result = bytes[0] | (bytes[1] << 8);
    return result;
}

void frame_tools_uint16_to_bytes_MSB(uint16_t value, uint8_t bytes[])
{
    bytes[0] = (uint8_t)(value >> 8);
    bytes[1] = (uint8_t)value;
}

uint16_t frame_tools_bytes_MSB_to_uint16(uint8_t bytes[])
{
    uint16_t result;

    result = (bytes[0] << 8) | bytes[1];
    return result;
}

uint16_t frame_tools_int16_to_nbit_compl(int16_t value, uint8_t nbits)
{
    uint16_t mask = (uint16_t)0xFFFF >> (16 - nbits);       //nbit mask right-aligned

    return (uint16_t)value & mask;
}

int16_t frame_tools_nb_compl_to_int16(uint16_t value, uint8_t nbits)
{
    uint16_t mask = (uint16_t)0xFFFF << nbits;              //(16 - nbit) mask left_aligned
    uint16_t sign_bit = (uint16_t)1 << (nbits - 1);

    if(value & sign_bit)
    {
        value |= mask;
    }
    return (int16_t)value;
}

void frame_tools_rotate_uint16_t(uint16_t *value)
{
    uint16_t result;
    uint8_t *result_ptr = (uint8_t*)&result;
    uint8_t *value_ptr = (uint8_t*)value;

    result_ptr[1] = value_ptr[0];
    result_ptr[0] = value_ptr[1];

    *value = result;
}

void frame_tools_rotate_int16_t(int16_t *value)
{
    frame_tools_rotate_uint16_t((uint16_t*)value);
}

void frame_tools_rotate_uint32_t(uint32_t *value)
{
    uint32_t result;
    uint8_t *result_ptr = (uint8_t*)&result;
    uint8_t *value_ptr = (uint8_t*)value;
    uint8_t i;

    for(i = 0; i < 4; i++)
    {
        result_ptr[3 - i] = value_ptr[i];
    }

    *value = result;
}

void frame_tools_rotate_int32_t(int32_t *value)
{
    frame_tools_rotate_uint32_t((uint32_t*)value);
}









