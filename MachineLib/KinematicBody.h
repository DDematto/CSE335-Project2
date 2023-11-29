/**
 * @file KinematicBody.h
 * @author Devin DeMatto
 */

#ifndef CANADIANEXPERIENCE_MACHINELIB_KINEMATICBODY_H
#define CANADIANEXPERIENCE_MACHINELIB_KINEMATICBODY_H

#include "Body.h"
#include "RotationSink.h"

/**
 * Created Bodies That are Kinematic in World
 */
class KinematicBody : public Body, public RotationSink
{
public:
    KinematicBody() {};

    /**
     * Sets Body to Be Kinematic
     */
    void SetKinematic()
    {
        GetPolygon()->SetKinematic();
    }

    /**
     * Sets Rotation of the Kinematic Polygon
     * @param rotation Rotation of Pulley
     * @param speed Speed of Pulley
     */
    void SetRotation(double rotation, double speed) override
    {
        GetPolygon()->SetAngularVelocity(speed);
    };

};

#endif //CANADIANEXPERIENCE_MACHINELIB_KINEMATICBODY_H
