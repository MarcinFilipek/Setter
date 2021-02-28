#include "wtp_address_srv.h"

/**
 * Modify for your platform to save data pernamently and read
 * Address must be inited with WTP_ADDRESS_UNINITIALIZED when run first time
 */
#define WTP_ADDRESS_SRV_CHIP_ID_BASE_ADDRESS   0x1FFFF7E8

static uint32_t wtp_address_srv_addr = WTP_ADDRESS_UNINITIALIZED;

uint32_t wtp_address_srv_get_address()
{
    return wtp_address_srv_addr;
}

void wtp_address_srv_set_address(uint32_t address)
{
    wtp_address_srv_addr = address;
}

uint8_t wtp_address_srv_get_chip_id(uint8_t byte_index)
{
    uint8_t *id_ptr = (uint8_t*)WTP_ADDRESS_SRV_CHIP_ID_BASE_ADDRESS;

    if(byte_index < WTP_ADDRESS_SRV_CHIP_ID_BYTES)
    {
        return id_ptr[byte_index];
    }
    return 0;
}

uint8_t wtp_address_srv_get_chip_id_size()
{
    return WTP_ADDRESS_SRV_CHIP_ID_BYTES;
}
