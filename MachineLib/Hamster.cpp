/**
 * @file Hamster.cpp
 * @author Devin DeMatto
 */

#include "pch.h"
#include "Hamster.h"

/// The center point for drawing the wheel
/// relative to the bottom center of the cage
const auto WheelCenter = wxPoint2DDouble(-12, 24);

/// The size of the hamster cage in centimeters
const auto HamsterCageSize = wxSize(75, 50);

/// Size of the hamster wheel (diameter) in centimeters
const double HamsterWheelSize = 45;

/// Size of the hamster wheel (square) in centimeters
const double HamsterSize = 45;

/// How fast the hamster runs. This is now many cycles of
/// the 3 images we make per second as images 1, 2, 3, 2, ...
const double HamsterSpeed = 4.0;

/// The offset from the bottom center of the hamster cage
/// to the center of the output shaft.
const auto HamsterShaftOffset = wxPoint2DDouble(25, 40);

/// The image for the hamster cage
const std::wstring HamsterCageImage = L"/hamster-cage.png";

/// The image for the hamster wheel
const std::wstring HamsterWheelImage = L"/hamster-wheel.png";

/// The hamster images. Image 0 is sleeping, 1-3 are
/// the running hamster animation images.
const std::wstring HamsterImages[4] =
    {L"/hamster-sleep.png", L"/hamster-run-1.png",
        L"/hamster-run-2.png", L"/hamster-run-3.png"};

/**
 * Constructor for Hamster
 * @param imagedir ImageDirectory
 */
Hamster::Hamster(std::wstring imagedir)
{
    // Initialize Cage and Wheel with Images
    mHamsterCage.BottomCenteredRectangle(HamsterCageSize);
    mHamsterCage.SetImage(imagedir + HamsterCageImage);

    mHamsterWheel.CenteredSquare(HamsterWheelSize);
    mHamsterWheel.SetImage(imagedir + HamsterWheelImage);

    // Load Hamster Images for Different States
    for(const auto &HamsterImage : HamsterImages)
    {
        std::unique_ptr<cse335::Polygon> hamster(new cse335::Polygon());
        hamster->CenteredSquare(HamsterSize);
        hamster->SetImage(imagedir + HamsterImage);
        mHamsters.push_back(std::move(hamster));
    }
}

/**
 * Sets Initial Positions for all Polygons
 * @param x X Position
 * @param y Y Position
 */
void Hamster::SetPosition(double x, double y)
{
    mHamsterCage.SetInitialPosition(x, y);
}

/**
 * Draw Hamster to Screen
 * @param graphics Graphics Context
 */
void Hamster::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    graphics->PushState();

    mHamsterCage.Draw(graphics);

    graphics
        ->Translate(mHamsterCage.GetPosition().m_x + WheelCenter.m_x, mHamsterCage.GetPosition().m_y + WheelCenter.m_y);
    mHamsterWheel.DrawPolygon(graphics, 0, 0, mRotation);

    // Check the speed for flipping the hamster if needed
    if(mSpeed < 0)
    {
        graphics->Scale(-1, 1);
    }

    mHamsters[mHamsterIndex]->DrawPolygon(graphics, 0, 0, 0);

    graphics->PopState();
}

/**
 * Update Method
 * @param elapsed elapsed time
 */
void Hamster::Update(double elapsed)
{
    // Don't Update if not running
    if(!mIsRunning)
    {
        return;
    }

    // Update Rotation
    mRotation += -mSpeed * elapsed;

    // Calculate the total rotation considering HamsterSpeed
    double totalRotation = mRotation * HamsterSpeed / mSpeed;

    // Normalize totalRotation to stay within the 0 to 1 range per cycle
    double normalizedRotation = fmod(fabs(totalRotation), 1.0);

    // Determine the current image based on the normalized rotation
    if(normalizedRotation < 0.25) {
        mHamsterIndex = 1; // Image 1
    } else if(normalizedRotation < 0.50) {
        mHamsterIndex = 2; // Image 2
    } else if(normalizedRotation < 0.75) {
        mHamsterIndex = 3; // Image 3
    } else {
        mHamsterIndex = 2; // Back to Image 2
    }

    // Update Source Rotation
    mSource.UpdateRotation(mRotation, -mSpeed);
}

/**
 * Handle a contact beginning
 * @param contact Contact object
 */
void Hamster::BeginContact(b2Contact *contact)
{
    b2ContactListener::BeginContact(contact);
    SetInitiallyRunning(true);
}

/**
 * Should Hamster be Running
 * @param isRunning boolean
 */
void Hamster::SetInitiallyRunning(bool isRunning)
{
    mIsRunning = isRunning;

}

/**
 * Set Speed for Hamster
 * @param speed double
 */
void Hamster::SetSpeed(double speed)
{
    mSpeed = speed;
}

/**
 * Returns the Shaft Position Relative to the Position of Hamster
 * @return double
 */
wxPoint2DDouble Hamster::GetShaftPosition()
{
    return mHamsterCage.GetPosition() + HamsterShaftOffset;
}


