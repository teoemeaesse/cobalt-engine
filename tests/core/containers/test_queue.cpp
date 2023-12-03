//
// Created by tomas on 03-12-2023.
//

#include "unity/unity.h"

#include "core/containers/queue.h"


void setUp(void) {
    // set stuff up here
}

void tearDown(void) {
    // clean stuff up here
}

void test_queue_enqueue() {
    cobalt::core::Queue<int> queue;
    queue.enqueue(1);
    queue.enqueue(2);
    queue.enqueue(3);
    TEST_ASSERT_EQUAL_INT(1, queue.dequeue());
    TEST_ASSERT_EQUAL_INT(2, queue.dequeue());
    queue.enqueue(4);
    TEST_ASSERT_EQUAL_INT(3, queue.dequeue());
    TEST_ASSERT_EQUAL_INT(4, queue.dequeue());
}

void test_queue_dequeue() {
    cobalt::core::Queue<int> queue;
    queue.enqueue(1);
    queue.enqueue(2);
    queue.enqueue(3);
    TEST_ASSERT_EQUAL_INT(1, queue.dequeue());
    TEST_ASSERT_EQUAL_INT(2, queue.dequeue());
    TEST_ASSERT_EQUAL_INT(3, queue.dequeue());
    TEST_ASSERT_EQUAL_INT(0, queue.getSize());
    try {
        queue.dequeue();
        TEST_FAIL_MESSAGE("Expected exception");
    } catch (cobalt::core::ContainerException& e) {
        TEST_ASSERT_EQUAL_STRING("Queue is empty", e.what());
    }
}

void test_queue_stress() {
    cobalt::core::Queue<int> queue;
    for (int i = 0; i < 1000000; i++) {
        queue.enqueue(i);
    }
    for (int i = 0; i < 1000000; i++) {
        TEST_ASSERT_EQUAL_INT(i, queue.dequeue());
    }
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_queue_enqueue);
    RUN_TEST(test_queue_dequeue);
    RUN_TEST(test_queue_stress);
    return UNITY_END();
}