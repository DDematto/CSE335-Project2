/**
 * @file CustomMachineFactory.cpp
 * @author Devin DeMatto
 */

#include "pch.h"
#include "CustomMachineFactory.h"
#include "MachineActual.h"
#include "Body.h"
#include "Hamster.h"
#include "Conveyor.h"
#include "Pulley.h"
#include "DynamicBody.h"

/**
 * Create the Machine
 * @return Machine #2
 */
std::shared_ptr<MachineActual> CustomMachineFactory::Create()
{
    auto machine = std::make_shared<MachineActual>();

    const double FloorWidth = 800;
    const double FloorHeight = 25;

    // Create the floor
    auto floor = std::make_shared<Body>();
    floor->Rectangle(-FloorWidth / 2, -FloorHeight, FloorWidth, FloorHeight);
    floor->SetImage(GetImageDir() + L"/floor.png");
    machine->AddComponent(floor);

    // PulleyChain
    PulleyChain(machine);

    // Ramp Cascade W/Ball
    wxPoint2DDouble rampStartPos = wxPoint2DDouble(-160, 290);

    Ball(machine, rampStartPos + wxPoint2DDouble(10, 50));

    // Add Cascading Down Ramps
    LeftRamp(machine, rampStartPos);
    RightRamp(machine, rampStartPos);
    LeftRamp(machine, rampStartPos);
    RightRamp(machine, rampStartPos);
    LeftRamp(machine, rampStartPos);
    RightRamp(machine, rampStartPos);
    LeftRamp(machine, rampStartPos);
    RightRamp(machine, rampStartPos);

    // Stack to Start Hamster Machine
    DominoesOnBeam(machine, wxPoint2DDouble(-150, -15));
    DominoesOnBeam(machine, wxPoint2DDouble(0, -15));
    DominoesOnBeam(machine, wxPoint2DDouble(150, -15));

    // Add the basketball goal at the end
    BasketballGoal(machine);

    return machine;
}

/**
 * Create a Ball for Machine
 * @param machine The Machine
 * @param position Ball Position
 */
void CustomMachineFactory::Ball(std::shared_ptr<MachineActual> machine, wxPoint2DDouble position)
{
    auto basketball1 = std::make_shared<DynamicBody>();
    basketball1->Circle(12);
    basketball1->SetImage(GetImageDir() + L"/basketball1.png");
    basketball1->SetInitialPosition(position.m_x, position.m_y);
    basketball1->SetDynamic();
    basketball1->SetPhysics(10, 5, 0.3);
    machine->AddComponent(basketball1);
}

/**
 * Create a Left Ramp For Machine
 * @param machine Machine
 * @param position Ramp Position
 */
void CustomMachineFactory::LeftRamp(std::shared_ptr<MachineActual> machine, wxPoint2DDouble &position)
{
    auto leftRamp = std::make_shared<Body>();
    leftRamp->AddPoint(0, 30);
    leftRamp->AddPoint(0, 0);
    leftRamp->AddPoint(150, 0);
    leftRamp->SetImage(GetImageDir() + L"/wedge.png");
    leftRamp->SetInitialPosition(position.m_x, position.m_y);
    machine->AddComponent(leftRamp);
    position.m_y -= 30;
    position.m_x += 300;
}

/**
 * Create a Right Ramp For Machine
 * @param machine Machine
 * @param position Ramp Position
 */
void CustomMachineFactory::RightRamp(std::shared_ptr<MachineActual> machine, wxPoint2DDouble &position)
{
    auto rightRamp = std::make_shared<Body>();
    rightRamp->AddPoint(0, 0);
    rightRamp->AddPoint(0, 30);
    rightRamp->AddPoint(-150, 0);
    rightRamp->SetImage(GetImageDir() + L"/wedgeI.png");
    rightRamp->SetInitialPosition(position.m_x, position.m_y);
    machine->AddComponent(rightRamp);
    position.m_y -= 30;
    position.m_x -= 300;
}

/**
 * Creates a Series of Chains Showing off Physics for Belts, and Different pulley sizes
 * @param machine Machine
 */
void CustomMachineFactory::PulleyChain(std::shared_ptr<MachineActual> machine)
{
    //
    // Showing Off Different Sized Pulleys Working
    //
    auto hamster = std::make_shared<Hamster>(GetImageDir());
    hamster->SetPosition(-280, 0);
    hamster->SetInitiallyRunning(false);
    hamster->SetSpeed(-10);
    machine->AddComponent(hamster);
    auto hamsterShaft = hamster->GetShaftPosition();


    // The pulley driven by the hamster
    auto pulley1 = std::make_shared<Pulley>(10);
    pulley1->SetImage(GetImageDir() + L"/pulley3.png");
    pulley1->SetPosition(hamsterShaft);
    machine->AddComponent(pulley1);

    hamster->GetSource()->ConnectSink(pulley1);

    const wxPoint pulleyPosition = wxPoint(-280, 150);

    auto pulley2 = std::make_shared<Pulley>(30);
    pulley2->SetImage(GetImageDir() + L"/pulley3.png");
    pulley2->SetPosition(pulleyPosition);
    machine->AddComponent(pulley2);

    pulley1->Drive(pulley2);

    auto pulley3 = std::make_shared<Pulley>(10);
    pulley3->SetImage(GetImageDir() + L"/pulley3.png");
    pulley3->SetPosition(pulleyPosition);
    machine->AddComponent(pulley3);

    pulley2->GetSource()->ConnectSink(pulley3);

    auto pulley4 = std::make_shared<Pulley>(50);
    pulley4->SetImage(GetImageDir() + L"/pulley3.png");
    pulley4->SetPosition(wxPoint(-280, 330));
    machine->AddComponent(pulley4);

    pulley3->Drive(pulley4);

    auto pulley5 = std::make_shared<Pulley>(20);
    pulley5->SetImage(GetImageDir() + L"/pulley3.png");
    pulley5->SetPosition(wxPoint(-280, 330));
    machine->AddComponent(pulley5);

    pulley4->GetSource()->ConnectSink(pulley5);

    Ball(machine, wxPoint2DDouble(100, 370));

    auto conveyor = std::make_shared<Conveyor>(GetImageDir());
    conveyor->SetPosition(wxPoint2DDouble(150, 330));
    auto conveyorShaft = conveyor->GetShaftPosition();
    machine->AddComponent(conveyor);

    auto pulley6 = std::make_shared<Pulley>(40);
    pulley6->SetImage(GetImageDir() + L"/pulley3.png");
    pulley6->SetPosition(conveyorShaft);
    machine->AddComponent(pulley6);

    pulley5->Drive(pulley6);
    pulley5->GetSource()->ConnectSink(conveyor);

}
