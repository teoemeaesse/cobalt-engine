//
// Created by tomas on 19-11-2023.
//

#include "unity.h"

#include "core/memory/pool.h"


void setUp(void) {
    // set stuff up here
}

void tearDown(void) {
    // clean stuff up here
}

void test_pool_create() {
    cobalt::PoolAllocator<int> pool(10);

    int *a = pool.grab();
    *a = 0;

    TEST_ASSERT_EQUAL_INT(0, *a);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_pool_create);
    return UNITY_END();
}