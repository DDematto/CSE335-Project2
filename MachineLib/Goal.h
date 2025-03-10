/**
 * @file Goal.h
 * @author Devin DeMatto
 */

#ifndef CANADIANEXPERIENCE_MACHINELIB_GOAL_H
#define CANADIANEXPERIENCE_MACHINELIB_GOAL_H

#include "Component.h"
#include "PhysicsPolygon.h"
#include <b2_world_callbacks.h>
#include "b2_contact.h"

/**
 * Basketball Goal.
 */
class Goal : public Component, public b2ContactListener
{
private:
    /// Score of the Goal
    int mScore = 0;

    /// The polygon object for the goal image
    cse335::Polygon mHoop;

    /// Physics polygon for the backboard/post
    cse335::PhysicsPolygon mPost;

    /// Polygon that we are going to hit to
    /// determine the basket has been scored
    cse335::PhysicsPolygon mTarget;

    /// Position of Goal
    wxPoint mPosition;

public:
    /// Constructor
    Goal(std::wstring path);

    /// Copy constructor (disabled)
    Goal(const Goal &) = delete;

    /// Assignment operator (disabled)
    void operator=(const Goal &) = delete;

    void BeginContact(b2Contact *contact) override;

    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;

    void PreSolve(b2Contact *contact, const b2Manifold *manifold) override;

    /**
     * Visitor Function
     * @param visitor Visitor Object
     */
    void Accept(ComponentVisitor &visitor) override
    {
        visitor.VisitGoal(this);
    }

    void SetPosition(int x, int y);

    /**
     * Returns the Target Polygon
     * @return PhysicsPolygon
     */
    cse335::PhysicsPolygon *GetTarget() { return &mTarget; };

    /**
     * Returns the Post Polygon
     * @return PhysicsPolygon
     */
    cse335::PhysicsPolygon *GetPost() { return &mPost; };

    /**
     * Reset Goal Score when Going Back in Frames
     */
    void ResetScore() { mScore = 0; }
};

#endif //CANADIANEXPERIENCE_MACHINELIB_GOAL_H
