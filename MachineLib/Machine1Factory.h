/**
 * @file Machine1Factory.h
 * @author Charles Owen
 *
 * Factory for creating Machine #1
 */

#ifndef CANADIANEXPERIENCE_MACHINE1FACTORY_H
#define CANADIANEXPERIENCE_MACHINE1FACTORY_H

#include <memory>
#include <string>
#include "GeneralMachineFactory.h"

/**
 * Factory for creating Machine #1
 */
class Machine1Factory : public GeneralMachineFactory
{
private:

public:
    /**
     * Constructor
     * @param resourcesDir Resources Directory
     */
    Machine1Factory(std::wstring resourcesDir) : GeneralMachineFactory(resourcesDir) {};

    std::shared_ptr<MachineActual> Create();
};

#endif //CANADIANEXPERIENCE_MACHINE1FACTORY_H
