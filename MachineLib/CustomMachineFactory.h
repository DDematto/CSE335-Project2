/**
 * @file CustomMachineFactory.h
 * @author Devin
 *
 *
 */

#ifndef CANADIANEXPERIENCE_MACHINELIB_CUSTOMMACHINEFACTORY_H
#define CANADIANEXPERIENCE_MACHINELIB_CUSTOMMACHINEFACTORY_H

#include <memory>
#include <string>
#include "GeneralMachineFactory.h"

class MachineActual;
class Body;
class Conveyor;

/**
 * Factory for creating My Machine Machine #2
 */
class CustomMachineFactory : public GeneralMachineFactory
{
private:

public:
    /**
     * Constructor
     * @param resourcesDir Resources Directory
     */
    CustomMachineFactory(std::wstring resourcesDir) : GeneralMachineFactory(resourcesDir) {};

    std::shared_ptr<MachineActual> Create();
    void PulleyChain(std::shared_ptr<MachineActual> machine);
    void LeftRamp(std::shared_ptr<MachineActual> machine, wxPoint2DDouble &position);
    void RightRamp(std::shared_ptr<MachineActual> machine, wxPoint2DDouble &position);
    void Ball(std::shared_ptr<MachineActual> machine, wxPoint2DDouble position);
};

#endif //CANADIANEXPERIENCE_MACHINELIB_CUSTOMMACHINEFACTORY_H
