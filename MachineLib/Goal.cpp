/**
 * @file Goal.cpp
 * @author Devin DeMatto
 */

#include "pch.h"
#include "Goal.h"

/// Image to draw for the goal
const std::wstring GoalImage = L"/goal.png";

/// Size to draw the entire goal post image
/// This does not go into the physics system at all
const auto GoalSize = wxSize(65, 247);

/// Size to create a rectangle in the physics system only
/// (does not draw) to reflect off of the backboard and post
const auto PostSize = wxSize(10, 250);

/// Size of a target object inside the goal net that
/// we'll consider a score when touched by a ball
const auto TargetSize = wxSize(20, 5);

/// The color of the scoreboard background
const auto ScoreboardBackgroundColor = wxColor(24, 69, 59);

/// Width of the black line around the scoreboard
const int ScoreboarderLineWidth = 3;

/// Scoreboard font size (height) in cm
/// The font color is white
const int ScoreboardFontSize = 20;

/// Rectangle that represents the location relative to the
/// goal position for the scoreboard and its size.
const auto ScoreboardRectangle = wxRect2DDouble(5, 280, 30, 20);

/// Location of the scoreboard text relative to the
/// scoreboard location in cm.
const auto ScoreboardTextLocation = wxPoint2DDouble(9, 299);

/**
 * Constructor
 * @param imagesDir Image Path
 */
Goal::Goal(std::wstring imagesDir)
{
    mHoop.BottomCenteredRectangle(GoalSize);
    mHoop.SetImage(imagesDir + GoalImage);

    mPost.BottomCenteredRectangle(PostSize);
    mPost.SetColor(*wxBLUE);

    mTarget.BottomCenteredRectangle(TargetSize);
    mTarget.SetColor(*wxBLUE);
}

/**
 * Draw the component
 * @param graphics The graphics context to draw on
 */
void Goal::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    graphics->PushState();

    mHoop.DrawPolygon(graphics, mPosition.x, mPosition.y, 0);
    mPost.Draw(graphics);
    mTarget.Draw(graphics);

    // Draw the scoreboard based on the image specified
    graphics->Translate(mPosition.x, mPosition.y);
    graphics->SetBrush(wxBrush(ScoreboardBackgroundColor));
    graphics->SetPen(wxPen(*wxBLACK, ScoreboarderLineWidth));
    graphics->DrawRectangle(ScoreboardRectangle.m_x,
                            ScoreboardRectangle.m_y,
                            ScoreboardRectangle.m_width,
                            ScoreboardRectangle.m_height);

    // Setup Scoreboard Text
    graphics->Translate(ScoreboardTextLocation.m_x, ScoreboardTextLocation.m_y);

    // Invert To Draw Upright
    graphics->Scale(1, -1);

    // Format the score with leading zeros if necessary
    wxFont font = wxFont(wxSize(0, ScoreboardFontSize), wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
    graphics->SetFont(font, *wxWHITE);

    // Create String and Convert Score
    std::wstring scoreText = std::to_wstring(mScore);

    // Append 0 if Less than 10
    if(mScore < 10)
    {
        scoreText.insert(0, 1, L'0');
    }

    graphics->DrawText(scoreText, 0, -2);
    graphics->PopState();
}

/**
 * Handle a contact beginning
 * @param contact Contact object
 */
void Goal::BeginContact(b2Contact *contact)
{
    mScore += 2;
}

/**
 * Handle before the solution of a contact with the
 * scoreboard target object. We take this time to
 * turn off the contact, so the ball will pass through.
 * @param contact Contqct object
 * @param manifold Manifold object
 */
void Goal::PreSolve(b2Contact *contact, const b2Manifold *manifold)
{
    contact->SetEnabled(false);
}

/**
 * Set Position
 * @param x X
 * @param y Y
 */
void Goal::SetPosition(int x, int y)
{
    mPosition = wxPoint(x, y);
    mTarget.SetInitialPosition(x - 13, y + 165);
    mPost.SetInitialPosition(x + 20, y);
}
