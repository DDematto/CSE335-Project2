/**
 * @file ComponentVisitor.h
 * @author Devin DeMatto
 */

#ifndef CANADIANEXPERIENCE_MACHINELIB_COMPONENTVISITOR_H
#define CANADIANEXPERIENCE_MACHINELIB_COMPONENTVISITOR_H

class Body;
class Goal;
class Conveyor;
class Hamster;

/**
 * Base Visitor class for components
 */
class ComponentVisitor {
protected:
    ComponentVisitor() {}

public:
    virtual ~ComponentVisitor() {};

    /**
     * Visit a Body component
     * @param body object we are visiting
     */
    virtual void VisitBody(Body *body) {}

    /**
     * Visit a Goal component
     * @param goal object we are visiting
     */
    virtual void VisitGoal(Goal *goal) {}

    /**
     * Visit a Conveyor component
     * @param conveyor object we are visiting
     */
    virtual void VisitConveyor(Conveyor *conveyor) {}

    /**
     * Visit a Hamster component
     * @param hamster object we are visiting
     */
    virtual void VisitHamster(Hamster *hamster) {}
};



#endif //CANADIANEXPERIENCE_MACHINELIB_COMPONENTVISITOR_H
