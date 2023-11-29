/**
 * @file RotationSource.cpp
 * @author Devin DeMatto
 */

#include "pch.h"
#include "RotationSource.h"
#include "RotationSink.h"
#include "Conveyor.h"

RotationSource::RotationSource()
{

}

/**
 * Sets Rotation of Component that Inherits Rotation Sink
 * @param rotation Rotation
 * @param speed Speed
 */
void RotationSource::UpdateRotation(double rotation, double speed)
{
    mSink->SetRotation(rotation, speed);
}

/**
 * Connects Component that is a Sink to the source
 * @param sink The Component that inherits Rotation Sink
 */
void RotationSource::ConnectSink(std::shared_ptr<RotationSink> sink)
{

    mSink = sink;
}
