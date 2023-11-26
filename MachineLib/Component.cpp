/**
 * @file Component.cpp
 * @author Devin DeMatto
 */

#include "pch.h"
#include "Component.h"

Component::Component()
{

}

/**
 * Draw the component
 * @param graphics The graphics context to draw on
 */
void Component::Draw(std::shared_ptr<wxGraphicsContext> graphics) {}

/**
 * Update the component based on elapsed time
 * @param elapsed The time elapsed since the last update
 */
void Component::Update(double elapsed)
{
    // Implement update code here
}

/**
 * Connect this component to another component
 * @param component The component to connect to
 */
void Component::Connect(std::shared_ptr<Component> component)
{
    // Implement connection code here
}

/**
 * Set the rotation of this component
 * @param rotation The rotation in degrees
 */
void Component::SetRotation(double rotation)
{
    // Implement rotation setting code here
}


