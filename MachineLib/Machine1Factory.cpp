/**
 * @file Machine1Factory.cpp
 * @author Charles Owen
 */

#include "pch.h"
#include "Machine1Factory.h"
#include "MachineActual.h"
#include "HamsterAndConveyorFactory.h"
#include "Body.h"
#include "Hamster.h"
#include "Conveyor.h"

/**
 * Factory method to create machine #1
 * @return
 */
std::shared_ptr<MachineActual> Machine1Factory::Create()
{
    // The machine itself
    // In this solution the machine number is passed
    // to the working machine constructor, so it knows
    // its number.
    auto machine = std::make_shared<MachineActual>();

    // Notice: All dimensions are in centimeters and assumes
    // the Y axis is positive in the up direction.

    const double FloorWidth = 600;
    const double FloorHeight = 15;

    //
    // The floor
    //
    // The values are chosen so the top of the floor
    // is at Y=0
    //
    auto floor = std::make_shared<Body>();
    floor->Rectangle(-FloorWidth / 2, -FloorHeight, FloorWidth, FloorHeight);
    floor->SetImage(GetImageDir() + L"/floor.png");
    machine->AddComponent(floor);

    //
    // Create the top beam and the basketball
    // that rolls off of it
    //
    TopBeamAndRamp(machine);

    //
    // Create the beam with the hamster driving a
    // spinning arm that hits the ball to make it roll
    //
    BeamAndSpinningArm(machine);

    //
    // Create a stack of dominos
    //
    const auto DominoStack1Position = wxPoint2DDouble(-230, 0);

    DominoStack(machine, DominoStack1Position);

    //
    // Create another stack of dominos
    //
    const auto DominoStack2Position = wxPoint2DDouble(115, 0);

    DominoStack(machine, DominoStack2Position);

    //
    // Create a factory that will manufacture hamster, pulley,
    // pulley, and conveyor assemblies
    //
    HamsterAndConveyorFactory hamsterAndConveyorFactory(machine, GetImageDir());

    //
    // First conveyor with a ball sitting on it
    //
    hamsterAndConveyorFactory.Create(wxPoint2DDouble(240, 0), wxPoint2DDouble(100, 90));
    hamsterAndConveyorFactory.AddBall(40);
    auto hamster1 = hamsterAndConveyorFactory.GetHamster();
    auto conveyor1 = hamsterAndConveyorFactory.GetConveyor();
    hamster1->SetSpeed(-1);

    //
    // Second conveyor with a ball on it
    //
    wxPoint2DDouble conveyor2position(-230, 130);

    // Dominos on a beam that the conveyor ball will knock down.
    // Add this first, so it is behind the second conveyor pulleys
    DominoesOnBeam(machine, conveyor2position + wxPoint2DDouble(140, 0));

    hamsterAndConveyorFactory.Create(conveyor1->GetPosition() + wxPoint2DDouble(-105, -40), conveyor2position);
    hamsterAndConveyorFactory.AddBall(-40);
    auto hamster2 = hamsterAndConveyorFactory.GetHamster();
    auto conveyor2 = hamsterAndConveyorFactory.GetConveyor();

    //
    // Third hamster/conveyor assembly.
    //
    wxPoint2DDouble conveyor3position(150, 200);

    hamsterAndConveyorFactory.Create(conveyor2position + wxPoint2DDouble(260, 20), conveyor3position);
    hamsterAndConveyorFactory.AddBall(-40);
    auto hamster3 = hamsterAndConveyorFactory.GetHamster();
    hamster3->SetSpeed(1.5);
    auto conveyor3 = hamsterAndConveyorFactory.GetConveyor();

    //
    // We add the baskedball goal last, so all basketballs
    // will draw behind it.
    //
    BasketballGoal(machine);

    return machine;
}
