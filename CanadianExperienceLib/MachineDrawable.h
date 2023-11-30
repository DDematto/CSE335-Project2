/**
 * @file MachineDrawable.h
 * @author Devin DeMatto
 */

#ifndef CANADIANEXPERIENCE_CANADIANEXPERIENCELIB_MACHINEDRAWABLE_H
#define CANADIANEXPERIENCE_CANADIANEXPERIENCELIB_MACHINEDRAWABLE_H

#include "../MachineLib/IMachineSystem.h"
#include "../MachineLib/MachineSystemFactory.h"
#include "Drawable.h"

/**
 * Adapter Class for Loading Machine into Canadian Experience
 */
class MachineDrawable : public Drawable
{
private:
    /// Machine Instance
    std::shared_ptr<IMachineSystem> mMachine;

    /// Machine Start Time
    double mStartTime = 0.0;

public:
    MachineDrawable(const std::wstring &name) : Drawable(name)
    {
//        mMachine = MachineSystemFactory(L"./resources").CreateMachineSystem();
    }

    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;

    bool HitTest(wxPoint point) override;
};

#endif //CANADIANEXPERIENCE_CANADIANEXPERIENCELIB_MACHINEDRAWABLE_H
