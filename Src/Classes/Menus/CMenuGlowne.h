/*
 * CMenuGlowne.h
 *
 *  Created on: 4 lip 2016
 *      Author: marmur
 */

#ifndef CMENUGLOWNE_H_
#define CMENUGLOWNE_H_

#include "AMenuList.h"
#include "IUpdatable.h"
#include "timer.h"

class CMenuGlowne: public AMenuList, IUpdatable
{
    static const SMenuItem MENU_ITEMS[];
public:
    CMenuGlowne();
    void updateItem(SMenuItem *menuItem);
    void onItemSelected(SMenuItem *menuItem);

public:
    void update();
};

#endif /* CMENUGLOWNE_H_ */
