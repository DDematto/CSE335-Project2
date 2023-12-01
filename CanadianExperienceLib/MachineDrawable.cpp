/**
 * @file MachineDrawable.cpp
 * @author Devin DeMatto
 */

#include "pch.h"
#include <wx/xrc/xmlres.h>
#include "MachineDrawable.h"
#include "Actor.h"
#include "Picture.h"

MachineDrawable::MachineDrawable(const std::wstring &name, const std::wstring &resourcesDir, wxFrame *parent)
    : Drawable(name), mParent(parent)
{
    MachineSystemFactory factory(resourcesDir);
    mMachine = factory.CreateMachineSystem();
    mParent->Bind(wxEVT_COMMAND_MENU_SELECTED, &MachineDrawable::ShowDialog, this, XRCID("MachineInfo"));
}

/**
* Draw the machine at the currently specified location
* @param graphics Graphics object to render to
*/
void MachineDrawable::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    double scale = 0.50f;

    graphics->PushState();
    graphics->Scale(scale, scale);
    mMachine->DrawMachine(graphics);
    mMachine->SetMachineFrame(mActor->GetPicture()->GetTimeline()->GetCurrentFrame());
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
 * Show Dialog Box When Clicking on Menu Item
 * @param event Command Event from WxWidgets
 */
void MachineDrawable::ShowDialog(wxCommandEvent &event)
{
    MachineDialog dlg(mParent, mMachine);
    if(dlg.ShowModal() == wxID_OK)
    {
        mActor->GetPicture()->SetAnimationTime(0);
        mMachine->SetMachineFrame(0);
    }
}

void MachineDrawable::SetPosition(wxPoint position)
{
    mMachine->SetLocation(position);
}

void MachineDrawable::SetActor(std::shared_ptr<Actor> actor)
{
    mActor = actor;
}
