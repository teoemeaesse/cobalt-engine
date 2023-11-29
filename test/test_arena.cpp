//
// Created by tomas on 19-11-2023.
//

#include "unity.h"

#include <iostream>
#include "core/memory/arena.h"


void setUp(void) {
    // set stuff up here
}

void tearDown(void) {
    // clean stuff up here
}

void test_arena_grab() {
    cobalt::ArenaAllocator arena(10 * sizeof(int));
    int *ptr[10];
    for (int i = 0; i < 10; i++) {
        ptr[i] = (int *) arena.grab(sizeof(int));
        *ptr[i] = i;
    }
    TEST_ASSERT_EQUAL_INT(10 * sizeof(int), arena.size());
    for (int i = 0; i < 10; i++) {
        TEST_ASSERT_EQUAL_INT(i, *ptr[i]);
    }
}

void test_arena_resize() {
    cobalt::ArenaAllocator arena(10 * sizeof(int));
    int *ptr[10];
    for (int i = 0; i < 10; i++) {
        ptr[i] = (int *) arena.grab(sizeof(int));
        *ptr[i] = i;
    }
    TEST_ASSERT_EQUAL_INT(10 * sizeof(int), arena.size());
    for (int i = 0; i < 10; i++) {
        TEST_ASSERT_EQUAL_INT(i, *ptr[i]);
    }
    for (int i = 0; i < 10; i++) {
        ptr[i] = (int *) arena.resize(ptr[i], sizeof(int) * 2);
        *ptr[i] = i;
    }
    TEST_ASSERT_EQUAL_INT(30 * sizeof(int), arena.size());
    for (int i = 0; i < 10; i++) {
        TEST_ASSERT_EQUAL_INT(i, *ptr[i]);
    }
}

void test_arena_expand() {
    cobalt::ArenaAllocator arena(1);
    int *ptr[10];
    for (int i = 0; i < 10; i++) {
        ptr[i] = (int *) arena.grab(sizeof(int));
        *ptr[i] = i;
    }
    TEST_ASSERT_EQUAL_INT(10 * sizeof(int), arena.size());
    for (int i = 0; i < 10; i++) {
        TEST_ASSERT_EQUAL_INT(i, *ptr[i]);
    }
    for (int i = 0; i < 10; i++) {
        ptr[i] = (int *) arena.resize(ptr[i], sizeof(int) * 2);
        *ptr[i] = i;
    }
    TEST_ASSERT_EQUAL_INT(30 * sizeof(int), arena.size());
    for (int i = 0; i < 10; i++) {
        TEST_ASSERT_EQUAL_INT(i, *ptr[i]);
    }
    for (int i = 0; i < 10; i++) {
        ptr[i] = (int *) arena.grab(sizeof(int));
        *ptr[i] = i;
    }
    TEST_ASSERT_EQUAL_INT(40 * sizeof(int), arena.size());
    for (int i = 0; i < 10; i++) {
        TEST_ASSERT_EQUAL_INT(i, *ptr[i]);
    }

}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_arena_grab);
    RUN_TEST(test_arena_resize);
    RUN_TEST(test_arena_expand);
    return UNITY_END();
}