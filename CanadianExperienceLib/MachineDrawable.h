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

    /// Actor Component
    std::shared_ptr<Actor> mActor;

    /// Parent Frame
    wxFrame *mParent;

public:
    /**
     * Constructor
     * @param name Name of Drawable
     * @param resourcesDir Resource Directory
     * @param parent Parent Frame
     */
    MachineDrawable(const std::wstring &name, const std::wstring &resourcesDir, wxFrame *parent);

    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;

    bool HitTest(wxPoint point) override;

    void ShowDialog(wxCommandEvent &event);

    /**
     * Sets Position in Machine System
     * @param position wxPoint
     */
    void SetPosition(wxPoint position);

    /**
     * Sets Actor Associated with MachineDrawable
     * @param actor Actor Object
     */
    void SetActor(std::shared_ptr<Actor> actor);
};

#endif //CANADIANEXPERIENCE_CANADIANEXPERIENCELIB_MACHINEDRAWABLE_H
