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
    DynamicBody();

    void SetDynamic();
};

#endif //CANADIANEXPERIENCE_MACHINELIB_DYNAMICBODY_H
