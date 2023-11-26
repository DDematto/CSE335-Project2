/**
 * @file MachineActual.h
 * @author Devin DeMatto
 */

#ifndef CANADIANEXPERIENCE_MACHINELIB_MACHINEACTUAL_H
#define CANADIANEXPERIENCE_MACHINELIB_MACHINEACTUAL_H

#include <b2_world.h>

// Forward Declaration
class Component;
class MachineSystem;
class ContactListener;

/**
 * Class Describing the Machine and Handles World Logic
 */
class MachineActual
{
private:
    /// Number Associated with Machine
    int mMachineNumber = 0;

    /// Position of Machine
    wxPoint mPosition = wxPoint(500, 500);

    /// Components Associated with Machine
    std::vector<std::shared_ptr<Component>> mComponents;

    /// The box2d world
    std::shared_ptr<b2World> mWorld;

    /// The installed contact filter
    std::shared_ptr<ContactListener> mContactListener;

    /// Gravity in meters per second per second
    const float Gravity = -9.8f;

    /// Number of velocity update iterations per step
    const int VelocityIterations = 6;

    /// Number of position update iterations per step
    const int PositionIterations = 2;

public:
    MachineActual();

    void Draw(std::shared_ptr<wxGraphicsContext> graphics);

    wxPoint GetLocation() const;

    void SetLocation(wxPoint position);

    void Update(double elapsed);

    /**
     * Gets Current Machine Number
     * @return int
     */
    int GetMachineNumber() const { return mMachineNumber; }

    /**
     * Sets Current Machine number
     * @param number int
     */
    void SetMachineNumber(int number) { mMachineNumber = number; }

    void AddComponent(const std::shared_ptr<Component> &component);

    /**
     * Returns all Components
     * @return Components
     */
    std::vector<std::shared_ptr<Component>> GetComponents() { return mComponents; }

    void Reset();
};

#endif //CANADIANEXPERIENCE_MACHINELIB_MACHINEACTUAL_H
