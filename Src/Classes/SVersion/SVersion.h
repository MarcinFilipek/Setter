/*
 * SVersion.h
 *
 *  Created on: Oct 30, 2014
 *      Author: krzysiek
 */

#ifndef SVERSION_H_
#define SVERSION_H_

#include <stdio.h>
#include <stdint.h>

struct SVersion
{
    uint16_t major;
    uint16_t minor;
    uint16_t revision;

    SVersion();
    SVersion(uint16_t value);
    SVersion(uint16_t major, uint16_t minor, uint16_t revision);

    void init(uint16_t value);
    bool init(const char *buffer);

    void toString(char *buffer);
    uint16_t toShort();

    int8_t compareTo(const SVersion &version);
};

#endif /* SVERSION_H_ */
