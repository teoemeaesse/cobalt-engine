//
// Created by tomas on 19-11-2023.
//

#include "unity/unity.h"

#include "core/containers/stack.h"


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

struct TestStruct {
    int a;
    int b;
    int c;
};

void test_stack_emplace() {
    cobalt::core::Stack<int> stack(1);
    for (int i = 0; i < 1000; i++) {
        stack.emplace(i);
    }
    TEST_ASSERT_EQUAL_INT(1000, stack.getSize());

    cobalt::core::Stack<TestStruct> stack2(1);
    for (int i = 0; i < 1000; i++) {
        stack2.emplace(i, i + 1, i + 2);
    }
    TEST_ASSERT_EQUAL_INT(1000, stack2.getSize());
}

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

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_stack_push);
    RUN_TEST(test_stack_emplace);
    RUN_TEST(test_stack_pop);
    RUN_TEST(test_stack_peek);
    //RUN_TEST(test_stack_stress);
    return UNITY_END();
}