//
// Created by tomas on 19-11-2023.
//

#include "unity/unity.h"

#include "core/memory/pool.h"


void setUp(void) {
    // set stuff up here
}

void tearDown(void) {
    // clean stuff up here
}

void test_pool_grab() {
    cobalt::PoolAllocator<int> pool(10 * sizeof(int));
    int *ptr[10];
    for (int i = 0; i < 10; i++) {
        ptr[i] = pool.grab();
        *ptr[i] = i;
    }
    TEST_ASSERT_EQUAL_INT(10 * sizeof(int), pool.size());
    for (int i = 0; i < 10; i++) {
        TEST_ASSERT_EQUAL_INT(i, *ptr[i]);
    }
}

void test_pool_drop() {
    cobalt::PoolAllocator<int> pool(10 * sizeof(int));
    int *ptr[10];
    for (int i = 0; i < 10; i++) {
        ptr[i] = pool.grab();
        *ptr[i] = i;
    }
    TEST_ASSERT_EQUAL_INT(10 * sizeof(int), pool.size());
    for (int i = 0; i < 10; i++) {
        TEST_ASSERT_EQUAL_INT(i, *ptr[i]);
    }
    for (int i = 0; i < 10; i++) {
        pool.drop(ptr[i]);
    }
    TEST_ASSERT_EQUAL_INT(0 * sizeof(int), pool.size());
}

void test_pool_expand() {
    cobalt::PoolAllocator<int> pool(10 * sizeof(int));
    int *ptr[1000];
    for (int i = 0; i < 1000; i++) {
        ptr[i] = pool.grab();
        *ptr[i] = i;
    }
    TEST_ASSERT_EQUAL_INT(1000 * sizeof(int), pool.size());
    for (int i = 0; i < 1000; i++) {
        TEST_ASSERT_EQUAL_INT(i, *ptr[i]);
    }
    for (int i = 0; i < 1000; i++) {
        pool.drop(ptr[i]);
    }
    TEST_ASSERT_EQUAL_INT(0 * sizeof(int), pool.size());
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_pool_grab);
    RUN_TEST(test_pool_drop);
    RUN_TEST(test_pool_expand);
    return UNITY_END();
}