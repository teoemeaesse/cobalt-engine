// Created by tomas on
// 28-01-2024.

#include "core/ecs/component/registry.h"
#include "core/ecs/entity/registry.h"
#include "unity/unity.h"

using namespace cobalt;
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
    EntityRegistry entityRegistry(componentRegistry);
    auto& entity = entityRegistry.add();
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
    bool check = entity.has<Position, Velocity>();
    TEST_ASSERT_TRUE_MESSAGE(check, "Entity should have Position and Velocity components");
    check = entity.has<Position, Velocity, Mass>();
    TEST_ASSERT_FALSE_MESSAGE(check, "Entity should not have Position, Velocity and Mass components");
    entity.add<Mass>(0);
}

void test_component_registry_remove() {
    ComponentRegistry componentRegistry;
    componentRegistry.registerComponent<Position>();
    componentRegistry.registerComponent<Velocity>();
    componentRegistry.registerComponent<Mass>();
    EntityRegistry entityRegistry(componentRegistry);
    auto& entity = entityRegistry.add();
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

void test_component_registry_get() {
    ComponentRegistry componentRegistry;
    componentRegistry.registerComponent<Position>();
    componentRegistry.registerComponent<Velocity>();
    componentRegistry.registerComponent<Mass>();
    EntityRegistry entityRegistry(componentRegistry);
    auto& entity = entityRegistry.add();
    entity.add<Position>(0, 0);
    auto& position = entity.get<Position&>();
    position.x = 1;
    position.y = 2;
    auto& updatedPosition = entity.get<const Position&>();
    TEST_ASSERT_EQUAL_INT(1, updatedPosition.x);
    TEST_ASSERT_EQUAL_INT(2, updatedPosition.y);
    try {
        auto [errPosition, errVelocity] = entity.getMany<const Position&, const Velocity&>();
        TEST_FAIL_MESSAGE("Entity should not have Velocity component");
    } catch (const ComponentNotFoundException<Velocity, ComponentRegistry>& e) {
        TEST_ASSERT_EQUAL_STRING("cobalt::core::ecs::ComponentRegistry threw: Component not found for entity (0) with component: Velocity", e.what());
    }
}

void test_component_variadics() {
    ComponentRegistry componentRegistry;
    componentRegistry.registerComponent<Position>();
    componentRegistry.registerComponent<Velocity>();
    componentRegistry.registerComponent<Mass>();
    EntityRegistry entityRegistry(componentRegistry);
    auto& entity = entityRegistry.add();
    entity.add<Position>(0, 0);
    entity.add<Velocity>(0, 0);
    entity.add<Mass>(0);
    bool check = entity.has<Position, Velocity>();
    TEST_ASSERT_TRUE_MESSAGE(check, "Entity should have Position and Velocity components");
    check = entity.has<Position, Velocity, Mass>();
    TEST_ASSERT_TRUE_MESSAGE(check, "Entity should have Position, Velocity and Mass components");
    entity.remove<Position, Velocity>();
    check = entity.has<Position, Velocity>();
    TEST_ASSERT_FALSE_MESSAGE(check, "Entity should not have Position and Velocity components");
    check = entity.has<Position, Velocity, Mass>();
    TEST_ASSERT_FALSE_MESSAGE(check, "Entity should not have Position, Velocity and Mass components");
    entity.add<Position>(0, 0);
    entity.add<Velocity>(0, 0);
    entity.add<Mass>(0);
    entity.add<Position>(0, 0);
    check = entity.has<Position, Velocity, Mass>();
    TEST_ASSERT_TRUE_MESSAGE(check, "Entity should have Position, Velocity and Mass components");
    entity.remove<Position, Mass>();
    check = entity.has<Velocity>();
    TEST_ASSERT_TRUE_MESSAGE(check, "Entity should have Velocity component");
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_component_registry_register);
    RUN_TEST(test_component_registry_add);
    RUN_TEST(test_component_registry_remove);
    RUN_TEST(test_component_registry_get);
    RUN_TEST(test_component_variadics);
    return UNITY_END();
}