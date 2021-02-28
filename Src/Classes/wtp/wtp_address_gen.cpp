#include "wtp_address_gen.h"
#include "wtp_address_srv.h"
#include "crc_tools.h"

//private
uint32_t wtp_address_gen_generate();
void     wtp_address_gen_copy_chip_id(uint8_t array[], uint8_t start_index);

void wtp_address_gen_init()
{
    if(wtp_address_srv_get_address() == WTP_ADDRESS_UNINITIALIZED)
    {
        wtp_address_srv_set_address(wtp_address_gen_generate());
    }
}

uint32_t wtp_address_gen_get_address()
{
    return wtp_address_srv_get_address();
}

void wtp_address_gen_set_address(uint32_t address)
{
    wtp_address_srv_set_address(address);
}

//private
uint32_t wtp_address_gen_generate()
{
    uint8_t chip_id_arr[WTP_ADDRESS_SRV_CHIP_ID_BYTES];
    uint32_t crc32;
    uint8_t i;
    uint8_t found = 0;

    for(i = 0; i < WTP_ADDRESS_SRV_CHIP_ID_BYTES; i++)
    {
        wtp_address_gen_copy_chip_id(chip_id_arr, i);
        crc32 = crc_tools_32_calculate(chip_id_arr, WTP_ADDRESS_SRV_CHIP_ID_BYTES, 0);
        if((crc32 != WTP_ADDRESS_FORBIDDEN_1) && (crc32 != WTP_ADDRESS_FORBIDDEN_2))
        {
            found = 1;
            break;
        }
    }
    if(!found)
    {
        crc32 = 1;
    }
    return crc32;
}

void wtp_address_gen_copy_chip_id(uint8_t array[], uint8_t start_index)
{
    uint8_t i;

    if(start_index < WTP_ADDRESS_SRV_CHIP_ID_BYTES)
    {
        for(i = 0; i < WTP_ADDRESS_SRV_CHIP_ID_BYTES; i++)
        {
            array[i] = wtp_address_srv_get_chip_id(start_index);
            if(++start_index >= WTP_ADDRESS_SRV_CHIP_ID_BYTES)
            {
                start_index = 0;
            }
        }
    }
}

