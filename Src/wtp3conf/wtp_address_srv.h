#ifndef WTP_ADDRESS_SRV_H_
#define WTP_ADDRESS_SRV_H_

#include "stdint.h"
#include "wtp_address_consts.h"

//change address size if necessary
#define WTP_ADDRESS_SRV_CHIP_ID_BYTES         12

uint32_t wtp_address_srv_get_address();
void     wtp_address_srv_set_address(uint32_t address);
uint8_t  wtp_address_srv_get_chip_id(uint8_t byte_no);
uint8_t  wtp_address_srv_get_chip_id_size();

#endif /* WTP_ADDRESS_SRV_H_ */
