/**
 * @file Conveyor.h
 * @author Devin DeMatto
 */

#ifndef CANADIANEXPERIENCE_MACHINELIB_CONVEYOR_H
#define CANADIANEXPERIENCE_MACHINELIB_CONVEYOR_H

#include "PhysicsPolygon.h"
#include "Component.h"
#include "RotationSink.h"
#include <b2_world_callbacks.h>
#include "b2_contact.h"

/**
 * Base Class for Conveyor
 */
class Conveyor : public RotationSink, public Component, public b2ContactListener
{
private:
    /// Speed of the Conveyor
    double mSpeed = 0;

    /// Polygon of Conveyor
    cse335::PhysicsPolygon mConveyorMech;

public:
    /// Constructor
    Conveyor(const std::wstring &resourceDir);

    /// Default constructor (disabled)
    Conveyor() = delete;

    /// Copy constructor (disabled)
    Conveyor(const Conveyor &) = delete;

    /// Assignment operator
    void operator=(const Conveyor &) = delete;

    void PreSolve(b2Contact *contact, const b2Manifold *manifold);

    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;

    void Update(double elapsed) override;

    void SetRotation(double rotation, double speed) override;

    /**
     * Visitor Function
     * @param visitor Visitor Object
     */
    void Accept(ComponentVisitor &visitor) override
    {
        visitor.VisitConveyor(this);
    }

    /**
     * Returns the Conveyor Polygon
     * @return PhysicsPolygon
     */
    cse335::PhysicsPolygon *GetConveyor() { return &mConveyorMech; };

    wxPoint2DDouble GetShaftPosition();

    /**
     * Returns Position of Conveyor
     * @return wxPoint2Double
     */
    wxPoint2DDouble GetPosition() { return mConveyorMech.GetPosition(); }

    void SetPosition(wxPoint2DDouble position);

};

#endif //CANADIANEXPERIENCE_MACHINELIB_CONVEYOR_H
