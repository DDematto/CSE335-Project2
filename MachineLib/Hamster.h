/**
 * @file Hamster.h
 * @author Devin DeMatto
 */

#ifndef CANADIANEXPERIENCE_MACHINELIB_HAMSTER_H
#define CANADIANEXPERIENCE_MACHINELIB_HAMSTER_H

#include "Component.h"
#include <b2_world_callbacks.h>
#include "PhysicsPolygon.h"
#include "RotationSource.h"

/**
 * Hamster Class.
 */
class Hamster : public Component, public b2ContactListener
{
private:
    /// Speed of Hamster
    double mSpeed = 1;

    /// The Physics polygon object for the hamster cage
    cse335::PhysicsPolygon mHamsterCage;

    /// The Polygon object for the wheel in the cage
    cse335::Polygon mHamsterWheel;

    /// Current Hamster State
    int mHamsterIndex = 0;

    /// States of Hamster as Polygons
    std::vector<std::unique_ptr<cse335::Polygon>> mHamsters;

    /// Set If the Hamster is Currently Running
    bool mIsRunning = false;

    /// Rotation of Hamster
    double mRotation = 0;

    /// Rotation source for this component
    RotationSource mSource;

public:
    Hamster(std::wstring imagedir);

    /// Copy constructor (disabled)
    Hamster(const Hamster &) = delete;

    /// Assignment operator (disabled)
    void operator=(const Hamster &) = delete;

    void BeginContact(b2Contact *contact) override;

    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;

    void Update(double elapsed) override;

    void SetPosition(double x, double y);

    void SetInitiallyRunning(bool isRunning);

    void SetSpeed(double speed);

    wxPoint2DDouble GetShaftPosition();

    /**
     * Visitor Function
     * @param visitor Visitor Object
     */
    void Accept(ComponentVisitor &visitor) override
    {
        visitor.VisitHamster(this);
    }

    /**
     * Gets Cage Object
     * @return PhysicsPolygon
     */
    cse335::PhysicsPolygon *GetCage() { return &mHamsterCage; }

    /**
     * Returns Source Object for Hamster
     * @return
     */
    RotationSource *GetSource() { return &mSource; }
};

#endif //CANADIANEXPERIENCE_MACHINELIB_HAMSTER_H
