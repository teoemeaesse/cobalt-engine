//
// Created by tomas on 06-12-2023.
//

#include "unity/unity.h"

#include "core/containers/vector.h"


void setUp(void) {
    // set stuff up here
}

void tearDown(void) {
    // clean stuff up here
}

void test_vector_push() {
    cobalt::core::Vector<int> vector(1);
    vector.push(1);
    TEST_ASSERT_EQUAL(1, vector[0]);
}

void test_vector_resize() {
    cobalt::core::Vector<int> vector(1);
    for (int i = 0; i < 100; i++) {
        vector.push(i);
    }
    TEST_ASSERT_EQUAL(100, vector.getSize());
}

void test_vector_remove() {
    cobalt::core::Vector<int> vector(1);
    for (int i = 0; i < 100; i++) {
        vector.push(i);
    }
    vector.remove(50);
    TEST_ASSERT_EQUAL(99, vector.getSize());
    TEST_ASSERT_EQUAL(51, vector[50]);
}

void test_vector_remove_exception() {
    cobalt::core::Vector<int> vector(1);
    for (int i = 0; i < 100; i++) {
        vector.push(i);
    }
    try {
        vector.remove(101);
    } catch (cobalt::core::ContainerException& e) {
        TEST_ASSERT_EQUAL_STRING("Index out of bounds", e.what());
    }
    try {
        vector.remove(-1);
    } catch (cobalt::core::ContainerException& e) {
        TEST_ASSERT_EQUAL_STRING("Index out of bounds", e.what());
    }
    for (int i = 0; i < 100; i++) {
        vector.remove(0);
    }
    try {
        vector.remove(0);
    } catch (cobalt::core::ContainerException& e) {
        TEST_ASSERT_EQUAL_STRING("Index out of bounds", e.what());
    }
}

void test_vector_remove_push() {
    cobalt::core::Vector<int> vector(1);
    for (int i = 0; i < 100; i++) {
        vector.push(i);
    }
    for (int i = 0; i < 100; i++) {
        vector.remove(0);
    }
    TEST_ASSERT_EQUAL(0, vector.getSize());
    for (int i = 100; i < 200; i++) {
        vector.push(i);
    }
    TEST_ASSERT_EQUAL(100, vector.getSize());
    for (int i = 0; i < 100; i++) {
        TEST_ASSERT_EQUAL(i + 100, vector[i]);
    }
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_vector_push);
    RUN_TEST(test_vector_resize);
    RUN_TEST(test_vector_remove);
    RUN_TEST(test_vector_remove_exception);
    RUN_TEST(test_vector_remove_push);
    return UNITY_END();
}