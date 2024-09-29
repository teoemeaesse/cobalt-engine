/**
 * @file test_dbvh.h
 * @brief Test the dynamic BVH implementation.
 * @author Tomás Marques
 * @date 29-09-2024
 */

#include "core/geom/dbvh.h"
#include "unity/unity.h"

using namespace cobalt::core::geom;
using namespace cobalt;

void setUp() {}

void tearDown() {}

void test_insert() {
    DBVH<int> dbvh;
    int index = dbvh.insert(0, AABB());
    TEST_ASSERT_EQUAL(0, index);
    index = dbvh.insert(1, AABB());
    TEST_ASSERT_EQUAL(2, index);
    index = dbvh.insert(2, AABB());
    TEST_ASSERT_EQUAL(4, index);
}

void test_remove() {
    DBVH<int> dbvh;
    dbvh.remove(0);
    int index = dbvh.insert(0, AABB());
    TEST_ASSERT_EQUAL(0, index);
    dbvh.remove(index);
    index = dbvh.insert(1, AABB());
    TEST_ASSERT_EQUAL(0, index);
    dbvh.remove(index);
    for (int i = 0; i < 5; i++) {
        index = dbvh.insert(i, AABB());
        TEST_ASSERT_EQUAL(i * 2, index);
    }
    for (int i = 0; i < 10; i++) {
        dbvh.remove(i);
    }
}

void test_query_range() {
    DBVH<int> dbvh;
    std::vector<std::reference_wrapper<int>> found;
    dbvh.query(found, AABB());
    TEST_ASSERT_EQUAL(0, found.size());
    for (int i = 0; i < 5; i++) {
        dbvh.insert(i, AABB(glm::vec3(-i), glm::vec3(i)));
    }
    // Big range should find all 5
    dbvh.query(found, AABB(glm::vec3(-10), glm::vec3(10)));
    TEST_ASSERT_EQUAL(5, found.size());
    found.clear();
    // Small range centered at 0 should intersect all 5
    dbvh.query(found, AABB(glm::vec3(-0.5f), glm::vec3(0.5f)));
    TEST_ASSERT_EQUAL(5, found.size());
    found.clear();
    // Range offset from the center should intersect 3
    dbvh.query(found, AABB(glm::vec3(1.5f), glm::vec3(2.5f)));
    TEST_ASSERT_EQUAL(3, found.size());
    found.clear();
    // Void intersection
    dbvh.query(found, AABB(glm::vec3(10), glm::vec3(20)));
    TEST_ASSERT_EQUAL(0, found.size());
}

void test_query_point() {
    DBVH<int> dbvh;
    std::vector<std::reference_wrapper<int>> found;
    dbvh.query(found, glm::vec3(0));
    TEST_ASSERT_EQUAL(0, found.size());
    for (int i = 0; i < 5; i++) {
        dbvh.insert(i, AABB(glm::vec3(-i), glm::vec3(i)));
    }
    // Point at 0 should find all 5
    /*dbvh.query(found, glm::vec3(0));
    TEST_ASSERT_EQUAL(5, found.size());
    found.clear();
    // Point touching the edge of the 3rd box should find 3
    dbvh.query(found, glm::vec3(2));
    TEST_ASSERT_EQUAL(3, found.size());
    found.clear();*/
    // Point touching the edge of the last box should find 1
    dbvh.query(found, glm::vec3(4));
    TEST_ASSERT_EQUAL(1, found.size());
    found.clear();
    // Void intersection
    /*dbvh.query(found, glm::vec3(10));
    TEST_ASSERT_EQUAL(0, found.size());*/
}

int main() {
    UNITY_BEGIN();
    RUN_TEST(test_insert);
    RUN_TEST(test_remove);
    RUN_TEST(test_query_range);
    RUN_TEST(test_query_point);
    return UNITY_END();
}