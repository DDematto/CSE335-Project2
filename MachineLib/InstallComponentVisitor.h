/**
 * @file InstallComponentVisitor.h
 * @author Devin DeMatto
 */

#ifndef CANADIANEXPERIENCE_MACHINELIB_INSTALLCOMPONENTVISITOR_H
#define CANADIANEXPERIENCE_MACHINELIB_INSTALLCOMPONENTVISITOR_H

#include <memory>
#include "b2_world.h"
#include "ContactListener.h"
#include "ComponentVisitor.h"
#include "Body.h"
#include "Goal.h"

/**
 * Class that installs physics to all components
 */
class InstallComponentVisitor : public ComponentVisitor
{
private:
    /// World Instance
    std::shared_ptr<b2World> mWorld;

    /// Contact Listener Instance
    std::shared_ptr<ContactListener> mContactListener;

public:
    /**
     * Constructor
     * @param world World Object
     * @param contactListener Contact Listener
     */
    InstallComponentVisitor(std::shared_ptr<b2World> world, std::shared_ptr<ContactListener> contactListener) : mWorld(
        world), mContactListener(contactListener) {}

    /**
     * Ran on all Body Components
     * @param body Body Object
     */
    void VisitBody(Body *body) override
    {
        body->GetPolygon()->InstallPhysics(mWorld);
    }

    /**
     * Ran on all Goal Components
     * @param goal Goal Object
     */
    void VisitGoal(Goal *goal) override
    {
        goal->GetTarget()->InstallPhysics(mWorld);
        goal->GetPost()->InstallPhysics(mWorld);
        mContactListener->Add(goal->GetTarget()->GetBody(), goal);
    }

    /**
     * Ran on all Conveyor Components
     * @param conveyor Conveyor Object
     */
    void VisitConveyor(Conveyor *conveyor) override
    {
    }

    /**
     * Ran on all Hamster Components
     * @param hamster Hamster Object
     */
    void VisitHamster(Hamster *hamster) override
    {
    }
};

#endif //CANADIANEXPERIENCE_MACHINELIB_INSTALLCOMPONENTVISITOR_H
