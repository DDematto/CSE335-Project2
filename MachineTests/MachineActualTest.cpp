/**
 * @file MachineActualTest.cpp
 * @author Devin DeMatto
 */


#include "pch.h"
#include "gtest/gtest.h"

#include <MachineActual.h>
#include <Component.h>

TEST(MachineActualTest, Constructor)
{
    MachineActual machineActual;
    ASSERT_EQ(machineActual.GetMachineNumber(), 0);
    ASSERT_TRUE(machineActual.GetLocation().x == 500 && machineActual.GetLocation().y == 500);
}

TEST(MachineActualTest, Components)
{
    MachineActual machineActual;

    // Test initial state with zero components
    auto initialComponents = machineActual.GetComponents();
    ASSERT_TRUE(initialComponents.empty());

    // Add a component and test again
    auto component = std::make_shared<Component>();
    machineActual.AddComponent(component);
    auto componentsAfterAdd = machineActual.GetComponents();
    ASSERT_EQ(componentsAfterAdd.size(), 1);
}