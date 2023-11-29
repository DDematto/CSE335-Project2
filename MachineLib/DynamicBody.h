/**
 * @file DynamicBody.h
 * @author Devin DeMatto
 */

#ifndef CANADIANEXPERIENCE_MACHINELIB_DYNAMICBODY_H
#define CANADIANEXPERIENCE_MACHINELIB_DYNAMICBODY_H

#include "Body.h"

/**
 * Created Bodies That are Dynamic in World
 */
class DynamicBody : public Body
{
public:
    DynamicBody() = default;

    /// Copy constructor (disabled)
    DynamicBody(const DynamicBody &) = delete;

    /// Assignment operator (disabled)
    void operator=(const DynamicBody &) = delete;

    /**
     * Sets Body to Be Dynamic
     */
    void SetDynamic()
    {
        GetPolygon()->SetDynamic();
    }
};

#endif //CANADIANEXPERIENCE_MACHINELIB_DYNAMICBODY_H
