/**
 * @file test_pool.h
 * @brief Test the memory pool implementation.
 * @author Tomás Marques
 * @date 19-11-2023
 */

#include "core/memory/pool.h"
#include "unity/unity.h"

void setUp(void) {}

void tearDown(void) {}

void test_pool_grab() {
    cobalt::core::memory::PoolAllocator<int> pool(10 * sizeof(int));
    int* ptr[10];
    for (int i = 0; i < 10; i++) {
        ptr[i] = pool.grab();
        *ptr[i] = i;
    }
    TEST_ASSERT_EQUAL_INT(10 * sizeof(int), pool.getSize());
    for (int i = 0; i < 10; i++) {
        TEST_ASSERT_EQUAL_INT(i, *ptr[i]);
    }
}

void test_pool_drop() {
    cobalt::core::memory::PoolAllocator<int> pool(10 * sizeof(int));
    int* ptr[10];
    for (int i = 0; i < 10; i++) {
        ptr[i] = pool.grab();
        *ptr[i] = i;
    }
    TEST_ASSERT_EQUAL_INT(10 * sizeof(int), pool.getSize());
    for (int i = 0; i < 10; i++) {
        TEST_ASSERT_EQUAL_INT(i, *ptr[i]);
    }
    for (int i = 0; i < 10; i++) {
        pool.drop(ptr[i]);
    }
    TEST_ASSERT_EQUAL_INT(0 * sizeof(int), pool.getSize());
}

void test_pool_expand() {
    cobalt::core::memory::PoolAllocator<int> pool(10 * sizeof(int));
    int* ptr[1000];
    for (int i = 0; i < 1000; i++) {
        ptr[i] = pool.grab();
        *ptr[i] = i;
    }
    TEST_ASSERT_EQUAL_INT(1000 * sizeof(int), pool.getSize());
    for (int i = 0; i < 1000; i++) {
        TEST_ASSERT_EQUAL_INT(i, *ptr[i]);
    }
    for (int i = 0; i < 1000; i++) {
        pool.drop(ptr[i]);
    }
    TEST_ASSERT_EQUAL_INT(0 * sizeof(int), pool.getSize());
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_pool_grab);
    RUN_TEST(test_pool_drop);
    RUN_TEST(test_pool_expand);
    return UNITY_END();
}