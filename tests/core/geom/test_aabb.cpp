/**
 * @file test_aabb.h
 * @brief Test the AABB implementation.
 * @author Tomás Marques
 * @date 12-09-2024
 */

#include "core/geom/aabb.h"
#include "unity/unity.h"

using namespace cobalt::core::geom;
using namespace cobalt;

void setUp() {}

void tearDown() {}

void test_intersects() {
    // Partial intersection
    AABB aabb1 = AABB({0, 0, 0}, {1, 1, 1});
    AABB aabb2 = AABB({0.5, 0.5, 0.5}, {1.5, 1.5, 1.5});
    TEST_ASSERT_TRUE(aabb1.intersects(aabb2));

    // Full intersection
    AABB aabb3 = AABB({0, 0, 0}, {1, 1, 1});
    TEST_ASSERT_TRUE(aabb1.intersects(aabb3));

    // Touching points intersection
    AABB aabb4 = AABB({1, 1, 1}, {2, 2, 2});
    TEST_ASSERT_TRUE(aabb1.intersects(aabb4));

    // No intersection
    AABB aabb5 = AABB({1.1, 1.1, 1.1}, {2.1, 2.1, 2.1});
    TEST_ASSERT_FALSE(aabb1.intersects(aabb5));

    // Empty boxes should not intersect anything
    AABB empty1 = AABB();
    AABB empty2 = AABB();
    TEST_ASSERT_FALSE(empty1.intersects(empty2));
    TEST_ASSERT_FALSE(empty1.intersects(aabb1));
    TEST_ASSERT_FALSE(aabb1.intersects(empty1));
}

void test_contains() {
    // Check all edge cases for a unit cube
    AABB aabb1 = AABB({0, 0, 0}, {1, 1, 1});
    TEST_ASSERT_TRUE(aabb1.contains({0.5, 0.5, 0.5}));
    TEST_ASSERT_TRUE(aabb1.contains({0, 0, 0}));
    TEST_ASSERT_TRUE(aabb1.contains({0, 0, 1}));
    TEST_ASSERT_TRUE(aabb1.contains({0, 1, 1}));
    TEST_ASSERT_FALSE(aabb1.contains({-1, -1, -1}));
    TEST_ASSERT_FALSE(aabb1.contains({1, 1, 1.1}));
}

#define TEST_BOX_VALUES(aabb, minx, miny, minz, maxx, maxy, maxz) \
    TEST_ASSERT_EQUAL_FLOAT(minx, aabb.getMin().x);               \
    TEST_ASSERT_EQUAL_FLOAT(miny, aabb.getMin().y);               \
    TEST_ASSERT_EQUAL_FLOAT(minz, aabb.getMin().z);               \
    TEST_ASSERT_EQUAL_FLOAT(maxx, aabb.getMax().x);               \
    TEST_ASSERT_EQUAL_FLOAT(maxy, aabb.getMax().y);               \
    TEST_ASSERT_EQUAL_FLOAT(maxz, aabb.getMax().z);

void test_expand() {
    // Check expanding with a box that is not contained
    AABB aabb1 = AABB({0, 0, 0}, {1, 1, 1});
    AABB aabb2 = AABB({1, 1, 1}, {2, 2, 2});
    aabb1.expand(aabb2);
    TEST_BOX_VALUES(aabb1, 0, 0, 0, 2, 2, 2);

    // Check expanding with a box that is contained
    AABB aabb3 = AABB({0.5, 0.5, 0.5}, {1.5, 1.5, 1.5});
    aabb1.expand(aabb3);
    TEST_BOX_VALUES(aabb1, 0, 0, 0, 2, 2, 2);

    // Check expanding with a null box
    AABB aabb4 = AABB();
    aabb1.expand(aabb4);
    TEST_BOX_VALUES(aabb1, 0, 0, 0, 2, 2, 2);
    aabb4.expand(aabb1);
    TEST_BOX_VALUES(aabb4, 0, 0, 0, 2, 2, 2);
}

void test_combine() {
    // Check combining with a box that is not contained
    AABB aabb1 = AABB({0, 0, 0}, {1, 1, 1});
    AABB aabb2 = AABB({1, 1, 1}, {2, 2, 2});
    AABB aabb3 = aabb1.combine(aabb2);
    TEST_BOX_VALUES(aabb3, 0, 0, 0, 2, 2, 2);

    // Check combining with a box that is contained
    AABB aabb4 = AABB({0.5, 0.5, 0.5}, {1.5, 1.5, 1.5});
    AABB aabb5 = aabb3.combine(aabb4);
    TEST_BOX_VALUES(aabb5, 0, 0, 0, 2, 2, 2);

    // Check combining with a null box
    AABB aabb6 = AABB();
    AABB aabb7 = aabb5.combine(aabb6);
    TEST_BOX_VALUES(aabb7, 0, 0, 0, 2, 2, 2);
    aabb7 = aabb6.combine(aabb5);
    TEST_BOX_VALUES(aabb7, 0, 0, 0, 2, 2, 2);
}

void test_step() {
    AABB aabb = AABB({0, 0, 0}, {1, 1, 1});
    aabb.step();
    TEST_BOX_VALUES(aabb, -FLT_EPSILON, -FLT_EPSILON, -FLT_EPSILON, 1 + FLT_EPSILON, 1 + FLT_EPSILON, 1 + FLT_EPSILON);
}

int main() {
    UNITY_BEGIN();
    RUN_TEST(test_intersects);
    RUN_TEST(test_contains);
    RUN_TEST(test_expand);
    RUN_TEST(test_combine);
    RUN_TEST(test_step);
    return UNITY_END();
}