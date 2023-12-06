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
 * Constructor to Build the Picture
 * @param resourcesDir Resources Directory
 */
PictureFactory::PictureFactory(std::wstring resourcesDir)
{
    mImagesDir = resourcesDir + ImagesDirectory;

    // Create the background and add it
    auto background = std::make_shared<Actor>(L"Background");
    background->SetClickable(false);
    background->SetPosition(wxPoint(0, 0));
    auto backgroundI = std::make_shared<ImageDrawable>(L"Background", mImagesDir + L"/Background.jpg");
    background->AddDrawable(backgroundI);
    background->SetRoot(backgroundI);
    mPicture->AddActor(background);
}

/**
 * Factory method to create a new picture.
 * @return The created picture
 */
std::shared_ptr<Picture> PictureFactory::AddActors()
{
    // Create and add Harold
    HaroldFactory haroldFactory;
    auto harold = haroldFactory.Create(mImagesDir);

    // This is where Harold will start out.
    harold->SetPosition(wxPoint(300, 600));
    mPicture->AddActor(harold);

    // Create and add Sparty
    SpartyFactory spartyFactory;
    auto sparty = spartyFactory.Create(mImagesDir);

    sparty->SetPosition(wxPoint(950, 600));
    mPicture->AddActor(sparty);

    // Create a Flag and add it
    auto flag = std::make_shared<Actor>(L"Background");
    flag->SetClickable(true);
    flag->SetPosition(wxPoint(1000, 300));
    auto flagI = std::make_shared<ImageDrawable>(L"Flag", mImagesDir + L"/flag.png");
    flag->AddDrawable(flagI);
    flagI->SetCenter(wxPoint(127, 294));
    flag->SetRoot(flagI);
    mPicture->AddActor(flag);

    return mPicture;
}

/**
 * Creates Machine Actor and Adds Drawable to Actor, then To Picture
 * @param machine Machine Drawable
 * @param position Position for machine to be placed in Picture
 */
void PictureFactory::AddMachine(const std::shared_ptr<MachineDrawable> &machine, wxPoint position)
{
    auto machineActor = std::make_shared<Actor>(L"Machine Actor");
    machineActor->AddDrawable(machine);
    machine->SetPosition(position);
    machine->SetActor(machineActor);
    mPicture->AddActor(machineActor);
}


