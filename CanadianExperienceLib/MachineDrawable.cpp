/**
 * @file MachineDrawable.cpp
 * @author Devin DeMatto
 */

#include "pch.h"
#include "MachineDrawable.h"

/**
* Draw the machine at the currently specified location
* @param graphics Graphics object to render to
*/
void MachineDrawable::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    mMachine->DrawMachine(graphics);
}

/**
 * Sets Machine to be interacted with
 * @param point point to be tested
 * @return false
 */
bool MachineDrawable::HitTest(wxPoint point)
{
    return false;
}
