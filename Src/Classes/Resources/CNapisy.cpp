/*
 * CNapisy.h
 *
 *  Created on: Sep 29, 2015
 *      Author: krzysiek
 */

#include "CNapisy.h"

const uint8_t CNapisy::FLASH_DATA[] = {
#include "flashCPU.h"
        };

int8_t CNapisy::getLanguageVersion(uint16_t language)
{
    typedef enum
    {
#include "languageIdEnum.h"
    } TWersjaJezykowa;

    switch (language)
    {
        case JEZYK_POLSKI:
            return pl;

//        case JEZYK_ANGIELSKI:
//            return gbr;

//        case JEZYK_CZESKI:
//            return cze;
//
//        case JEZYK_SLOWACKI:
//            return svk;
//
//        case JEZYK_NIEMIECKI:
//            return deu;
//
//        case JEZYK_WEGIERSKI:
//            return hun;
//
//        case JEZYK_UKRAINSKI:
//            return ukr;
//
//        case JEZYK_ROSYJSKI:
//            return rus;
//
//        case JEZYK_FRANCUSKI:
//            return fra;
//
//        case JEZYK_BULGARSKI:
//            return bgr;
//
//        case JEZYK_LITEWSKI:
//            return lt;
//
//        case JEZYK_WLOSKI:
//            return ita;
//
//        case JEZYK_ESTONSKI:
//            return est;
//
//        case JEZYK_LOTEWSKI:
//            return lva;
//
//        case JEZYK_SLOWENSKI:
//            return svn;
//
//        case JEZYK_HISZPANSKI:
//            return esp;
//
//        case JEZYK_SZWEDZKI:
//            return swe;
//
//        case JEZYK_FINSKI:
//            return fin;
//
//        case JEZYK_GRECKI:
//            return grc;
//
//        case JEZYK_RUMUNSKI:
//            return rou;
//
//        case JEZYK_NIDERLANDZKI:
//            return nld;
//
//        case JEZYK_DUNSKI:
//            return dnk;
//
//        case JEZYK_SERBSKI:
//            return srb;
//
//        case JEZYK_ALBANSKI:
//            return alb;
//
//        case JEZYK_MACEDONSKI:
//            return mkd;
//
//        case JEZYK_CHORWACKI:
//            return hrv;
//
//        case JEZYK_CHINSKI:
//            return chn;
//
//        case JEZYK_MOLDAWSKI:
//            return mda;

//        default:
//            return gbr;
    }
}
