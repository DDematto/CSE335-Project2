/**
 * @file ResetComponentsVisitor.h
 * @author Devin DeMatto
 */

#ifndef CANADIANEXPERIENCE_MACHINELIB_RESETCOMPONENTSVISITOR_H
#define CANADIANEXPERIENCE_MACHINELIB_RESETCOMPONENTSVISITOR_H

#include <memory>
#include "b2_world.h"
#include "ContactListener.h"
#include "ComponentVisitor.h"
#include "Body.h"
#include "Goal.h"
#include "Hamster.h"
#include "Conveyor.h"

/**
 * Class that resets components to initial state
 */
class ResetComponentVisitor : public ComponentVisitor
{
public:
    /**
     * Constructor
     * @param world World Object
     * @param contactListener Contact Listener
     */
    ResetComponentVisitor() {}

    /// Copy constructor (disabled)
    ResetComponentVisitor(const ResetComponentVisitor &) = delete;

    /// Assignment operator (disabled)
    void operator=(const ResetComponentVisitor &) = delete;

    /**
     * Ran on all Body Components
     * @param body Body Object
     */
    void VisitBody(Body *body) override
    {
    }

    /**
     * Ran on all Goal Components
     * @param goal Goal Object
     */
    void VisitGoal(Goal *goal) override
    {
        goal->ResetScore();
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

#endif //CANADIANEXPERIENCE_MACHINELIB_RESETCOMPONENTSVISITOR_H
