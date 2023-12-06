/**
 * @file MachineDataDlg.cpp
 * @author Devin
 */

#include "pch.h"
#include <wx/xrc/xmlres.h>
#include <wx/valnum.h>
#include "MachineDataDlg.h"
#include "MachineDrawable.h"

/**
 * Constructor
 * @param parent The parent window we will center in
 * @param machine Pointer to the machine we are editing
 * @param maxFrames Maximum amount of Frames in Timeline
 */
MachineDataDlg::MachineDataDlg(wxWindow *parent, MachineDrawable *machine, int maxFrames) : mMachine(machine)
{
    wxXmlResource::Get()->LoadDialog(this, parent, L"MachineDataDlg");

    mStartFrame = mMachine->GetStartFrame();

    Bind(wxEVT_BUTTON, &MachineDataDlg::OnOK, this, wxID_OK);

    auto startTimeCtrl = XRCCTRL(*this, "MachineDataDlgStartFrame", wxTextCtrl);
    wxIntegerValidator<int> startTimeValidator(&mStartFrame);
    startTimeValidator.SetRange(0, maxFrames);
    startTimeCtrl->SetValidator(startTimeValidator);
}

/**
 * Handle an OK button press
 * @param event Button event
 */
void MachineDataDlg::OnOK(wxCommandEvent &event)
{
    if(Validate() && TransferDataFromWindow())
    {
        mMachine->SetStartFrame(mStartFrame);
        EndModal(wxID_OK);
    }
}
