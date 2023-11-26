/**
 * @file MachineCFactory.cpp
 * @author Charles Owen
 */

#include "pch.h"
#include "MachineCFactory.h"
#include "MachineActual.h"
#include "Body.h"
#include "DynamicBody.h"
#include "Goal.h"

/// The images directory in resources
const std::wstring ImagesDirectory = L"/images";

/**
 * Constructor
 * @param resourcesDir Directory containing the machine resources
 */
MachineCFactory::MachineCFactory(std::wstring resourcesDir) : mResourcesDir(resourcesDir)
{
    mImagesDir = resourcesDir + ImagesDirectory;
}

/**
 * Create a machine
 * @return Pointer to newly created machine
 */
std::shared_ptr<MachineActual> MachineCFactory::Create()
{
    auto machine = std::make_shared<MachineActual>();

    // Notice: All dimensions are in centimeters and assume
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
    floor->SetImage(mImagesDir + L"/floor.png");
    machine->AddComponent(floor);

    const double BeamX = -25;

    // Basketball 1
    auto basketball1 = std::make_shared<DynamicBody>();
    basketball1->Circle(12);
    basketball1->SetImage(mImagesDir + L"/basketball1.png");
    basketball1->SetInitialPosition(0, 353);
    basketball1->SetDynamic();
    basketball1->SetPhysics(1, 0.5, 0.6);
    machine->AddComponent(basketball1);

    auto goal = std::make_shared<Goal>(mImagesDir);
    goal->SetPosition(250, 0);
    machine->AddComponent(goal);

    return machine;
}