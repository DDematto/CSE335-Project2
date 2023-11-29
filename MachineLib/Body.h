/**
 * @file Body.h
 * @author Devin DeMatto
 */

#ifndef CANADIANEXPERIENCE_MACHINELIB_BODY_H
#define CANADIANEXPERIENCE_MACHINELIB_BODY_H

#include "Component.h"
#include "PhysicsPolygon.h"

/**
 * The Body class represents a physical body component of a machine.
 */
class Body : public Component
{
private:
    /// Polygon
    cse335::PhysicsPolygon mPolygon;

public:
    Body();

    /// Copy constructor (disabled)
    Body(const Body &) = delete;

    /// Assignment operator (disabled)
    void operator=(const Body &) = delete;

    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;

    /**
     * Get a pointer to the polygon this body uses
     * @return Pointer to the polygon object
     */
    cse335::PhysicsPolygon *GetPolygon() { return &mPolygon; }

    /**
     * Builds Rectangle
     * @param x x position
     * @param y y position
     * @param width width
     * @param height height
     */
    void Rectangle(double x, double y, double width, double height);

    /**
     * Sets Image on Polygon
     * @param image image path
     */
    void SetImage(std::wstring image);

    /**
     * Function for Visitor Pattern
     * @param visitor Visitor Object
     */
    void Accept(ComponentVisitor &visitor) override
    {
        visitor.VisitBody(this);
    }

    /**
     * Creates a Bottom Centered Rectangle
     * @param x X Position
     * @param y Y Position
     */
    void BottomCenteredRectangle(double x, double y);

    /**
     * Sets Initial Position
     * @param x X
     * @param y Y
     */
    void SetInitialPosition(double x, double y);

    /**
     * Adds a Point to Build a Polygon
     * @param x X
     * @param y Y
     */
    void AddPoint(double x, double y);

    /**
     * Creates a Circle Polygon
     * @param radius Radius
     */
    void Circle(double radius);

    /**
     * Sets up Physics for Polygon
     * @param density Density
     * @param friction Friction
     * @param restitution Restitution
     */
    void SetPhysics(double density, double friction, double restitution);

    /**
     * Set Initial Rotation
     * @param rotation rotation
     */
    void SetInitialRotation(double rotation);
};

#endif //CANADIANEXPERIENCE_MACHINELIB_BODY_H
