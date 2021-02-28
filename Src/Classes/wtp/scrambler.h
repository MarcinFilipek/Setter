#ifndef SCRAMBLER_H_
#define SCRAMBLER_H_

#include <stdint.h>

typedef struct
{
    uint8_t state;
} scrambler_t;

void scrambler_reset_state(scrambler_t *ob);
uint8_t scrambler_update(scrambler_t *ob, uint8_t byte);
uint8_t descrambler_update(scrambler_t *ob, uint8_t byte);


#endif /* SCRAMBLER_H_ */
