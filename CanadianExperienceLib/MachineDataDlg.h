/**
 * @file MachineDataDlg.h
 * @author Devin DeMatto
 */

#ifndef CANADIANEXPERIENCE_CANADIANEXPERIENCELIB_MACHINEDATADLG_H
#define CANADIANEXPERIENCE_CANADIANEXPERIENCELIB_MACHINEDATADLG_H

class MachineDrawable;

/**
 * Timeline dialog box
 */
class MachineDataDlg final : public wxDialog
{
private:
    void OnOK(wxCommandEvent &event);

    /// The pointer to the Machine System
    MachineDrawable *mMachine;

    /// Start Frame for The Machine
    int mStartFrame;

public:
    MachineDataDlg(wxWindow *parent, MachineDrawable *machine, int maxFrames);
};

#endif //CANADIANEXPERIENCE_CANADIANEXPERIENCELIB_MACHINEDATADLG_H
