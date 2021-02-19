/*
 * CEEPROMVar.cpp
 *
 *  Created on: 18-09-2012
 *      Author: sporysz
 */

#include "CEEPROMVar.h"

using namespace CEEPROMVarConf;


bool CEEPROMMgr::shouldInitialize;
uint32_t CEEPROMMgr::alloctedData;
Ceeprom* CEEPROMMgr::eepDrvRef;
CEEPROMMgr::TEEPROMError CEEPROMMgr::eeError;
CEEPROMMgr::TEEPROMErrorCallback CEEPROMMgr::errorCallback;

uint32_t CEEPROMMgr::allocateVar(uint16_t size)
{
	uint32_t address ;
	if((EEPROM_MANAGED_BLOCK_START + alloctedData + size) <= EEPROM_MANAGED_BLOCK_END)
	{
		address = alloctedData;
		alloctedData += size;
	}else
	{
		address = 0;
		throwException(EC_EEPROMVAR_END_OF_BLOCK);
	}

	return address;
}



uint32_t CEEPROMMgr::getAllocatedBytes()
{
	return alloctedData;
}


bool CEEPROMMgr::getShouldInitialize()
{
	return shouldInitialize;
}

void CEEPROMMgr::init(Ceeprom* eepromDrv, bool forceDefaults)
{
	eepDrvRef = eepromDrv;

	if(CFlashSignature::isFristRun())
	{
		shouldInitialize = true;
	}

	if(forceDefaults)
	{
		shouldInitialize = true;
	}
}

CEEPROMMgr::TEEPROMError CEEPROMMgr::getEEPROMError()
{
    return eeError;
}

bool CEEPROMMgr::isEEPROMError()
{
    return (bool)eeError;
}

void CEEPROMMgr::setupError(bool operationFault, TEEPROMError possibleError)
{
    if(operationFault)
    {
        eeError = possibleError;
        if(errorCallback)
        {
            errorCallback(possibleError);
        }
    }else
    {
        eeError = TEE_NO_ERROR;
    }
}

void CEEPROMMgr::setEEPROMErrorCallback(TEEPROMErrorCallback ec)
{
    errorCallback = ec;
}
