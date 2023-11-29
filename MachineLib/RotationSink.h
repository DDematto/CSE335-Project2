/**
 * @file RotationSink.h
 * @author Devin DeMatto
 */

#ifndef CANADIANEXPERIENCE_MACHINELIB_ROTATIONSINK_H
#define CANADIANEXPERIENCE_MACHINELIB_ROTATIONSINK_H

/**
 * Inheritance Class for Components to Implement Being a Sink
 */
class RotationSink
{
public:
    virtual ~RotationSink() = default;

    /**
     * Set the rotation of the sink.
     * @param rotation The rotation value to be set.
     * @param speed The Speed to be Set
     */
    virtual void SetRotation(double rotation, double speed) = 0;
};

#endif //CANADIANEXPERIENCE_MACHINELIB_ROTATIONSINK_H
