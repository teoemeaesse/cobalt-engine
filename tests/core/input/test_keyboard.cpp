//
// Created
// by
// tomas
// on
// 26-12-2023.
//

#include "unity/unity.h"

void setUp(void) {}

void tearDown(void) {}
/*
#include "core/ecs/world.h"
#include "core/input/keyboard.h"

int eventCounter = 0;
const int KEY_MAX = static_cast<int>(cobalt::core::input::KeyboardInputID::COUNT);

class TestClass {
    public:
    TestClass() : value(0), pressed(false) {}  // Initialize 'pressed' to false
    void setValue(int value, bool pressed) {
        this->value = value;
        this->pressed = pressed;
    }
    void assertValue(cobalt::core::input::KeyboardInputID value) { TEST_ASSERT_EQUAL_INT(static_cast<int>(value), this->value); }
    void assertValue(int value) { TEST_ASSERT_EQUAL_INT(value, this->value); }
    void assertPressed() { TEST_ASSERT_EQUAL_INT(true, this->pressed); }
    void assertReleased() { TEST_ASSERT_EQUAL_INT(false, this->pressed); }
    int value;
    bool pressed;
};
#define DEFINE_PERIPHERAL_CMD(num)                                                               \
    class TestPeripheralCmd##num : public cobalt::core::input::ConcreteInputCommand<TestClass> { \
        public:                                                                                  \
        TestPeripheralCmd##num(cobalt::core::ecs::World& world, TestClass* test)                 \
            : cobalt::core::input::ConcreteInputCommand<TestClass>(world, test) {}               \
        void execute() const override {                                                          \
            getTarget()->setValue(num, getInput().active);                                       \
            eventCounter++;                                                                      \
        }                                                                                        \
    };
#define BIND_KEY(world, num, bindptr) \
    keyboard->bind(static_cast<cobalt::core::input::KeyboardInputID>(num), std::make_unique<TestPeripheralCmd##num>(world, bindptr));
#define X(num) DEFINE_PERIPHERAL_CMD(num)
#define Y(world, num, bindptr) BIND_KEY(world, num, bindptr)
// Goes up
// to 78.
// Sue me.
X(0);
X(1);
X(2);
X(3);
X(4);
X(5);
X(6);
X(7);
X(8);
X(9);
X(10);
X(11);
X(12);
X(13);
X(14);
X(15);
X(16);
X(17);
X(18);
X(19);
X(20);
X(21);
X(22);
X(23);
X(24);
X(25);
X(26);
X(27);
X(28);
X(29);
X(30);
X(31);
X(32);
X(33);
X(34);
X(35);
X(36);
X(37);
X(38);
X(39);
X(40);
X(41);
X(42);
X(43);
X(44);
X(45);
X(46);
X(47);
X(48);
X(49);
X(50);
X(51);
X(52);
X(53);
X(54);
X(55);
X(56);
X(57);
X(58);
X(59);
X(60);
X(61);
X(62);
X(63);
X(64);
X(65);
X(66);
X(67);
X(68);
X(69);
X(70);
X(71);
X(72);
X(73);
X(74);
X(75);
X(76);
X(77);
X(78);

cobalt::core::ecs::World world;

// And so does this one!
#define BIND_KEYS(bindptr) \
    Y(world, 0, bindptr);  \
    Y(world, 1, bindptr);  \
    Y(world, 2, bindptr);  \
    Y(world, 3, bindptr);  \
    Y(world, 4, bindptr);  \
    Y(world, 5, bindptr);  \
    Y(world, 6, bindptr);  \
    Y(world, 7, bindptr);  \
    Y(world, 8, bindptr);  \
    Y(world, 9, bindptr);  \
    Y(world, 10, bindptr); \
    Y(world, 11, bindptr); \
    Y(world, 12, bindptr); \
    Y(world, 13, bindptr); \
    Y(world, 14, bindptr); \
    Y(world, 15, bindptr); \
    Y(world, 16, bindptr); \
    Y(world, 17, bindptr); \
    Y(world, 18, bindptr); \
    Y(world, 19, bindptr); \
    Y(world, 20, bindptr); \
    Y(world, 21, bindptr); \
    Y(world, 22, bindptr); \
    Y(world, 23, bindptr); \
    Y(world, 24, bindptr); \
    Y(world, 25, bindptr); \
    Y(world, 26, bindptr); \
    Y(world, 27, bindptr); \
    Y(world, 28, bindptr); \
    Y(world, 29, bindptr); \
    Y(world, 30, bindptr); \
    Y(world, 31, bindptr); \
    Y(world, 32, bindptr); \
    Y(world, 33, bindptr); \
    Y(world, 34, bindptr); \
    Y(world, 35, bindptr); \
    Y(world, 36, bindptr); \
    Y(world, 37, bindptr); \
    Y(world, 38, bindptr); \
    Y(world, 39, bindptr); \
    Y(world, 40, bindptr); \
    Y(world, 41, bindptr); \
    Y(world, 42, bindptr); \
    Y(world, 43, bindptr); \
    Y(world, 44, bindptr); \
    Y(world, 45, bindptr); \
    Y(world, 46, bindptr); \
    Y(world, 47, bindptr); \
    Y(world, 48, bindptr); \
    Y(world, 49, bindptr); \
    Y(world, 50, bindptr); \
    Y(world, 51, bindptr); \
    Y(world, 52, bindptr); \
    Y(world, 53, bindptr); \
    Y(world, 54, bindptr); \
    Y(world, 55, bindptr); \
    Y(world, 56, bindptr); \
    Y(world, 57, bindptr); \
    Y(world, 58, bindptr); \
    Y(world, 59, bindptr); \
    Y(world, 60, bindptr); \
    Y(world, 61, bindptr); \
    Y(world, 62, bindptr); \
    Y(world, 63, bindptr); \
    Y(world, 64, bindptr); \
    Y(world, 65, bindptr); \
    Y(world, 66, bindptr); \
    Y(world, 67, bindptr); \
    Y(world, 68, bindptr); \
    Y(world, 69, bindptr); \
    Y(world, 70, bindptr); \
    Y(world, 71, bindptr); \
    Y(world, 72, bindptr); \
    Y(world, 73, bindptr); \
    Y(world, 74, bindptr); \
    Y(world, 75, bindptr); \
    Y(world, 76, bindptr); \
    Y(world, 77, bindptr); \
    Y(world, 78, bindptr);
// Basically just bind every key to a command that sets the value of a TestClass to the key's id.

TestClass testClass;
cobalt::core::input::Keyboard* keyboard;

void setUp(void) {
    keyboard = new cobalt::core::input::Keyboard(1);
    BIND_KEYS(&testClass);
}

void tearDown(void) { delete keyboard; }

void testKeyboardSingleTaps() {
    eventCounter = 0;
    // Do this 5 times to make sure the state is consistent across frames.
    for (int repeats = 0; repeats < 5; repeats++) {
        for (int i = 0; i < KEY_MAX; i++) {
            // Tap key. Ensure that the key input is calling the correct command.
            keyboard->onKeyPress(static_cast<cobalt::core::input::KeyboardInputID>(i), GLFW_PRESS);
            keyboard->pollEvents();
            keyboard->clearEvents();
            testClass.assertValue(i);
            testClass.assertPressed();
            // Release key.
            keyboard->onKeyPress(static_cast<cobalt::core::input::KeyboardInputID>(i), GLFW_RELEASE);
            keyboard->pollEvents();
            keyboard->clearEvents();
            testClass.assertValue(i);
            testClass.assertReleased();
        }
    }
    // Make sure that the counter is correct.
    TEST_ASSERT_EQUAL_INT(KEY_MAX * 5 * 2, eventCounter);
}

void testKeyboardHold() {
    eventCounter = 0;
    // Hold every key.
    for (int i = 0; i < KEY_MAX; i++) {
        keyboard->onKeyPress(static_cast<cobalt::core::input::KeyboardInputID>(i), GLFW_PRESS);
    }
    keyboard->pollEvents();
    keyboard->clearEvents();
    TEST_ASSERT_EQUAL_INT(KEY_MAX, eventCounter);

    // Next frame, make sure that the keys are still down.
    keyboard->pollEvents();
    keyboard->clearEvents();
    TEST_ASSERT_EQUAL_INT(KEY_MAX * 2, eventCounter);
    // No extra events should be generated.
    keyboard->clearEvents();
    TEST_ASSERT_EQUAL_INT(KEY_MAX * 2, eventCounter);
    eventCounter = 0;

    // Double poll. Make sure that all the events are queued.
    keyboard->pollEvents();
    keyboard->pollEvents();
    keyboard->clearEvents();
    TEST_ASSERT_EQUAL_INT(KEY_MAX * 2, eventCounter);
    eventCounter = 0;

    // Release events should only be generated once.
    for (int i = 0; i < KEY_MAX; i++) {
        keyboard->onKeyPress(static_cast<cobalt::core::input::KeyboardInputID>(i), GLFW_RELEASE);
    }
    keyboard->pollEvents();
    keyboard->pollEvents();
    keyboard->pollEvents();
    keyboard->clearEvents();
    keyboard->clearEvents();
    TEST_ASSERT_EQUAL_INT(KEY_MAX, eventCounter);
}

void testKeyboardOutOfBounds() {
    bool exceptionThrown = false;
    eventCounter = 0;
    try {
        keyboard->onKeyPress(keyboard->glfwToCobalt(-1), GLFW_PRESS);
        keyboard->pollEvents();
        keyboard->clearEvents();
    } catch (const std::exception& e) {
        exceptionThrown = true;
    }
    TEST_ASSERT_TRUE_MESSAGE(exceptionThrown, "Expected exception for lower bound key press was not thrown.");

    exceptionThrown = false;
    eventCounter = 0;
    try {
        keyboard->onKeyPress(keyboard->glfwToCobalt(123456789), GLFW_PRESS);
        keyboard->pollEvents();
        keyboard->clearEvents();
    } catch (const std::exception& e) {
        exceptionThrown = true;
    }
    TEST_ASSERT_TRUE_MESSAGE(exceptionThrown, "Expected exception for upper bound key press was not thrown.");
    TEST_ASSERT_EQUAL_INT(0, eventCounter);
}
*/
int main(void) {
    UNITY_BEGIN();
    // RUN_TEST(testKeyboardSingleTaps);
    // RUN_TEST(testKeyboardHold);
    // RUN_TEST(testKeyboardOutOfBounds);
    return UNITY_END();
}