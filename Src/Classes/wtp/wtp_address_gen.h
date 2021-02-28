#ifndef WTP_ADDRESS_GEN_H_
#define WTP_ADDRESS_GEN_H_

#include "stdint.h"

void     wtp_address_gen_init();
uint32_t wtp_address_gen_get_address();
void     wtp_address_gen_set_address(uint32_t address);

#endif /* WTP_ADDRESS_GEN_H_ */
