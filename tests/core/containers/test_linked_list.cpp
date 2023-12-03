//
// Created by tomas on 30-11-2023.
//

#include "unity/unity.h"

#include "core/containers/linked_list.h"


void setUp(void) {
    // set stuff up here
}

void tearDown(void) {
    // clean stuff up here
}

void test_ll_push() {
    cobalt::core::LinkedList<int> list;
    for (int i = 0; i < 100; i++) {
        list.push(i);
    }
    TEST_ASSERT_EQUAL(100, list.getSize());
}

struct TestStruct {
    int a;
    int b;
    int c;
};

void test_ll_emplace() {
    cobalt::core::LinkedList<TestStruct> list;
    for (int i = 0; i < 100; i++) {
        list.emplace(i, i + 1, i + 2);
    }
    TEST_ASSERT_EQUAL(100, list.getSize());
}

void test_ll_pop() {
    cobalt::core::LinkedList<int> list;
    for (int i = 0; i < 100; i++) {
        list.push(i);
    }
    for (int i = 0; i < 100; i++) {
        TEST_ASSERT_EQUAL(99 - i, list.pop());
    }
    TEST_ASSERT_EQUAL(0, list.getSize());
}

void test_ll_get() {
    cobalt::core::LinkedList<int> list;
    for (int i = 0; i < 100; i++) {
        list.push(i);
    }
    for (int i = 0; i < 100; i++) {
        TEST_ASSERT_EQUAL(i, list.get(i));
    }
}

void test_ll_remove() {
    cobalt::core::LinkedList<int> list;
    for (int i = 0; i < 100; i++) {
        list.push(i);
    }
    for (int i = 0; i < 100; i++) {
        list.remove(99 - i);
    }
    TEST_ASSERT_EQUAL(0, list.getSize());

    for (int i = 0; i < 100; i++) {
        list.push(i);
    }
    for (int i = 0; i < 100; i++) {
        list.remove(0);
    }
    TEST_ASSERT_EQUAL(0, list.getSize());

    for (int i = 0; i < 100; i++) {
        list.push(i);
    }
    for (int i = 0; i < 50; i++) {
        list.remove(0);
    }
    TEST_ASSERT_EQUAL(50, list.getSize());
    for (int i = 0; i < 50; i++) {
        TEST_ASSERT_EQUAL(50 + i, list.get(i));
    }
}

void test_ll_insert_after() {
    cobalt::core::LinkedList<int> list;
    for (int i = 0; i < 100; i++) {
        list.push(i);
    }
    list.insertAfter(50, 100);
    TEST_ASSERT_EQUAL(101, list.getSize());
    TEST_ASSERT_EQUAL(100, list.get(51));
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_ll_push);
    RUN_TEST(test_ll_emplace);
    RUN_TEST(test_ll_pop);
    RUN_TEST(test_ll_get);
    RUN_TEST(test_ll_remove);
    RUN_TEST(test_ll_insert_after);
    return UNITY_END();
}