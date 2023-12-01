/**
 * @file HamsterAndConveyorFactory.cpp
 * @author Charles Owen
 */

#include "pch.h"
#include "HamsterAndConveyorFactory.h"
#include "Hamster.h"
#include "Body.h"
#include "DynamicBody.h"
#include "MachineActual.h"
#include "Pulley.h"
#include "Conveyor.h"

/**
 * Create a hamster that is a conveyor.
 * @param hamsterPosition Where to place the hamster
 * @param conveyorPosition Where to place the conveyor
 * @param pulley1Size Size of Pulley 1
 * @param pulley2Size Size of Pulley 2
 */
void HamsterAndConveyorFactory::Create(wxPoint2DDouble hamsterPosition,
                                       wxPoint2DDouble conveyorPosition,
                                       double pulley1Size,
                                       double pulley2Size)
{
    auto hamster = std::make_shared<Hamster>(mImagesDir);
    mHamster = hamster;
    hamster->SetPosition(hamsterPosition.m_x, hamsterPosition.m_y);
    mMachine->AddComponent(hamster);
    auto hamsterShaft = hamster->GetShaftPosition();

    auto conveyor = std::make_shared<Conveyor>(mImagesDir);
    mConveyor = conveyor;
    conveyor->SetPosition(conveyorPosition);
    mMachine->AddComponent(conveyor);
    auto conveyorShaft = conveyor->GetShaftPosition();

    // The pulley driven by the hamster
    auto pulley1 = std::make_shared<Pulley>(pulley1Size);
    pulley1->SetImage(mImagesDir + L"/pulley3.png");
    pulley1->SetPosition(hamsterShaft);
    mMachine->AddComponent(pulley1);

    hamster->GetSource()->ConnectSink(pulley1);

    auto pulley2 = std::make_shared<Pulley>(pulley2Size);
    pulley2->SetImage(mImagesDir + L"/pulley3.png");
    pulley2->SetPosition(conveyorShaft);
    mMachine->AddComponent(pulley2);

    pulley1->Drive(pulley2);

    pulley2->GetSource()->ConnectSink(conveyor);
}

/**
 * Add a ball onto the conveyor belt for the just created hamster
 * conveyor belt combination.
 * @param placement Placement left (negative) to right (positive)
 * @return Gall object
 */
std::shared_ptr<Body> HamsterAndConveyorFactory::AddBall(double placement)
{
    // Ball
    auto ball = std::make_shared<DynamicBody>();
    ball->Circle(12);
    ball->SetImage(mImagesDir + L"/ball1.png");
    auto position = mConveyor->GetPosition() + wxPoint2DDouble(placement, 26);
    ball->SetInitialPosition(position.m_x, position.m_y);
    ball->SetDynamic();
    ball->SetPhysics(2, 0.5, 0.1);
    mMachine->AddComponent(ball);

    return ball;
}
