/**
 * @file RotationSource.h
 * @author Devin DeMatto
 */

#ifndef CANADIANEXPERIENCE_MACHINELIB_ROTATIONSOURCE_H
#define CANADIANEXPERIENCE_MACHINELIB_ROTATIONSOURCE_H

// Forward Declaration
class RotationSink;

/**
 * Class that Describes Rotation Sources
 */
class RotationSource
{
private:
    /// Connected Sink
    std::shared_ptr<RotationSink> mSink;

public:
    /// Default constructor
    RotationSource();

    /// Copy constructor (disabled)
    RotationSource(const RotationSource &) = delete;

    /// Assignment operator
    void operator=(const RotationSource &) = delete;

    void UpdateRotation(double rotation, double speed);

    void ConnectSink(std::shared_ptr<RotationSink> sink);
};

#endif //CANADIANEXPERIENCE_MACHINELIB_ROTATIONSOURCE_H
