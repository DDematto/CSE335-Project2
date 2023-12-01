/**
 * @file GeneralMachineFactory.cpp
 * @author Devin DeMatto
 */

#include "pch.h"
#include "GeneralMachineFactory.h"
#include "MachineActual.h"
#include "Body.h"
#include "Goal.h"
#include "DynamicBody.h"
#include "Hamster.h"
#include "KinematicBody.h"
#include "Conveyor.h"

/// The images directory in resources
const std::wstring ImagesDirectory = L"/images";

/**
 * Constructor
 * @param resourcesDir Path to the resources directory
 */
GeneralMachineFactory::GeneralMachineFactory(std::wstring resourcesDir) :
    mResourcesDir(resourcesDir)
{
    mImagesDir = mResourcesDir + ImagesDirectory;
}

/**
 * Generate the top beam and its basketball
 *
 * The top beam and ramp and basketball that
 * rolls right and goes through the hoop.
 * @param machine Beam to generate
 */
void GeneralMachineFactory::TopBeamAndRamp(std::shared_ptr<MachineActual> machine)
{
    const double BeamX = -25;
    auto beam1 = std::make_shared<Body>();
    beam1->BottomCenteredRectangle(400, 20);
    beam1->SetImage(mImagesDir + L"/beam.png");
    beam1->SetInitialPosition(BeamX, 300);
    machine->AddComponent(beam1);

    auto wedge1 = std::make_shared<Body>();
    wedge1->AddPoint(-25, 0);
    wedge1->AddPoint(25, 0);
    wedge1->AddPoint(25, 4.5);
    wedge1->AddPoint(-25, 25);
    wedge1->SetImage(mImagesDir + L"/wedge.png");
    wedge1->SetInitialPosition(BeamX - 175, 320);
    machine->AddComponent(wedge1);

    // Basketball 1
    auto basketball1 = std::make_shared<DynamicBody>();
    basketball1->Circle(12);
    basketball1->SetImage(mImagesDir + L"/basketball1.png");
    basketball1->SetInitialPosition(BeamX - 186, 353);
    basketball1->SetDynamic();
    basketball1->SetPhysics(1, 0.5, 0.6);
    machine->AddComponent(basketball1);
}

/**
 * Create a stack of 9 dominos.
 * @param machine Machine to add to
 * @param position The position to draw the domino stack at
 */
void GeneralMachineFactory::DominoStack(std::shared_ptr<MachineActual> machine, wxPoint2DDouble position)
{
    Domino(machine, position + wxPoint2DDouble(30, DominoHeight / 2), 0, DominoColor::Red);
    Domino(machine, position + wxPoint2DDouble(10, DominoHeight / 2), 0, DominoColor::Blue);
    Domino(machine, position + wxPoint2DDouble(20, DominoHeight + DominoWidth / 2), 0.25, DominoColor::Green);

    Domino(machine, position + wxPoint2DDouble(-10, DominoHeight / 2), 0, DominoColor::Red);
    Domino(machine, position + wxPoint2DDouble(-30, DominoHeight / 2), 0, DominoColor::Green);
    Domino(machine, position + wxPoint2DDouble(-20, DominoHeight + DominoWidth / 2), 0.25, DominoColor::Black);

    const int DominoLevel2 = DominoHeight + DominoWidth;

    Domino(machine, position + wxPoint2DDouble(10, DominoLevel2 + DominoHeight / 2), 0, DominoColor::Red);
    Domino(machine, position + wxPoint2DDouble(-10, DominoLevel2 + DominoHeight / 2), 0, DominoColor::Green);
    Domino(machine,
           position + wxPoint2DDouble(0, DominoLevel2 + DominoHeight + DominoWidth / 2),
           0.25,
           DominoColor::Black);
}

/**
 * This is the second beam from the top and the spinning arm that hits the ball
 * @param machine Machine to add to
 */
void GeneralMachineFactory::BeamAndSpinningArm(std::shared_ptr<MachineActual> machine)
{
    const double Beam2X = -25;
    auto beam2 = std::make_shared<Body>();
    beam2->BottomCenteredRectangle(400, 20);
    beam2->SetImage(mImagesDir + L"/beam.png");
    beam2->SetInitialPosition(Beam2X, 240);
    machine->AddComponent(beam2);

    // Basketball 2
    auto basketball2 = std::make_shared<DynamicBody>();
    basketball2->Circle(12);
    basketball2->SetImage(mImagesDir + L"/basketball2.png");
    basketball2->SetInitialPosition(Beam2X - 170, 240 + 12 + 20);
    basketball2->SetDynamic();
    basketball2->SetPhysics(1, 0.5, 0.75);
    machine->AddComponent(basketball2);

    //
    // The hamster motor for the second-beam
    //
    auto hamster = std::make_shared<Hamster>(mImagesDir);
    hamster->SetPosition(-220, 185);
    hamster->SetInitiallyRunning(true);      // Initially running
    hamster->SetSpeed(0.6);
    machine->AddComponent(hamster);

    auto hamster1shaft = hamster->GetShaftPosition();

    auto arm = std::make_shared<KinematicBody>();
    arm->SetInitialPosition(hamster1shaft.m_x, hamster1shaft.m_y);
    arm->AddPoint(-7, 10);
    arm->AddPoint(7, 10);
    arm->AddPoint(7, -60);
    arm->AddPoint(-7, -60);
    arm->SetImage(mImagesDir + L"/arm.png");
    arm->SetKinematic();
    machine->AddComponent(arm);

    hamster->GetSource()->ConnectSink(arm);
}

/**
 * Add the basketball goal to the machine
 * @param machine Machine to add to
 */
void GeneralMachineFactory::BasketballGoal(std::shared_ptr<MachineActual> machine)
{
    auto goal = std::make_shared<Goal>(mImagesDir);
    goal->SetPosition(270, 0);
    machine->AddComponent(goal);
}

/**
 * Create the beam that has 10 dominoes on it.
 * @param machine Machine to add bem to
 * @param position Location to place the beam.
 */
void GeneralMachineFactory::DominoesOnBeam(std::shared_ptr<MachineActual> machine, wxPoint2DDouble position)
{
    // The beam the dominoes sit on
    auto beam = std::make_shared<Body>();
    beam->BottomCenteredRectangle(150, 15);
    beam->SetImage(mImagesDir + L"/beam.png");
    beam->SetInitialPosition(position.m_x, position.m_y);
    machine->AddComponent(beam);

    for(int d = 0; d < 10; d++)
    {
        // Where to put this domino
        auto dominos = position + wxPoint2DDouble(-70 + d * 15, 27);

        Domino(machine, dominos, 0, DominoColor::Green);
    }
}

/**
 * Create a Domino and add it to the machine.
 *
 * This has been created to make it easier to create
 * a lot of dominos
 *
 * @param machine Machine to add the domino to
 * @param position Position to place the center of the domino
 * @param rotation Rotation in turns
 * @param color Color code
 * @return Returns the created domino body
 */
std::shared_ptr<Body> GeneralMachineFactory::Domino(std::shared_ptr<MachineActual> machine,
                                                    wxPoint2DDouble position,
                                                    double rotation,
                                                    DominoColor color)
{
    auto x = position.m_x;
    auto y = position.m_y;

    auto domino = std::make_shared<DynamicBody>();
    domino->Rectangle(-DominoWidth / 2, -DominoHeight / 2, DominoWidth, DominoHeight);
    switch(color)
    {
        case DominoColor::Black:domino->SetImage(mImagesDir + L"/domino-black.png");
            break;

        case DominoColor::Red:domino->SetImage(mImagesDir + L"/domino-red.png");
            break;

        case DominoColor::Green:domino->SetImage(mImagesDir + L"/domino-green.png");
            break;

        case DominoColor::Blue:domino->SetImage(mImagesDir + L"/domino-blue.png");
            break;
    }

    domino->SetInitialPosition(x, y);
    domino->SetInitialRotation(rotation);
    domino->SetDynamic();
    machine->AddComponent(domino);

    return domino;
}

