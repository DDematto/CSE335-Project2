/**
 * @file Pulley.cpp
 * @author Devin DeMatto
 */

#include "pch.h"
#include "Pulley.h"

/// Maximum amount to rock the belt
/// No, I'm not going to tell you what
/// the units are.
const double BeltRockAmount = 3.0;

/// How quickly to rock the belt in radians per second
/// This is divided by the length to get the actual rate
const double BeltRockBaseRate = M_PI * 1000;

#ifndef M_PI
/// Defines PI
#define M_PI 3.14159265358979323846
#endif

/**
 * Constructor for Pulley
 * @param radius Radius of Pully
 */
Pulley::Pulley(double radius)
{
    mRadius = radius;

    mPulley.CenteredSquare(mRadius * 2);
}

/**
 * Drawing the Pulley
 * @param graphics graphics Context
 */
void Pulley::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    graphics->PushState();

    if(mConnected != nullptr)
    {
        const auto connectedPos = mConnected->GetPosition();

        // Calculate Difference in Positions
        double dx = connectedPos.m_x - mPosition.m_x;
        double dy = connectedPos.m_y - mPosition.m_y;

        // Calculate Distance
        double distance = sqrt(dx * dx + dy * dy);

        // Calculate Theta
        double theta = atan2(dy, dx);

        // Calculate phi
        double phi = asin(abs(mConnected->GetRadius() - mRadius) / distance);

        double betaPositive, betaNegative;
        if(mRotation >= 0)
        {
            betaPositive = theta + phi - (M_PI / 2);
            betaNegative = theta - phi + (M_PI / 2);
        }
        else
        {
            betaPositive = theta - phi - (M_PI / 2);
            betaNegative = theta + phi + (M_PI / 2);
        }

        // Calculate for Positive Positive
        auto point1Positive = CalculateTangentPoint(mPosition, mRadius, betaPositive);
        auto point2Positive = CalculateTangentPoint(mConnected->GetPosition(), mConnected->GetRadius(), betaPositive);

        // Calculate for Negative Negative
        auto point1Negative = CalculateTangentPoint(mPosition, mRadius, betaNegative);
        auto point2Negative = CalculateTangentPoint(mConnected->GetPosition(), mConnected->GetRadius(), betaNegative);

        // Offset by Width of Belt
        double offsetMagnitude = 2;
        double perpendicularOffsetX = -dy / distance * offsetMagnitude;
        double perpendicularOffsetY = dx / distance * offsetMagnitude;

        // Adjust and draw the belts
        AdjustAndDrawBelt(graphics, point1Positive, point2Positive, perpendicularOffsetX, perpendicularOffsetY);
        AdjustAndDrawBelt(graphics, point1Negative, point2Negative, -perpendicularOffsetX, -perpendicularOffsetY);
    }

    // Draw Pulley
    graphics->Translate(mPosition.m_x, mPosition.m_y);
    mPulley.DrawPolygon(graphics, 0, 0, mRotation);

    graphics->PopState();
}

/**
 * Sets Rotation of the Two Pulleys
 * @param rotation Rotation of Pulley
 * @param speed Speed of Pulley
 */
void Pulley::SetRotation(double rotation, double speed)
{
    mRotation = rotation;

    // Setup Second Pulley Rotation
    if(mConnected != nullptr)
    {
        double gearRatio = mRadius / mConnected->mRadius;
        mConnected->SetRotation(rotation * gearRatio, speed * gearRatio);

        // Since the connected pulley is also a source, update its rotation to notify its sink
        mConnected->mSource.UpdateRotation(rotation * gearRatio, speed * gearRatio);
        mSource.UpdateRotation(rotation * gearRatio, -speed * gearRatio);
    }
}

/**
 * Sets Image for Pulley
 * @param filePath file path
 */
void Pulley::SetImage(std::wstring filePath)
{
    mPulley.SetImage(filePath);
}

/**
 * Sets Position for Pulley
 * @param position
 */
void Pulley::SetPosition(wxPoint2DDouble position)
{
    mPosition = position;
}

/**
 * Drives Rotation of another Pulley
 * @param connectedPulley Pulley
 */
void Pulley::Drive(std::shared_ptr<Pulley> connectedPulley)
{
    mConnected = connectedPulley;
    mSource.ConnectSink(connectedPulley);
}

/**
 * Calculates Tangent Point
 * @param position position
 * @param radius radius
 * @param beta beta value
 * @return tangent point
 */
wxPoint2DDouble Pulley::CalculateTangentPoint(wxPoint2DDouble position, double radius, double beta)
{
    return {position.m_x + radius * cos(beta), position.m_y + radius * sin(beta)};
}

/**
 * Adjust Belts and Draw them
 * @param graphics graphics
 * @param point1 start point
 * @param point2 end point
 * @param offsetX offset in x
 * @param offsetY offset in y
 */
void Pulley::AdjustAndDrawBelt(std::shared_ptr<wxGraphicsContext> graphics,
                               wxPoint2DDouble point1,
                               wxPoint2DDouble point2,
                               double offsetX,
                               double offsetY)
{
    // Calculate the mid-point for the Bézier curve
    double midX = (point1.m_x + point2.m_x) / 2.0;
    double midY = (point1.m_y + point2.m_y) / 2.0;

    // Calculate distance between pulleys
    double distance = sqrt(pow(point2.m_x - point1.m_x, 2) + pow(point2.m_y - point1.m_y, 2));

    // Adjust the rocking rate based on the length of the belt
    double rockingRate = BeltRockBaseRate / distance;

    // Calculate sway using the time-based rocking rate
    double swayX = BeltRockAmount * cos(mTime * rockingRate);
    double swayY = BeltRockAmount * sin(mTime * rockingRate);

    // Determine the control point for the Bézier curve with dynamic sway
    wxPoint2DDouble controlPoint(midX + swayX, midY + swayY);

    // Create a path for the belt
    wxGraphicsPath beltPath = graphics->CreatePath();
    beltPath.MoveToPoint(point1.m_x + offsetX, point1.m_y + offsetY);
    beltPath.AddQuadCurveToPoint(controlPoint.m_x, controlPoint.m_y, point2.m_x + offsetX, point2.m_y + offsetY);

    // Set the pen for drawing the belt
    graphics->SetPen(wxPen(*wxBLACK, 2.0, wxPENSTYLE_SOLID));

    // Draw the belt path
    graphics->StrokePath(beltPath);
}

/**
 * Compute Belt Rocking Amount
 * @param elapsed delta time
 */
void Pulley::Update(double elapsed)
{
    mTime += elapsed;
}
