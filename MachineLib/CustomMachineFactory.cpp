/**
 * @file CustomMachineFactory.cpp
 * @author Devin DeMatto
 */

#include "pch.h"
#include "CustomMachineFactory.h"
#include "MachineActual.h"
#include "HamsterAndConveyorFactory.h"
#include "Body.h"
#include "Hamster.h"
#include "Conveyor.h"
#include "Pulley.h"

/**
 * Create the Machine
 * @return Machine #2
 */
std::shared_ptr<MachineActual> CustomMachineFactory::Create()
{
    auto machine = std::make_shared<MachineActual>();

    const double FloorWidth = 600;
    const double FloorHeight = 15;

    //
    // Floor Component
    //
    auto floor = std::make_shared<Body>();
    floor->Rectangle(-FloorWidth / 2, -FloorHeight, FloorWidth, FloorHeight);
    floor->SetImage(GetImageDir() + L"/floor.png");
    machine->AddComponent(floor);

    //
    // Showing Off Different Sized Pulleys Working
    //
    auto hamster = std::make_shared<Hamster>(GetImageDir());
    hamster->SetPosition(-250, 100);
    hamster->SetInitiallyRunning(true);
    machine->AddComponent(hamster);
    auto hamsterShaft = hamster->GetShaftPosition();


    // The pulley driven by the hamster
    auto pulley1 = std::make_shared<Pulley>(10);
    pulley1->SetImage(GetImageDir() + L"/pulley3.png");
    pulley1->SetPosition(hamsterShaft);
    machine->AddComponent(pulley1);

    hamster->GetSource()->ConnectSink(pulley1);

    const wxPoint pulleyPosition = wxPoint(-150, 200);

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
    pulley4->SetPosition(wxPoint(200, 200));
    machine->AddComponent(pulley4);

    pulley3->Drive(pulley4);

    return machine;
}
