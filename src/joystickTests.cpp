#include <gtest/gtest.h>

extern "C" {
    #include "joystickControl.c"
}

TEST(JoystickControl, WhenNoMovementShouldReturnFalse) {
    // ARRANGE
    uint16_t horz = 512;
    uint16_t vert = 512;
    bool hasChanged = false;
    int8_t num = 1;

    // ACT
    bool result = handleInput(horz, vert, &hasChanged, &num);

    // ASSERT
    ASSERT_FALSE(result);
}

TEST(JoystickControl, WhenMovedUpShouldReturnTrueAndNumShouldBeThree) {
    // ARRANGE
    uint16_t horz = 512;
    uint16_t vert = 1023;
    bool hasChanged = true;
    int8_t num = 1;

    // ACT
    bool result = handleInput(horz, vert, &hasChanged, &num);

    // ASSERT
    ASSERT_TRUE(result);
    ASSERT_EQ(num, 3);
}
