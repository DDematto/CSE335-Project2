/**
 * @file PictureFactory.cpp
 * @author Charles Owen
 */

#include "pch.h"
#include "PictureFactory.h"
#include "Picture.h"
#include "HaroldFactory.h"
#include "SpartyFactory.h"
#include "Actor.h"
#include "ImageDrawable.h"
#include "MachineDrawable.h"

/// Directory within resources that contains the images.
const std::wstring ImagesDirectory = L"/images";

/**
 * Factory method to create a new picture.
 * @param resourcesDir Directory that contains the resources for this application
 * @param machineDrawable Passed in Machine Drawable Object
 * @return The created picture
 */
std::shared_ptr<Picture> PictureFactory::Create(std::wstring resourcesDir,
                                                std::shared_ptr<MachineDrawable> machineDrawable)
{
    auto imagesDir = resourcesDir + ImagesDirectory;

    auto picture = std::make_shared<Picture>();

    // Create the background and add it
    auto background = std::make_shared<Actor>(L"Background");
    background->SetClickable(false);
    background->SetPosition(wxPoint(0, 0));
    auto backgroundI = std::make_shared<ImageDrawable>(L"Background", imagesDir + L"/Background.jpg");
    background->AddDrawable(backgroundI);
    background->SetRoot(backgroundI);
    picture->AddActor(background);

    // Create Machine Actor and Add to System & Picture
    auto machineActor = std::make_shared<Actor>(L"Machine Actor");
    machineActor->AddDrawable(machineDrawable);
    machineDrawable->SetPosition(wxPoint(1200, 1000));
    machineDrawable->SetActor(machineActor);
    picture->AddActor(machineActor);

    // Create a Flag and add it
    auto flag = std::make_shared<Actor>(L"Background");
    flag->SetClickable(true);
    flag->SetPosition(wxPoint(1000, 300));
    auto flagI = std::make_shared<ImageDrawable>(L"Flag", imagesDir + L"/flag.png");
    flag->AddDrawable(flagI);
    flagI->SetCenter(wxPoint(127, 294));
    flag->SetRoot(flagI);
    picture->AddActor(flag);

    // Create and add Harold
    HaroldFactory haroldFactory;
    auto harold = haroldFactory.Create(imagesDir);

    // This is where Harold will start out.
    harold->SetPosition(wxPoint(300, 600));
    picture->AddActor(harold);

    // Create and add Sparty
    SpartyFactory spartyFactory;
    auto sparty = spartyFactory.Create(imagesDir);

    sparty->SetPosition(wxPoint(950, 600));
    picture->AddActor(sparty);

    return picture;
}

