/**
 * @file test_path.h
 * @brief Test the system path implementation.
 * @author Tomás Marques
 * @date 19-11-2023
 */

#include "core/io/path.h"
#include "unity/unity.h"

std::string curPath;

void setUp(void) { curPath = std::filesystem::current_path().string(); }

void tearDown(void) {}

void test_path_create() {
    cobalt::core::io::Path path("foo/bar", true);
    TEST_ASSERT_EQUAL_STRING((curPath + "/foo/bar").c_str(), path.getPath().c_str());
    TEST_ASSERT_EQUAL_STRING("bar", path.getFileName().c_str());
    TEST_ASSERT_EQUAL_STRING((curPath + "/foo").c_str(), path.getDirectory().c_str());
    TEST_ASSERT_EQUAL_STRING("bar", path.getFileNameWithoutExtension().c_str());
    TEST_ASSERT_EQUAL_STRING("", path.getExtension().c_str());
    TEST_ASSERT_FALSE(path.exists());
    TEST_ASSERT_FALSE(path.isFile());
    TEST_ASSERT_FALSE(path.isDirectory());
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_path_create);
    // TODO: Add more tests
    // Path is just a wrapper around std::filesystem::path so it should be enough to test that it works as expected
    return UNITY_END();
}