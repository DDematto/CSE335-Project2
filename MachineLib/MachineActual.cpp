/**
 * @author Devin DeMatto
 * @file MachineActual.cpp
 */

#include "pch.h"
#include "MachineActual.h"
#include "Component.h"
#include "MachineSystem.h"
#include "ContactListener.h"
#include "InstallComponentVisitor.h"

/**
 * Constructor
 */
MachineActual::MachineActual()
{
    mWorld = std::make_shared<b2World>(b2Vec2(0.0f, Gravity));
}

/**
 * Draws the Machine
 * @param graphics Graphics Context
 */
void MachineActual::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    for(auto &component : mComponents)
    {
        component->Draw(graphics);
    }
}

/**
 * Updates Machine Based on elapsed time
 * @param elapsed the time since last call to this function
 */
void MachineActual::Update(double elapsed)
{
    for(auto &component : mComponents)
    {
        component->Update(elapsed);
    }

    // Advance the physics system one frame in time
    mWorld->Step(elapsed, VelocityIterations, PositionIterations);
}

/**
 * Get Location of Machine
 * @return wxPoint
 */
wxPoint MachineActual::GetLocation() const
{
    return mPosition;
}

/**
 * Set Location of Machine
 * @param position wxPoint
 */
void MachineActual::SetLocation(wxPoint position)
{
    this->mPosition = position;
}

/**
 * Adds Component to MachineActualTest
 * @param component Component
 */
void MachineActual::AddComponent(const std::shared_ptr<Component> &component)
{
    mComponents.push_back(component);
}

/**
 * Reset the World and Generate a new one
 */
void MachineActual::Reset()
{
    // Resetting b2World as new instance
    mWorld = std::make_shared<b2World>(b2Vec2(0.0f, Gravity));

    // Create and install the contact filter
    mContactListener = std::make_shared<ContactListener>();
    mWorld->SetContactListener(mContactListener.get());

    // Instantiate the InstallComponentVisitor
    InstallComponentVisitor installer(mWorld, mContactListener);

    for(auto &component : mComponents)
    {
        component->Accept(installer);
    }
}

