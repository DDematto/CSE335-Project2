/**
 * @file MachineDrawable.cpp
 * @author Devin DeMatto
 */

#include "pch.h"
#include <wx/xrc/xmlres.h>
#include "MachineDrawable.h"
#include "Actor.h"
#include "Picture.h"
#include "MachineDataDlg.h"

/**
 * Constructor
 * @param name Name of Drawable
 * @param resourcesDir Resource Directory
 * @param parent Parent Frame
 */
MachineDrawable::MachineDrawable(const std::wstring &name, const std::wstring &resourcesDir, wxFrame *parent)
    : Drawable(name), mParent(parent)
{
    MachineSystemFactory factory(resourcesDir);
    mMachine = factory.CreateMachineSystem();

    /// Bind the Given Dialog Box for Machine Switching
    mParent->Bind(wxEVT_COMMAND_MENU_SELECTED, &MachineDrawable::ShowSwitchDialog, this, XRCID("MachineInfo" + name));

    /// Bind the Machine Start Time Dialog Box
    mParent->Bind(wxEVT_COMMAND_MENU_SELECTED, &MachineDrawable::ShowStartDialog, this, XRCID("MachineStart" + name));
}

/**
* Draw the machine at the currently specified location
* @param graphics Graphics object to render to
*/
void MachineDrawable::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    double scale = 0.50f;

    auto picture = mActor->GetPicture();
    auto timeline = picture->GetTimeline();

    graphics->PushState();
    graphics->Scale(scale, scale);
    mMachine->DrawMachine(graphics);

    if(timeline->GetCurrentFrame() >= mStartFrame)
    {
        mMachine->SetMachineFrame(timeline->GetCurrentFrame() - mStartFrame);
    }

    graphics->PopState();
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

/**
 * Show Machine System Switch Dialog
 * @param event Command Event from WxWidgets
 */
void MachineDrawable::ShowSwitchDialog(wxCommandEvent &event)
{
    MachineDialog dlg(mParent, mMachine);
    if(dlg.ShowModal() == wxID_OK)
    {
        mActor->GetPicture()->SetAnimationTime(0);
        mMachine->SetMachineFrame(0);
    }
}

/**
 * Show Machine Start Time Dialog
 * @param event Command Event from WxWidgets
 */
void MachineDrawable::ShowStartDialog(wxCommandEvent &event)
{
    MachineDataDlg dlg(mParent, this, mActor->GetPicture()->GetTimeline()->GetNumFrames());
    if(dlg.ShowModal() == wxID_OK)
    {
    }
}

/**
 * Sets Position in Machine System
 * @param position wxPoint
 */
void MachineDrawable::SetPosition(wxPoint position)
{
    mMachine->SetLocation(position);
}

/**
 * Sets Actor Associated with MachineDrawable
 * @param actor Actor Object
 */
void MachineDrawable::SetActor(std::shared_ptr<Actor> actor)
{
    mActor = actor;
}
