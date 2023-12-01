/**
 * @file Pulley.h
 * @author Devin DeMatto
 */

#ifndef CANADIANEXPERIENCE_MACHINELIB_PULLEY_H
#define CANADIANEXPERIENCE_MACHINELIB_PULLEY_H

#include "Component.h"
#include "RotationSink.h"
#include "RotationSource.h"
#include "Polygon.h"

/**
 * Base Class for Pulley
 */
class Pulley : public RotationSink, public Component
{
private:
    /// Connected Pulley
    std::shared_ptr<Pulley> mConnected;

    /// Rotation source for this component
    RotationSource mSource;

    /// Pulley
    cse335::Polygon mPulley;

    /// Pulley Belt
    cse335::Polygon mBelt;

    /// Radius of Pulley
    double mRadius;

    /// Position of Pulley
    wxPoint2DDouble mPosition;

    /// Rotation of Pulley
    double mRotation;

    /// Total Time
    double mTime = 0;

    /// Calculate the rocking effect
    double mRock = 0;

public:
    Pulley(double radius);

    void Drive(std::shared_ptr<Pulley> connectedPulley);

    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;

    void Update(double elapsed) override;

    void SetRotation(double rotation, double speed) override;

    void SetImage(std::wstring filePath);

    void SetPosition(wxPoint2DDouble position);

    /**
     * Returns Source Object
     * @return Source
     */
    RotationSource *GetSource() { return &mSource; }

    /**
     * Returns the Position of the Pulley
     * @return
     */
    wxPoint2DDouble GetPosition() { return mPosition; }

    /**
     * Returns the Radius of the Pulley
     * @return
     */
    double GetRadius() { return mRadius; }

    wxPoint2DDouble CalculateTangentPoint(wxPoint2DDouble position, double rotation, double beta);
    void AdjustAndDrawBelt(std::shared_ptr<wxGraphicsContext> graphics,
                           wxPoint2DDouble point1,
                           wxPoint2DDouble point2,
                           double offsetX,
                           double offsetY);
};

#endif //CANADIANEXPERIENCE_MACHINELIB_PULLEY_H
