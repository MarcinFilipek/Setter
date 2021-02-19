/*
 * AScreen.cpp
 *
 *  Created on: Sep 30, 2015
 *      Author: krzysiek
 */

#include "AScreen.h"
#include "CContext.h"

void AScreen::finish()
{
    CContext::finishScreen(this);
}

void AScreen::resume()
{
    CContext::redraw();
}

void AScreen::onStart()
{
}

void AScreen::onResume()
{
}

void AScreen::onPause()
{
}

void AScreen::onStop()
{
}
