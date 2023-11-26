/**
 * @file MachineSystem.cpp
 * @author Devin DeMatto
 */

#include "pch.h"
#include "MachineSystem.h"
#include "MachineActual.h"
#include "MachineCFactory.h"
#include "Machine1Factory.h"

/**
 * Constructor
 * @param resourcesDir Resource Directory Path
 */
MachineSystem::MachineSystem(std::wstring resourcesDir) : mResourcesDir(resourcesDir)
{
    SetMachineNumber(1);
}

/**
 * Set Location of Machine
 * @param location wxPoint
 */
void MachineSystem::SetLocation(wxPoint location)
{
    mLocation = location;
}

/**
 * Get Location of Machine
 * @return wxPoint
 */
wxPoint MachineSystem::GetLocation()
{
    return mLocation;
}

/**
 * Draws the Machine
 * @param graphics Graphics Context
 */
void MachineSystem::DrawMachine(std::shared_ptr<wxGraphicsContext> graphics)
{
    graphics->PushState();
    graphics->Translate(mLocation.x, mLocation.y);
    graphics->Scale(mPixelsPerCentimeter, -mPixelsPerCentimeter);

    mMachine->Draw(graphics);

    graphics->PopState();
}

/**
 * Set Current Frame of Machine
 * @param frame int
 */
void MachineSystem::SetMachineFrame(int frame)
{
    if(frame < mFrame)
    {
        mFrame = 0;
        mMachine->Reset();
    }

    for(; mFrame < frame; mFrame++)
    {
        mMachine->Update(1.0 / mFrameRate);
    }

    mFrame = frame;
}

/**
 * Get Machine Number
 * @return int
 */
int MachineSystem::GetMachineNumber()
{
    return mMachine->GetMachineNumber();
}

/**
 * Given Machine Number, Instance Machine
 * @param number Machine Number
 */
void MachineSystem::SetMachineNumber(int number)
{
    if(number == 1)
    {
        MachineCFactory factory(mResourcesDir);
        mMachine = factory.Create();
    }
    else if(number == 2)
    {
        Machine1Factory factory(mResourcesDir);
        mMachine = factory.Create();
    }

    mMachine->Reset();
    mMachine->SetMachineNumber(number);
}

/**
 * Set Current Frame rate
 * @param rate double
 */
void MachineSystem::SetFrameRate(double rate)
{
    mFrameRate = rate;
}

/**
 * Calculate Current Machine Time
 * @return Machine Time
 */
double MachineSystem::GetMachineTime()
{
    return mFrame / mFrameRate;
}

/**
 * Sets Flag For Debugging
 * @param flag Flag Number
 */
void MachineSystem::SetFlag(int flag)
{
}



