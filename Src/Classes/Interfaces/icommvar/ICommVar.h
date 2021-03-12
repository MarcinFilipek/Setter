/*
 * ICommVar.h
 *
 *  Created on: Mar 1, 2021
 *      Author: marcin
 */

#ifndef CLASSES_INTERFACES_ICOMMVAR_ICOMMVAR_H_
#define CLASSES_INTERFACES_ICOMMVAR_ICOMMVAR_H_

#include "stdint.h"

class ICommVar
{
public:
	ICommVar()
	{
	}
	virtual ~ICommVar()
	{
	}
	virtual bool isNewValue() = 0;
	virtual uint8_t getSize() = 0;
	virtual uint8_t getCommand() = 0;
	virtual uint8_t* getDataPtr() = 0;
	virtual void clear() = 0;

};

#endif /* CLASSES_INTERFACES_ICOMMVAR_ICOMMVAR_H_ */
