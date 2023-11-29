/**
 * @file Pulley.cpp
 * @author Devin DeMatot
 */

#include "pch.h"
#include "Pulley.h"

#ifndef M_PI
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
        // Calculate theta
        double dx = mConnected->GetPosition().m_x - mPosition.m_x;
        double dy = mConnected->GetPosition().m_y - mPosition.m_y;
        double theta = atan2(dy, dx);

        // Calculate the distance between pulley centers
        double distance = sqrt(dx * dx + dy * dy);

        // Calculate phi
        double phi = asin(abs(mConnected->mRadius - mRadius) / distance);

        // Determine the direction of the belt based on rotation
        double betaPositive, betaNegative;
        if(mRotation >= 0)
        {
            // Positive to positive rotation
            betaPositive = theta + phi + M_PI / 2;
            betaNegative = theta - phi - M_PI / 2;
        }
        else
        {
            // Negative to negative rotation (reverse the direction)
            betaPositive = theta - phi - M_PI / 2;
            betaNegative = theta + phi + M_PI / 2;
        }

        // Calculate the tangent points on the edge of the pulleys
        wxPoint2DDouble
            point1Positive(mPosition.m_x + mRadius * cos(betaPositive), mPosition.m_y + mRadius * sin(betaPositive));
        wxPoint2DDouble point2Positive(mConnected->GetPosition().m_x + mConnected->mRadius * cos(betaPositive),
                                       mConnected->GetPosition().m_y + mConnected->mRadius * sin(betaPositive));

        wxPoint2DDouble
            point1Negative(mPosition.m_x + mRadius * cos(betaNegative), mPosition.m_y + mRadius * sin(betaNegative));
        wxPoint2DDouble point2Negative(mConnected->GetPosition().m_x + mConnected->mRadius * cos(betaNegative),
                                       mConnected->GetPosition().m_y + mConnected->mRadius * sin(betaNegative));

        // Set the pen width to the belt width
        graphics->SetPen(wxPen(wxColour(0, 0, 0), 2.0, wxPENSTYLE_SOLID));

        // Draw the belts as lines between the tangent points
        graphics->StrokeLine(point1Positive.m_x, point1Positive.m_y, point2Positive.m_x, point2Positive.m_y);
        graphics->StrokeLine(point1Negative.m_x, point1Negative.m_y, point2Negative.m_x, point2Negative.m_y);
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
    }

    // Additionally, update this pulley's source to notify the conveyor or any other connected sinks
    mSource.UpdateRotation(rotation, -speed);
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
