#ifndef WTP3DRIVERCALLS_H_
#define WTP3DRIVERCALLS_H_

#include <stdint.h>

void wtp3drivercalls_setTimer(uint8_t nr, uint32_t ms);
uint8_t wtp3drivercalls_isTimerZero(uint8_t nr);
void wtp3drivercalls_updateCounters();


#endif /* WTP3DRIVERCALLS_H_ */
