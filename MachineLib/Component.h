/**
 * @file Component.h
 * @author Devin DeMatto
 */

#ifndef CANADIANEXPERIENCE_MACHINELIB_COMPONENT_H
#define CANADIANEXPERIENCE_MACHINELIB_COMPONENT_H

#include "ComponentVisitor.h"

/**
 * The base class for components of a machine.
 */
class Component
{
private:

public:
    Component();

    /// Copy constructor (disabled)
    Component(const Component &) = delete;

    /// Assignment operator (disabled)
    void operator=(const Component &) = delete;

    virtual void Draw(std::shared_ptr<wxGraphicsContext> graphics);
    virtual void Update(double elapsed);

    /**
     * Visitor Function
     * @param visitor Visitor Object
     */
    virtual void Accept(ComponentVisitor &visitor) {};
};

#endif //CANADIANEXPERIENCE_MACHINELIB_COMPONENT_H
