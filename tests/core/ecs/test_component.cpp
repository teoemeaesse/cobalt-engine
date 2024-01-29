// Created by tomas on
// 28-01-2024.

#include "core/ecs/component/registry.h"
#include "core/ecs/entity/registry.h"
#include "unity/unity.h"

using namespace cobalt::core::ecs;

void setUp(void) {}

void tearDown(void) {}

struct Position : public Component {
    Position(int x, int y) : x(x), y(y) {}
    Position() : x(0), y(0) {}
    int x;
    int y;
};

struct Velocity : public Component {
    Velocity(int x, int y) : x(x), y(y) {}
    Velocity() : x(0), y(0) {}
    int x;
    int y;
};

struct Mass : public Component {
    Mass(int mass) : mass(mass) {}
    Mass() : mass(0) {}
    int mass;
};

void test_component_registry_register() {
    ComponentRegistry componentRegistry;
    componentRegistry.registerComponent<Position>();
    componentRegistry.registerComponent<Velocity>();
    componentRegistry.registerComponent<Mass>();
}

void test_component_registry_add() {
    ComponentRegistry componentRegistry;
    componentRegistry.registerComponent<Position>();
    componentRegistry.registerComponent<Velocity>();
    componentRegistry.registerComponent<Mass>();
    EntityRegistry entityRegistry;
    auto& entity = entityRegistry.add(componentRegistry);
    TEST_ASSERT_FALSE_MESSAGE(entity.has<Position>(), "Entity should not have Position component");
    TEST_ASSERT_FALSE_MESSAGE(entity.has<Velocity>(), "Entity should not have Velocity component");
    TEST_ASSERT_FALSE_MESSAGE(entity.has<Mass>(), "Entity should not have Mass component");
    entity.add<Position>(0, 0);
    TEST_ASSERT_TRUE_MESSAGE(entity.has<Position>(), "Entity should have Position component");
    entity.add<Velocity>(0, 0);
    TEST_ASSERT_TRUE_MESSAGE(entity.has<Velocity>(), "Entity should have Velocity component");
    entity.add<Mass>(0);
    TEST_ASSERT_TRUE_MESSAGE(entity.has<Mass>(), "Entity should have Mass component");
    entity.kill();
    TEST_ASSERT_FALSE_MESSAGE(entity.has<Position>(), "Entity should not have Position component");
    entity.add<Position>(0, 0);
    TEST_ASSERT_TRUE_MESSAGE(entity.has<Position>(), "Entity should have Position component");
    entity.add<Velocity>(0, 0);
    entity.add<Mass>(0);
}

void test_component_registry_remove() {
    ComponentRegistry componentRegistry;
    componentRegistry.registerComponent<Position>();
    componentRegistry.registerComponent<Velocity>();
    componentRegistry.registerComponent<Mass>();
    EntityRegistry entityRegistry;
    auto& entity = entityRegistry.add(componentRegistry);
    entity.add<Position>(0, 0);
    entity.add<Velocity>(0, 0);
    entity.add<Mass>(0);
    entity.remove<Position>();
    entity.remove<Velocity>();
    entity.remove<Mass>();
    entity.remove<Position>();
    entity.remove<Velocity>();
    entity.remove<Mass>();
    entityRegistry.remove(entity);
    entity.remove<Position>();
    entity.remove<Velocity>();
    entity.remove<Mass>();
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_component_registry_register);
    RUN_TEST(test_component_registry_add);
    RUN_TEST(test_component_registry_remove);
    return UNITY_END();
}