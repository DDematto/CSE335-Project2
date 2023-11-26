/**
 * @file Body.cpp
 * @author Devin DeMatto
 */

#include "pch.h"
#include "Body.h"

/**
 * Constructor
 */
Body::Body()
{
}

/**
 * Draws the Body component.
 * @param graphics Graphics context to use for drawing.
 */
void Body::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    mPolygon.Draw(graphics);
}

void Body::Rectangle(double x, double y, double width, double height)
{
    mPolygon.Rectangle(x, y, width, height);
}


void Body::SetImage(std::wstring image)
{
    mPolygon.SetImage(image);
}

void Body::Circle(double radius)
{
    mPolygon.Circle(radius);
}

void Body::SetInitialPosition(double x, double y)
{
    mPolygon.SetInitialPosition(x, y);
}

void Body::SetPhysics(double density, double friction, double restitution)
{
    mPolygon.SetPhysics(density, friction, restitution);
}

void Body::BottomCenteredRectangle(double x, double y)
{
    mPolygon.BottomCenteredRectangle(x, y);
}

void Body::AddPoint(double x, double y)
{
    mPolygon.AddPoint(x, y);
}

void Body::SetInitialRotation(double rotation)
{
    mPolygon.SetInitialRotation(rotation);
}
