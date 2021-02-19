/*
 * IBuzzer.h
 *
 *  Created on: Oct 14, 2014
 *      Author: krzysiek
 */

#ifndef IBUZZER_H_
#define IBUZZER_H_

#include <stdint.h>

class IBuzzer
{
public:
    virtual void beep(uint16_t milliseconds) = 0;
};

#endif /* IBUZZER_H_ */
