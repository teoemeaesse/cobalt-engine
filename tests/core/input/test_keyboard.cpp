//
// Created by tomas on 26-12-2023.
//

#include "unity/unity.h"

#include "core/input/keyboard.h"


int eventCounter = 0;
const int KEY_MAX = static_cast<int>(cobalt::core::KeyboardInputID::COUNT);

class TestClass {
    public:
    TestClass() : value(0) {}
    void setValue(int value, bool pressed) {
        this->value = value;
        this->pressed = pressed;
    }
    void assertValue(cobalt::core::KeyboardInputID value) {
        TEST_ASSERT_EQUAL_INT(static_cast<int>(value), this->value);
    }
    void assertValue(int value) {
        TEST_ASSERT_EQUAL_INT(value, this->value);
    }
    void assertPressed() {
        TEST_ASSERT_EQUAL_INT(true, this->pressed);
    }
    void assertReleased() {
        TEST_ASSERT_EQUAL_INT(false, this->pressed);
    }
    int value;
    bool pressed;
};
#define DEFINE_PERIPHERAL_CMD(num) \
    class TestPeripheralCmd##num : public cobalt::core::ConcreteInputCommand<TestClass> { \
        public: \
        TestPeripheralCmd##num(TestClass* test) : cobalt::core::ConcreteInputCommand<TestClass>(test) {} \
        void execute() const override {getTarget()->setValue(num, getInput().active); eventCounter++;} \
    };
#define BIND_KEY(num, bindptr) keyboard->bind(static_cast<cobalt::core::KeyboardInputID>(num), std::make_unique<TestPeripheralCmd##num>(bindptr));
#define X(num) DEFINE_PERIPHERAL_CMD(num)
#define Y(num, bindptr) BIND_KEY(num, bindptr)
// Goes up to 78. Sue me.
X(0); X(1); X(2); X(3); X(4); X(5); X(6); X(7); X(8); X(9); X(10); X(11); X(12); X(13); X(14); X(15); X(16); X(17); X(18); X(19); X(20); X(21); X(22); X(23); X(24); X(25); X(26); X(27); X(28); X(29); X(30); X(31); X(32); X(33); X(34); X(35); X(36); X(37); X(38); X(39); X(40); X(41); X(42); X(43); X(44); X(45); X(46); X(47); X(48); X(49); X(50); X(51); X(52); X(53); X(54); X(55); X(56); X(57); X(58); X(59); X(60); X(61); X(62); X(63); X(64); X(65); X(66); X(67); X(68); X(69); X(70); X(71); X(72); X(73); X(74); X(75); X(76); X(77); X(78);
// And so does this one!
#define BIND_KEYS(bindptr) Y(0, bindptr); Y(1, bindptr); Y(2, bindptr); Y(3, bindptr); Y(4, bindptr); Y(5, bindptr); Y(6, bindptr); Y(7, bindptr); Y(8, bindptr); Y(9, bindptr); Y(10, bindptr); Y(11, bindptr); Y(12, bindptr); Y(13, bindptr); Y(14, bindptr); Y(15, bindptr); Y(16, bindptr); Y(17, bindptr); Y(18, bindptr); Y(19, bindptr); Y(20, bindptr); Y(21, bindptr); Y(22, bindptr); Y(23, bindptr); Y(24, bindptr); Y(25, bindptr); Y(26, bindptr); Y(27, bindptr); Y(28, bindptr); Y(29, bindptr); Y(30, bindptr); Y(31, bindptr); Y(32, bindptr); Y(33, bindptr); Y(34, bindptr); Y(35, bindptr); Y(36, bindptr); Y(37, bindptr); Y(38, bindptr); Y(39, bindptr); Y(40, bindptr); Y(41, bindptr); Y(42, bindptr); Y(43, bindptr); Y(44, bindptr); Y(45, bindptr); Y(46, bindptr); Y(47, bindptr); Y(48, bindptr); Y(49, bindptr); Y(50, bindptr); Y(51, bindptr); Y(52, bindptr); Y(53, bindptr); Y(54, bindptr); Y(55, bindptr); Y(56, bindptr); Y(57, bindptr); Y(58, bindptr); Y(59, bindptr); Y(60, bindptr); Y(61, bindptr); Y(62, bindptr); Y(63, bindptr); Y(64, bindptr); Y(65, bindptr); Y(66, bindptr); Y(67, bindptr); Y(68, bindptr); Y(69, bindptr); Y(70, bindptr); Y(71, bindptr); Y(72, bindptr); Y(73, bindptr); Y(74, bindptr); Y(75, bindptr); Y(76, bindptr); Y(77, bindptr); Y(78, bindptr);
// Basically just bind every key to a command that sets
// the value of a TestClass to the key's id.


TestClass testClass;
cobalt::core::Keyboard *keyboard;


void setUp(void) {
    cobalt::core::KeyCodes::init();
    keyboard = new cobalt::core::Keyboard();
    BIND_KEYS(&testClass);
}

void tearDown(void) {
    delete keyboard;
}

void testKeyboardSingleTaps() {
    eventCounter = 0;
    // Do this 5 times to make sure the state is consistent across frames.
    for (int repeats = 0; repeats < 5; repeats++) {
        for (int i = 0; i < KEY_MAX; i++) {
            // Tap key. Ensure that the key input is calling the correct command.
            keyboard->onKeyPress(keyboard->cobaltToGlfw(static_cast<cobalt::core::KeyboardInputID>(i)), GLFW_PRESS);
            keyboard->pollEvents();
            keyboard->clearEvents();
            testClass.assertValue(i);
            testClass.assertPressed();
            // Release key.
            keyboard->onKeyPress(keyboard->cobaltToGlfw(static_cast<cobalt::core::KeyboardInputID>(i)), GLFW_RELEASE);
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
        keyboard->onKeyPress(keyboard->cobaltToGlfw(static_cast<cobalt::core::KeyboardInputID>(i)), GLFW_PRESS);
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
    keyboard->pollEvents(); keyboard->pollEvents();
    keyboard->clearEvents();
    TEST_ASSERT_EQUAL_INT(KEY_MAX * 2, eventCounter);
    eventCounter = 0;

    // Release events should only be generated once.
    for (int i = 0; i < KEY_MAX; i++) {
        keyboard->onKeyPress(keyboard->cobaltToGlfw(static_cast<cobalt::core::KeyboardInputID>(i)), GLFW_RELEASE);
    }
    keyboard->pollEvents(); keyboard->pollEvents(); keyboard->pollEvents();
    keyboard->clearEvents(); keyboard->clearEvents();
    TEST_ASSERT_EQUAL_INT(KEY_MAX, eventCounter);
}

void testKeyboardOutOfBounds() {
    bool exceptionThrown = false;
    eventCounter = 0;
    try {
        keyboard->onKeyPress(-1, GLFW_PRESS);
        keyboard->pollEvents();
        keyboard->clearEvents();
    } catch (const std::exception& e) {
        exceptionThrown = true;
    }
    TEST_ASSERT_TRUE_MESSAGE(exceptionThrown, "Expected exception for lower bound key press was not thrown.");

    exceptionThrown = false;
    eventCounter = 0;
    try {
        keyboard->onKeyPress(123456789, GLFW_PRESS);
        keyboard->pollEvents();
        keyboard->clearEvents();
    } catch (const std::exception& e) {
        exceptionThrown = true;
    }
    TEST_ASSERT_TRUE_MESSAGE(exceptionThrown, "Expected exception for upper bound key press was not thrown.");
    TEST_ASSERT_EQUAL_INT(0, eventCounter);
}



int main(void) {
    UNITY_BEGIN();
    RUN_TEST(testKeyboardSingleTaps);
    RUN_TEST(testKeyboardHold);
    RUN_TEST(testKeyboardOutOfBounds);
    return UNITY_END();
}