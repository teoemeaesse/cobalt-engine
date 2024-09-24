/**
 * @file test_octree.h
 * @brief Test the Octree implementation.
 * @author Tomás Marques
 * @date 11-09-2024
 */

#include "core/geom/octree.h"
#include "unity/unity.h"

using namespace cobalt::core::geom;
using namespace cobalt;

void setUp() {}

void tearDown() {}

// Helper function to create an AABB for an integer element
AABB getElementBounds(const int& element) {
    // For simplicity, assume each element represents a point at (element, element, element)
    // with a small bounding box around it
    glm::vec3 point = glm::vec3(static_cast<float>(element));
    glm::vec3 halfSize = glm::vec3(0.1f);
    return AABB(point - halfSize, point + halfSize);
}

void test_insert() {
    // Elements with null bounds should not be inserted
    Octree<int>::Configuration config([](const int& element) { return AABB(); });
    Octree<int> octree(AABB(), config);
    octree.insert(1);
    Vec<Wrap<int>> found;
    octree.query(found);
    TEST_ASSERT_EQUAL_INT(0, found.size());

    // Elements with bounds outside the octree should not be inserted
    Octree<int>::Configuration config2([](const int& element) { return AABB({1.5f, 1.5f, 1.5f}, {2.0f, 2.0f, 2.0f}); });
    Octree<int> octree2(AABB({-1.0f, -1.0f, -1.0f}, {1.0f, 1.0f, 1.0f}), config2);
    octree2.insert(1);
    Vec<Wrap<int>> found2;
    octree2.query(found2);
    TEST_ASSERT_EQUAL_INT(0, found2.size());

    // Elements with bounds inside the octree should be inserted
    Octree<int>::Configuration config3([](const int& element) { return AABB({1.5f, 1.5f, 1.5f}, {2.0f, 2.0f, 2.0f}); });
    Octree<int> octree3(AABB({1.0f, 1.0f, 1.0f}, {2.0f, 2.0f, 2.0f}), config3);
    octree3.insert(1);
    Vec<Wrap<int>> found3;
    octree3.query(found3);
    TEST_ASSERT_EQUAL_INT(1, found3.size());
}

void test_insert_multiple() {
    // Elements with bounds fully inside the octree should be inserted
    Octree<int>::Configuration config1(getElementBounds, 10, 3);
    Octree<int> octree1(AABB({1.0f, 1.0f, 1.0f}, {4.0f, 4.0f, 4.0f}), config1);
    octree1.insert(2);
    octree1.insert(3);
    octree1.insert(4);
    Vec<Wrap<int>> found;
    octree1.query(found);
    TEST_ASSERT_EQUAL_INT(3, found.size());
    TEST_ASSERT_EQUAL_INT(2, found[0].get());
    TEST_ASSERT_EQUAL_INT(3, found[1].get());
    TEST_ASSERT_EQUAL_INT(4, found[2].get());

    // Elements with bounds partially inside the octree should be inserted
    Octree<int>::Configuration config2(getElementBounds, 10, 3);
    Octree<int> octree2(AABB({1.0f, 1.0f, 1.0f}, {3.0f, 3.0f, 3.0f}), config2);
    octree2.insert(2);  // Inside
    octree2.insert(3);  // Partially inside
    octree2.insert(5);  // Outside
    Vec<Wrap<int>> found2;
    octree2.query(found2);
    TEST_ASSERT_EQUAL_INT(2, found2.size());
    TEST_ASSERT_EQUAL_INT(2, found2[0].get());
    TEST_ASSERT_EQUAL_INT(3, found2[1].get());
}

void test_query_range() {
    // Test querying within a specific range
    Octree<int>::Configuration config(getElementBounds, 10, 3);
    Octree<int> octree(AABB({0.0f, 0.0f, 0.0f}, {10.0f, 10.0f, 10.0f}), config);
    for (int i = 0; i < 10; i++) {
        octree.insert(i);
    }
    Vec<Wrap<int>> found;
    AABB queryRange(glm::vec3(5.0f, 5.0f, 5.0f), glm::vec3(10.0f, 10.0f, 10.0f));
    octree.query(found, queryRange);
    TEST_ASSERT_EQUAL_INT(4, found.size());
    // Expected elements: 6,7,8,9
    for (int& element : found) {
        TEST_ASSERT_TRUE(element > 5 && element < 10);
    }
}

void test_query_point() {
    // Test querying a specific point
    Octree<int>::Configuration config(getElementBounds, 10, 3);
    Octree<int> octree(AABB({0.0f, 0.0f, 0.0f}, {10.0f, 10.0f, 10.0f}), config);
    for (int i = 1; i <= 10; i++) {
        octree.insert(i);
    }
    Vec<Wrap<int>> found;
    glm::vec3 queryPoint(7.0f, 7.0f, 7.0f);
    octree.query(found, queryPoint);
    TEST_ASSERT_EQUAL_INT(1, found.size());
    TEST_ASSERT_EQUAL_INT(7, found[0].get());
}

void test_octree_split() {
    // Test the splitting of the octree when maxElements is exceeded
    Octree<int>::Configuration config(getElementBounds, 10, 2);  // maxElements set to 2
    Octree<int> octree(AABB({0.0f, 0.0f, 0.0f}, {4.0f, 4.0f, 4.0f}), config);
    octree.insert(1);
    octree.insert(2);
    octree.insert(3);  // This should cause a split
    Vec<Wrap<int>> found;
    octree.query(found);
    TEST_ASSERT_EQUAL_INT(3, found.size());

    const auto& root = Octree<int>::Debug::getRoot(octree);
    TEST_ASSERT_FALSE(root.isLeaf());
    TEST_ASSERT_EQUAL_INT(1, Octree<int>::Debug::getData(root).size());

    int totalElementsInChildren = 0;
    for (const auto& child : Octree<int>::Debug::getChildren(root)) {
        totalElementsInChildren += Octree<int>::Debug::getData(child).size();
    }
    TEST_ASSERT_EQUAL_INT(2, totalElementsInChildren);
}

void test_out_of_bounds_insertion() {
    // Test inserting elements that are out of bounds
    Octree<int>::Configuration config(getElementBounds, 10, 3);
    Octree<int> octree(AABB({0.0f, 0.0f, 0.0f}, {5.0f, 5.0f, 5.0f}), config);
    octree.insert(6);  // Outside the bounds
    Vec<Wrap<int>> found;
    octree.query(found);
    TEST_ASSERT_EQUAL_INT(0, found.size());
}

void test_insert_duplicate_elements() {
    // Test inserting duplicate elements
    Octree<int>::Configuration config(getElementBounds, 10, 3);
    Octree<int> octree(AABB({0.0f, 0.0f, 0.0f}, {5.0f, 5.0f, 5.0f}), config);
    octree.insert(2);
    octree.insert(2);
    Vec<Wrap<int>> found;
    octree.query(found);
    TEST_ASSERT_EQUAL_INT(2, found.size());
    TEST_ASSERT_EQUAL_INT(2, found[0].get());
    TEST_ASSERT_EQUAL_INT(2, found[1].get());
}

int main() {
    UNITY_BEGIN();
    RUN_TEST(test_insert);
    RUN_TEST(test_insert_multiple);
    RUN_TEST(test_query_range);
    RUN_TEST(test_query_point);
    RUN_TEST(test_octree_split);
    RUN_TEST(test_out_of_bounds_insertion);
    RUN_TEST(test_insert_duplicate_elements);
    return UNITY_END();
}