/*
 * CommVar.h
 *
 *  Created on: Feb 28, 2021
 *      Author: marcin
 */

#ifndef CLASSES_COMMVAR_COMMVAR_H_
#define CLASSES_COMMVAR_COMMVAR_H_

#include "stdint.h"
#include "ICommVar.h"
#include "commands.h"

template<typename T>
class CommVar: public ICommVar
{
public:
	CommVar(): command(0), data(0), newValue(false)
	{
	}
	CommVar(uint8_t _comm, T _data) :
			command(_comm), data(_data), newValue(false)
	{
	}
	virtual ~CommVar()
	{
	}
	void setCommand(uint8_t _comm)
	{
		command = _comm;
	}
	bool isNewValue()
	{
		return newValue;
	}
	uint8_t getSize()
	{
		return sizeof(T);
	}
	uint8_t getCommand()
	{
		return command;
	}
	uint8_t* getData()
	{
		return (uint8_t*) &data;
	}
	void setData(T _data)
	{
		data = _data;
		newValue = true;
	}
	void clear()
	{
		newValue = false;
	}
private:
	uint8_t command;
	T data;
	bool newValue;
};

#endif /* CLASSES_COMMVAR_COMMVAR_H_ */
