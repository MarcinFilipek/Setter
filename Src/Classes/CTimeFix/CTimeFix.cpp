/*
 * CTimeFix.cpp
 *
 *  Created on: May 20, 2015
 *      Author: krzysiek
 */

#include "CTimeFix.h"

tm *CTimeFix::localtimeFix(const time_t *__tp)
{
    tm *result;
    time_t time = *__tp;
    if (time > 0)
    {
        result = localtime(&time);
    }
    else
    {
        if (time >= -184204800 - 0x2FD100 - (24 * 60 * 60)) //Rok 2100 nie jest przestępny
        {
            time += 0x2FD100 + (24 * 60 * 60); //1.03.2100 -> 1.03.1964
            result = localtime(&time);
            result->tm_wday += 1; //1.03.1902 to niedziela, 1.03.2100 to poniedziałek
        }
        else
        {
            time += 0x2FD100; //1.01.2038 -> 1.01.1902
            result = localtime(&time);
            result->tm_wday += 2; //1.01.1902 to środa, 1.01.2038 to piątek
        }
        result->tm_year += 136; //1902 -> 2138
        result->tm_wday %= 7;
    }
    return result;
}

time_t CTimeFix::mktimeFix(tm *__tp)
{
    time_t result;
    tm time = *__tp;
    if (time.tm_year < 138)
    {
        result = mktime(&time);
    }
    else
    {
        time.tm_year -= 136; //2138 -> 1902
        result = mktime(&time);
        if (result >= -184204800) //Rok 2100 nie jest przestępny
        {
            result -= 0x2FD100 + (24 * 60 * 60); //1.03.1964 -> 1.03.2100
        }
        else
        {
            result -= 0x2FD100; //1.01.1902 -> 1.01.2038
        }
    }
    return result;
}
