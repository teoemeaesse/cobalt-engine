// Created by tomas on
// 28-01-2024.

#include "core/ecs/entity/registry.h"
#include "core/ecs/system/manager.h"
#include "core/ecs/system/request.h"
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
    ComponentRegistry componentRegistry;
    EntityRegistry entityRegistry(componentRegistry);
    ResourceRegistry resourceRegistry;
    SystemManager systemManager(entityRegistry, resourceRegistry);
    resourceRegistry.add<MyResource>();

    ReadRequest<MyResource> request(entityRegistry, resourceRegistry, systemManager);
    const MyResource& resource = request.get();
    TEST_ASSERT_EQUAL(0, resource.valueInt);
    TEST_ASSERT_EQUAL_FLOAT(3.141, resource.valueFloat);

    resourceRegistry.add<MyResource>(1);
    ReadRequest<MyResource> request2(entityRegistry, resourceRegistry, systemManager);
    const MyResource& resource2 = request2.get();
    TEST_ASSERT_EQUAL(1, resource2.valueInt);
    TEST_ASSERT_EQUAL_FLOAT(0.577, resource2.valueFloat);
}

void test_write() {
    ComponentRegistry componentRegistry;
    EntityRegistry entityRegistry(componentRegistry);
    ResourceRegistry resourceRegistry;
    SystemManager systemManager(entityRegistry, resourceRegistry);
    resourceRegistry.add<MyResource>();

    WriteRequest<MyResource> request(entityRegistry, resourceRegistry, systemManager);
    MyResource& resource = request.get();
    resource.valueInt = 50;
    resource.valueFloat = 42;

    ReadRequest<MyResource> request2(entityRegistry, resourceRegistry, systemManager);
    const MyResource& resource2 = request2.get();
    TEST_ASSERT_EQUAL(50, resource2.valueInt);
    TEST_ASSERT_EQUAL_FLOAT(42, resource2.valueFloat);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_read);
    RUN_TEST(test_write);
    return UNITY_END();
}