/**
 * @file MachineSystem.h
 * @author Devin DeMato
 */

#ifndef CANADIANEXPERIENCE_MACHINELIB_MACHINESYSTEM_H
#define CANADIANEXPERIENCE_MACHINELIB_MACHINESYSTEM_H

#include "IMachineSystem.h"

// Forward Declarations
class MachineActual;

/**
 * Class that Handles the Machine and Logic with Other Libraries
 */
class MachineSystem : public IMachineSystem
{
private:
    /// Location of Machine System
    wxPoint mLocation = wxPoint(0, 0);

    /// Machine System Frame Rate
    double mFrameRate = 30;

    /// Current Frame
    int mFrame = 0;

    /// The Machine
    std::shared_ptr<MachineActual> mMachine;

    /// The resources directory
    std::wstring mResourcesDir;

    /// How many pixels there are for each CM
    double mPixelsPerCentimeter = 1.5;

public:
    /// Default constructor
    MachineSystem(std::wstring resourcesDir);

    /// Copy constructor (disabled)
    MachineSystem(const MachineSystem &) = delete;

    /// Assignment operator
    void operator=(const MachineSystem &) = delete;

    void SetLocation(wxPoint location) override;
    wxPoint GetLocation() override;
    void DrawMachine(std::shared_ptr<wxGraphicsContext> graphics) override;
    void SetMachineFrame(int frame) override;
    int GetMachineNumber() override;
    void SetMachineNumber(int machine) override;
    void SetFrameRate(double rate) override;
    double GetMachineTime() override;
    void SetFlag(int flag) override;
};

#endif //CANADIANEXPERIENCE_MACHINELIB_MACHINESYSTEM_H
