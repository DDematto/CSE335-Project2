/**
 * @file GeneralMachineFactory.h
 * @author Devin DeMatto
 */

#ifndef CANADIANEXPERIENCE_MACHINELIB_GENERALMACHINEFACTORY_H
#define CANADIANEXPERIENCE_MACHINELIB_GENERALMACHINEFACTORY_H

#include <memory>
#include <string>

class MachineActual;
class Body;
class Conveyor;

/**
 * General Machine Factory Class for Using Methods in Multiple Machine Factories
 */
class GeneralMachineFactory
{
private:
    /// Path to the resources directory
    std::wstring mResourcesDir;

    /// Path to the images directory
    std::wstring mImagesDir;

    /// The possible domino colors
    enum class DominoColor { Black, Red, Green, Blue };

    /// Height of a Domino
    const double DominoHeight = 25;

    /// Width of a Domino
    const double DominoWidth = 5;

public:
    /// Constructor
    GeneralMachineFactory(std::wstring resourcesDir);

    /// Default constructor (disabled)
    GeneralMachineFactory() = delete;

    /// Copy constructor (disabled)
    GeneralMachineFactory(const GeneralMachineFactory &) = delete;

    /// Assignment operator
    void operator=(const GeneralMachineFactory &) = delete;

    /**
     * Create Machine Function
     * @return Machine
     */
    virtual std::shared_ptr<MachineActual> Create() = 0;

    /**
     * Returns Image Directory
     * @return wstring
     */
    std::wstring GetImageDir() { return mImagesDir; }

    // Helpers for Other Machine Factories
    void TopBeamAndRamp(std::shared_ptr<MachineActual> machine);
    void BeamAndSpinningArm(std::shared_ptr<MachineActual> machine);
    void DominoStack(std::shared_ptr<MachineActual> machine, wxPoint2DDouble position);
    void BasketballGoal(std::shared_ptr<MachineActual> machine);
    void DominoesOnBeam(std::shared_ptr<MachineActual> machine, wxPoint2DDouble position);

    std::shared_ptr<Body> Domino(std::shared_ptr<MachineActual> machine,
                                 wxPoint2DDouble position,
                                 double rotation,
                                 DominoColor color);

};

#endif //CANADIANEXPERIENCE_MACHINELIB_GENERALMACHINEFACTORY_H
