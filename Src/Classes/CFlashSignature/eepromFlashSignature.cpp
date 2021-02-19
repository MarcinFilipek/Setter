/*
 * eepromFlashSignature.cpp
 *
 *  Created on: 04-07-2012
 *      Author: Marcin Sporysz
 *     Version: 1.0.1
 */

#if !defined DEF_HAL_F1 && !defined DEF_HAL_F2 && !defined DEF_HAL_F4
    #define DEF_HAL_F2
#endif

#include "eepromFlashSignature.h"
#ifdef DEF_HAL_F1
	#include "stm32f1xx_hal.h"
    #include "stm32f1xx_hal_flash.h"
#elif defined DEF_HAL_F2
    #include "stm32f2xx_hal_flash.h"
#elif defined DEF_HAL_F4
    #include "stm32f4xx_hal_flash.h"
#endif

const volatile uint16_t CFlashSignature::SIGNATURE = 0xFFFF;

bool CFlashSignature::isFristRun()
{
    return SIGNATURE;
}

CFlashSignature::TFlashUpdResult CFlashSignature::setSignature()
{
    TFlashUpdResult res;

    if (isFristRun())
    {
        HAL_FLASH_Unlock();
        HAL_StatusTypeDef status = HAL_FLASH_Program(TYPEPROGRAM_HALFWORD, (uint32_t) &SIGNATURE, 0);
        HAL_FLASH_Lock();
        status == HAL_OK ? res = TFUR_SUCCESS : res = TFUR_ERROR;
    }
    else
    {
        res = TFUR_ALREADY_SET;
    }

    return res;
}

