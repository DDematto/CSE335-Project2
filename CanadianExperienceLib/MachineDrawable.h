/**
 * @file MachineDrawable.h
 * @author Devin DeMatto
 */

#ifndef CANADIANEXPERIENCE_CANADIANEXPERIENCELIB_MACHINEDRAWABLE_H
#define CANADIANEXPERIENCE_CANADIANEXPERIENCELIB_MACHINEDRAWABLE_H

#include <machine-api.h>
#include "Drawable.h"
#include "Actor.h"

/**
 * Adapter Class for Machine Into Canadian Experience
 */
class MachineDrawable : public Drawable
{
private:
    /// Machine System
    std::shared_ptr<IMachineSystem> mMachine;

    /// Start Frame
    int mStartFrame = 0;

    /// Actor Component
    std::shared_ptr<Actor> mActor;

    /// Parent Frame
    wxFrame *mParent;

public:
    MachineDrawable(const std::wstring &name, const std::wstring &resourcesDir, wxFrame *parent);

    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;

    bool HitTest(wxPoint point) override;

    void ShowSwitchDialog(wxCommandEvent &event);

    void ShowStartDialog(wxCommandEvent &event);

    void SetPosition(wxPoint position);

    void SetActor(std::shared_ptr<Actor> actor);

    /**
     * Gets Start Frame for Machine
     * @return Int
     */
    int GetStartFrame() const { return mStartFrame; }

    /**
     * Sets Start Frame for Machine
     * @param frame Int
     */
    void SetStartFrame(int frame) { mStartFrame = frame; }

    /**
     * Get Machine Type for System
     * @return int
     */
    int GetMachineType() const { return mMachine->GetMachineNumber(); }

    /**
     * Set Machine Running in System
     * @param machineType int
     */
    void SetMachineType(int machineType) { mMachine->SetMachineNumber(machineType); }
};

#endif //CANADIANEXPERIENCE_CANADIANEXPERIENCELIB_MACHINEDRAWABLE_H
