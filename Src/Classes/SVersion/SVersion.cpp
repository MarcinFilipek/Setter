/*
 * SVersion.cpp
 *
 *  Created on: Oct 30, 2014
 *      Author: krzysiek
 */

#include "SVersion.h"

SVersion::SVersion():
        major(0), minor(0), revision(0)
{
}

SVersion::SVersion(uint16_t value)
{
    init(value);
}

SVersion::SVersion(uint16_t major, uint16_t minor, uint16_t revision) :
        major(major), minor(minor), revision(revision)
{
}

void SVersion::init(uint16_t value)
{
    major = value >> 12;
    minor = (value >> 8) & 0x0F;
    revision = value & 0xFF;
}

bool SVersion::init(const char* buffer)
{
    int32_t tmp[3];
    int32_t success = sscanf(buffer, "%d.%d.%d", &tmp[0], &tmp[1], &tmp[2]);

    if (success == 3)
    {
        major = tmp[0];
        minor = tmp[1];
        revision = tmp[2];
        return true;
    }

    return false;
}

void SVersion::toString(char* buffer)
{
    sprintf(buffer, "%d.%d.%d", major, minor, revision);
}

uint16_t SVersion::toShort()
{
    return (major << 12) | ((minor & 0x0F) << 8) | ((revision & 0xFF) << 0);
}

int8_t SVersion::compareTo(const SVersion &version)
{
    if (version.major < major)
        return 1;

    if (version.major > major)
        return -1;

    if (version.minor < minor)
        return 1;

    if (version.minor > minor)
        return -1;

    if (version.revision < revision)
        return 1;

    if (version.revision > revision)
        return -1;

    return 0;
}
