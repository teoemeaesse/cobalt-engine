/**
 * @file test_bvh.h
 * @brief Test the BVH implementation.
 * @author Tomás Marques
 * @date 16-09-2024
 */

#include "core/geom/bvh.h"
#include "unity/unity.h"

using namespace cobalt::core::geom;
using namespace cobalt;

struct TestElement {
    int id;
    AABB bounds;

    TestElement(int id, const glm::vec3& min, const glm::vec3& max) : id(id), bounds(min, max) {}
};

class TestSplitStrategy : public LongestAxisSplitStrategy<TestElement> {
    public:
    const AABB& getElementBounds(const TestElement& element) const noexcept override { return element.bounds; }
};

void setUp() {}

void tearDown() {}

void test_create() {
    Vec<TestElement> elements;

    // Empty BVH
    BVH<TestElement>::Configuration config1(CreateScope<TestSplitStrategy>(), 1);
    BVH<TestElement> emptyBvh(elements, config1);
    const auto& emptyRoot = BVH<TestElement>::Debug::getRoot(emptyBvh);
    TEST_ASSERT_TRUE(BVH<TestElement>::Debug::isLeaf(emptyRoot));
    TEST_ASSERT_TRUE(BVH<TestElement>::Debug::getData(emptyRoot).size() == 0);

    elements.push_back(TestElement(1, glm::vec3(0, 0, 0), glm::vec3(1, 1, 1)));
    elements.push_back(TestElement(2, glm::vec3(2, 2, 2), glm::vec3(3, 3, 3)));

    // BVH with 2 elements, should split
    BVH<TestElement> bvh(elements, config1);

    const auto& root = BVH<TestElement>::Debug::getRoot(bvh);
    TEST_ASSERT_FALSE(BVH<TestElement>::Debug::isLeaf(root));

    const auto& left = BVH<TestElement>::Debug::getLeft(root);
    const auto& right = BVH<TestElement>::Debug::getRight(root);
    TEST_ASSERT_NOT_NULL(&left);
    TEST_ASSERT_NOT_NULL(&right);
}

void test_query() {
    Vec<TestElement> elements;
    elements.push_back(TestElement(1, glm::vec3(0, 0, 0), glm::vec3(1, 1, 1)));
    elements.push_back(TestElement(2, glm::vec3(2, 2, 2), glm::vec3(3, 3, 3)));
    elements.push_back(TestElement(3, glm::vec3(4, 4, 4), glm::vec3(5, 5, 5)));
    elements.push_back(TestElement(4, glm::vec3(6, 6, 6), glm::vec3(7, 7, 7)));
    elements.push_back(TestElement(5, glm::vec3(8, 8, 8), glm::vec3(9, 9, 9)));

    BVH<TestElement>::Configuration config2(CreateScope<TestSplitStrategy>(), 2);
    BVH<TestElement> bvh(elements, config2);

    // Query AABB
    AABB query(glm::vec3(0, 0, 0), glm::vec3(1, 1, 1));
    Vec<Wrap<TestElement>> result;
    bvh.query(result, query);
    TEST_ASSERT_TRUE(result.size() == 1);
    TEST_ASSERT_TRUE(result[0].get().id == 1);

    // Query point
    /*Vec<Wrap<TestElement>> result2;
    bvh.query(result2, glm::vec3(0.5, 0.5, 0.5));
    TEST_ASSERT_TRUE(result2.size() == 1);
    TEST_ASSERT_TRUE(result2[0].get().id == 1);*/
}

int main() {
    UNITY_BEGIN();
    RUN_TEST(test_create);
    RUN_TEST(test_query);
    return UNITY_END();
}