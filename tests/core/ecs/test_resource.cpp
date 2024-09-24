/**
 * @file test_resource.h
 * @brief Test the ECS resource implementation.
 * @author Tomás Marques
 * @date 28-01-2024
 */

#include "core/ecs/world.h"
#include "unity/unity.h"

using namespace cobalt::core::ecs;
using namespace cobalt;

class MyResource : public Resource {
    public:
    MyResource() noexcept : valueInt(0), valueFloat(3.141) {}
    explicit MyResource(int valueInt) noexcept : valueInt(valueInt), valueFloat(0.577) {}

    int valueInt;
    float valueFloat;
};

void setUp(void) {}

void tearDown(void) {}

void test_read() {
    World world;
    world.addResource<MyResource>();

    auto request = world.read<MyResource>();
    const MyResource& resource = *request;
    TEST_ASSERT_EQUAL(0, resource.valueInt);
    TEST_ASSERT_EQUAL_FLOAT(3.141, resource.valueFloat);

    world.addResource<MyResource>(1);
    auto request2 = world.read<MyResource>();
    const MyResource& resource2 = *request2;
    TEST_ASSERT_EQUAL(1, resource2.valueInt);
    TEST_ASSERT_EQUAL_FLOAT(0.577, resource2.valueFloat);
}

void test_write() {
    World world;
    world.addResource<MyResource>();

    auto request = world.write<MyResource>();
    MyResource& resource = *request;
    resource.valueInt = 50;
    resource.valueFloat = 42;

    auto request2 = world.read<MyResource>();
    const MyResource& resource2 = *request2;
    TEST_ASSERT_EQUAL(50, resource2.valueInt);
    TEST_ASSERT_EQUAL_FLOAT(42, resource2.valueFloat);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_read);
    RUN_TEST(test_write);
    return UNITY_END();
}