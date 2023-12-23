//
// Created by tomas on 19-11-2023.
//

#include "unity/unity.h"

#include "core/containers/stack.h"


class TestClass {
    public:
    static int constructorCount;
    static int destructorCount;
    static int copyConstructorCount;
    static int moveConstructorCount;
    static int copyAssignmentCount;
    static int moveAssignmentCount;

    int value;
    bool ownsValue;

    TestClass(int val = 0) : value(val), ownsValue(true) { constructorCount++; }
    ~TestClass() { if (ownsValue) destructorCount++; }

    TestClass(const TestClass& other) : value(other.value), ownsValue(true) { copyConstructorCount++; }
    TestClass(TestClass&& other) noexcept : value(other.value) { other.value = 0; other.ownsValue = false; moveConstructorCount++; }

    TestClass& operator=(const TestClass& other) {
        if (this != &other) {
            value = other.value;
            copyAssignmentCount++;
        }
        return *this;
    }

    TestClass& operator=(TestClass&& other) noexcept {
        if (this != &other) {
            value = other.value;
            other.value = 0;
            other.ownsValue = false;
            moveAssignmentCount++;
        }
        return *this;
    }

    static void resetCounts() {
        constructorCount = destructorCount = copyConstructorCount = moveConstructorCount = copyAssignmentCount = moveAssignmentCount = 0;
    }
};

int TestClass::constructorCount = 0;
int TestClass::destructorCount = 0;
int TestClass::copyConstructorCount = 0;
int TestClass::moveConstructorCount = 0;
int TestClass::copyAssignmentCount = 0;
int TestClass::moveAssignmentCount = 0;

void setUp(void) {
    // set stuff up here
}

void tearDown(void) {
    // clean stuff up here
}

void test_stack_push() {
    cobalt::core::Stack<int> stack(7);
    for (int i = 0; i < 1000; i++) {
        stack.push(i);
    }
    TEST_ASSERT_EQUAL_INT(1000, stack.getSize());
}

class TestStruct {
    public:
    TestStruct(int a, int b, int c) : a(a), b(b), c(c) {}
    ~TestStruct() {}
    int a;
    int b;
    int c;
};

void test_stack_pop() {
    cobalt::core::Stack<int> stack(8);
    for (int i = 0; i < 500; i++) {
        stack.push(i);
    }
    TEST_ASSERT_EQUAL_INT(500, stack.getSize());
    for (int i = 500; i < 1000; i++) {
        stack.emplace(i);
    }
    for (int i = 0; i < 1000; i++) {
        int j = stack.pop();
        TEST_ASSERT_EQUAL_INT(1000 - i - 1, j);
    }
    TEST_ASSERT_EQUAL_INT(0, stack.getSize());

    cobalt::core::Stack<TestStruct> stack2(8);
    for (int i = 0; i < 1000; i++) {
        stack2.emplace(i, i + 1, i + 2);
    }
    TEST_ASSERT_EQUAL_INT(1000, stack2.getSize());
    for (int i = 0; i < 1000; i++) {
        TestStruct j = stack2.pop();
        TEST_ASSERT_EQUAL_INT(1000 - i - 1, j.a);
        TEST_ASSERT_EQUAL_INT(1000 - i, j.b);
        TEST_ASSERT_EQUAL_INT(1000 - i + 1, j.c);
    }
}

void test_stack_pop_empty() {
    cobalt::core::Stack<int> stack;
    bool exceptionThrown = false;
    try {
        stack.pop();
    } catch (const cobalt::core::ContainerException& e) {
        exceptionThrown = true;
    }
    TEST_ASSERT_TRUE(exceptionThrown);
}

void test_stack_peek() {
    cobalt::core::Stack<int> stack(8);
    for (int i = 0; i < 1000; i++) {
        stack.push(i);
    }
    TEST_ASSERT_EQUAL_INT(1000, stack.getSize());
    for (int i = 0; i < 1000; i++) {
        int j = stack.peek();
        TEST_ASSERT_EQUAL_INT(1000 - i - 1, j);
        stack.pop();
    }
    TEST_ASSERT_EQUAL_INT(0, stack.getSize());
}

void test_stack_stress() {
    cobalt::core::Stack<int> stack(8);
    for (int i = 0; i < 10000000; i++) {
        stack.push(i);
    }
    TEST_ASSERT_EQUAL_INT(10000000, stack.getSize());
    for (int i = 0; i < 10000000; i++) {
        int j = stack.pop();
        TEST_ASSERT_EQUAL_INT(10000000 - i - 1, j);
    }
    TEST_ASSERT_EQUAL_INT(0, stack.getSize());
}

void test_stack_copy_constructor() {
    cobalt::core::Stack<int> originalStack;
    for (int i = 0; i < 10; i++) {
        originalStack.push(i);
    }
    cobalt::core::Stack<int> copiedStack(originalStack);
    TEST_ASSERT_EQUAL_INT(originalStack.getSize(), copiedStack.getSize());
    for (int i = 9; i >= 0; i--) {
        TEST_ASSERT_EQUAL_INT(i, copiedStack.pop());
    }
}

void test_stack_move_constructor() {
    cobalt::core::Stack<int> originalStack;
    for (int i = 0; i < 10; i++) {
        originalStack.push(i);
    }
    cobalt::core::Stack<int> movedStack(std::move(originalStack));
    TEST_ASSERT_EQUAL_INT(0, originalStack.getSize());
    TEST_ASSERT_EQUAL_INT(10, movedStack.getSize());
}

void test_stack_copy_assignment() {
    cobalt::core::Stack<int> originalStack;
    for (int i = 0; i < 10; i++) {
        originalStack.push(i);
    }
    cobalt::core::Stack<int> copiedStack;
    copiedStack = originalStack;
    TEST_ASSERT_EQUAL_INT(originalStack.getSize(), copiedStack.getSize());
    for (int i = 9; i >= 0; i--) {
        TEST_ASSERT_EQUAL_INT(i, copiedStack.pop());
    }
}

void test_stack_move_assignment() {
    cobalt::core::Stack<int> originalStack;
    for (int i = 0; i < 10; i++) {
        originalStack.push(i);
    }
    cobalt::core::Stack<int> movedStack;
    movedStack = std::move(originalStack);
    TEST_ASSERT_EQUAL_INT(0, originalStack.getSize());
    TEST_ASSERT_EQUAL_INT(10, movedStack.getSize());
}

void test_stack_boundary_conditions() {
    cobalt::core::Stack<int> stack(1); // very small initial capacity to force resize
    stack.push(1);
    stack.push(2);
    TEST_ASSERT_EQUAL_INT(2, stack.getSize());
    TEST_ASSERT_EQUAL_INT(2, stack.pop());
    TEST_ASSERT_EQUAL_INT(1, stack.pop());
}

void test_stack_push_move_semantics() {
    TestClass::resetCounts();
    cobalt::core::Stack<TestClass> stack;
    for (int i = 0; i < 10; i++) {
        TestClass obj(i);
        stack.push(std::move(obj));
        // Verify that obj is in a moved-from state (specific to your implementation)
        TEST_ASSERT_EQUAL_INT(0, obj.value);  // or another appropriate check
    }
    TEST_ASSERT_EQUAL_INT(10, TestClass::constructorCount);
    TEST_ASSERT_EQUAL_INT(10, TestClass::moveConstructorCount);
    TEST_ASSERT_EQUAL_INT(0, TestClass::copyConstructorCount);
    TEST_ASSERT_EQUAL_INT(0, TestClass::destructorCount);
    TEST_ASSERT_EQUAL_INT(10, stack.getSize());
    for (int i = 9; i >= 0; i--) {
        TestClass popped = stack.pop();
        TEST_ASSERT_EQUAL_INT(i, popped.value);
    }
    TEST_ASSERT_EQUAL_INT(10, TestClass::destructorCount);
}

void test_stack_push_copy_and_move_semantics() {
    TestClass::resetCounts();
    cobalt::core::Stack<TestClass> stack;
    for (int i = 0; i < 10; i++) {
        if (i % 2 == 0) {
            TestClass obj(i);
            stack.push(obj);  // Copy
        } else {
            TestClass obj(i);
            stack.push(std::move(obj));  // Move
        }
    }
    TEST_ASSERT_EQUAL_INT(10, TestClass::constructorCount);
    TEST_ASSERT_EQUAL_INT(5, TestClass::copyConstructorCount);
    TEST_ASSERT_EQUAL_INT(5, TestClass::moveConstructorCount);
    TEST_ASSERT_EQUAL_INT(5, TestClass::destructorCount);
    TEST_ASSERT_EQUAL_INT(10, stack.getSize());
    for (int i = 9; i >= 0; i--) {
        TestClass popped = stack.pop();
        TEST_ASSERT_EQUAL_INT(i, popped.value);
    }
    TEST_ASSERT_EQUAL_INT(15, TestClass::destructorCount);
}

void test_stack_emplace() {
    TestClass::resetCounts();
    cobalt::core::Stack<TestClass> stack;

    for (int i = 0; i < 10; i++) {
        stack.emplace(i);
    }

    TEST_ASSERT_EQUAL_INT(10, TestClass::constructorCount);
    TEST_ASSERT_EQUAL_INT(0, TestClass::copyConstructorCount);
    TEST_ASSERT_EQUAL_INT(0, TestClass::moveConstructorCount);
    TEST_ASSERT_EQUAL_INT(0, TestClass::destructorCount);
    TEST_ASSERT_EQUAL_INT(10, stack.getSize());

    for (int i = 9; i >= 0; i--) {
        TestClass popped = stack.pop();
        TEST_ASSERT_EQUAL_INT(i, popped.value);
    }
}

void test_stack_self_assignment() {
    TestClass::resetCounts();
    // Setup a stack with TestClass instances
    cobalt::core::Stack<TestClass> stack;
    for (int i = 0; i < 5; i++) {
        stack.push(TestClass(i));
    }
    // Test Self-Copy Assignment
    stack = stack;
    TEST_ASSERT_EQUAL_INT(5, stack.getSize());
    TEST_ASSERT_EQUAL_INT(0, TestClass::copyAssignmentCount); // Self-assignment should not invoke copy assignment
    for (int i = 4; i >= 0; i--) {
        TEST_ASSERT_EQUAL_INT(i, stack.pop().value);
    }
    // Refill the stack for the next test
    for (int i = 0; i < 5; i++) {
        stack.push(TestClass(i));
    }
    TestClass::resetCounts();
    // Test Self-Move Assignment
    stack = std::move(stack);
    TEST_ASSERT_EQUAL_INT(5, stack.getSize());
    TEST_ASSERT_EQUAL_INT(0, TestClass::moveAssignmentCount); // Self-assignment should not invoke move assignment
    TEST_ASSERT_EQUAL_INT(0, TestClass::destructorCount); // Self-assignment should not invoke destructor
    TEST_ASSERT_EQUAL_INT(0, TestClass::constructorCount); // Self-assignment should not invoke constructor
    TEST_ASSERT_EQUAL_INT(0, TestClass::copyConstructorCount); // Self-assignment should not invoke copy constructor
    TEST_ASSERT_EQUAL_INT(0, TestClass::moveConstructorCount); // Self-assignment should not invoke move constructor
    for (int i = 4; i >= 0; i--) {
        TEST_ASSERT_EQUAL_INT(i, stack.pop().value);
    }
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_stack_push);
    RUN_TEST(test_stack_emplace);
    RUN_TEST(test_stack_pop);
    RUN_TEST(test_stack_peek);
    //RUN_TEST(test_stack_stress);
    RUN_TEST(test_stack_pop_empty);
    RUN_TEST(test_stack_copy_constructor);
    RUN_TEST(test_stack_move_constructor);
    RUN_TEST(test_stack_copy_assignment);
    RUN_TEST(test_stack_move_assignment);
    RUN_TEST(test_stack_boundary_conditions);
    RUN_TEST(test_stack_push_move_semantics);
    RUN_TEST(test_stack_push_copy_and_move_semantics);
    RUN_TEST(test_stack_self_assignment);
    return UNITY_END();
}