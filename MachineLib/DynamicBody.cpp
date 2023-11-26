/**
 * @file DynamicBody.cpp
 * @author Devin
 */

#include "pch.h"
#include "DynamicBody.h"

/// Constructor
DynamicBody::DynamicBody()
{
}


/**
 * Sets Body to Be Dynamic
 */
void DynamicBody::SetDynamic()
{
    GetPolygon()->SetDynamic();
}
