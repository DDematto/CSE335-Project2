/**
 * @file Conveyor.cpp
 * @author Devin DeMatto
 */

#include "pch.h"
#include "Conveyor.h"

/// The offset from the bottom center of the conveyor
/// to the center of the drive shaft.  48
const auto ConveyorShaftOffset = wxPoint2DDouble(48, 4);

/// The size of the conveyor in cm
const auto ConveyorSize = wxSize(125, 14);

/// The conveyor image to use
const std::wstring ConveyorImageName = L"/conveyor.png";

/**
 * Constructor
 * @param resourceDir Image Name to be Loaded
 */
Conveyor::Conveyor(const std::wstring &resourceDir)
{
    mConveyorMech.BottomCenteredRectangle(ConveyorSize);
    mConveyorMech.SetImage(resourceDir + ConveyorImageName);
}

/**
 * Graphics For Polygon
 * @param graphics Graphics Context
 */
void Conveyor::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    graphics->PushState();
    mConveyorMech.Draw(graphics);
    graphics->PopState();
}

/**
 * Setup Before Start
 * @param contact Contqct object
 * @param manifold Manifold object
 */
void Conveyor::PreSolve(b2Contact *contact, const b2Manifold *manifold)
{
    contact->SetTangentSpeed(-mSpeed);
}

/**
 * Update Function for Conveyor
 * @param elapsed Elapsed Time
 */
void Conveyor::Update(double elapsed)
{
    auto contact = mConveyorMech.GetBody()->GetContactList();
    while(contact != nullptr)
    {
        if(contact->contact->IsTouching())
        {
            contact->other->SetLinearVelocity(b2Vec2(-mSpeed, 0));
        }

        contact = contact->next;
    }
}

/**
 * Sets Speed of Conveyor
 * @param rotation Rotation
 * @param speed Speed
 */
void Conveyor::SetRotation(double rotation, double speed)
{
    mSpeed = speed;
}

/**
 * Calculate Shaft Position Based on Conveyor Polygon
 * @return
 */
wxPoint2DDouble Conveyor::GetShaftPosition()
{
    return mConveyorMech.GetPosition() + ConveyorShaftOffset;
}

/**
 * Sets Position of Conveyor Polygon
 * @param position Position as wxPoint2Double
 */
void Conveyor::SetPosition(wxPoint2DDouble position)
{
    mConveyorMech.SetInitialPosition(position.m_x, position.m_y);
}



