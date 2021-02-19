/*
 * IUpdatable.h
 *
 *  Created on: Aug 20, 2014
 *      Author: krzysiek
 */

#ifndef IUPDATABLE_H_
#define IUPDATABLE_H_

/**
 * Interfejs dla klas z metodą update.
 */
class IUpdatable
{
public:
    /**
     * Metoda przeznaczona do cyklicznego wywoływania.
     */
    virtual void update() = 0;
};

#endif /* IUPDATABLE_H_ */
