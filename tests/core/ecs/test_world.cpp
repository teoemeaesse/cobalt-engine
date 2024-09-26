/**
 * @file test_world.h
 * @brief Test the ECS world implementation.
 * @author Tomás Marques
 * @date 07-02-2024
 */

#include "core/ecs/world.h"
#include "unity/unity.h"

using namespace cobalt::core::ecs;
using namespace cobalt;

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

void setUp(void) {}

void tearDown(void) {}

void test_entity() {
    World world;
    world.registerComponent<Position>();
    world.registerComponent<Velocity>();
    world.registerComponent<Mass>();
    Entity& entity = world.spawn();
    entity.add<Position>(1, 2);
    entity.add<Velocity>(3, 4);
    entity.add<Mass>(5);
    TEST_ASSERT_EQUAL(1, entity.get<const Position&>().x);
    TEST_ASSERT_EQUAL(2, entity.get<const Position&>().y);
    TEST_ASSERT_EQUAL(3, entity.get<const Velocity&>().x);
    TEST_ASSERT_EQUAL(4, entity.get<const Velocity&>().y);
    TEST_ASSERT_EQUAL(5, entity.get<const Mass&>().mass);
    entity.kill();
    try {
        entity.get<const Position&>();
        TEST_FAIL();
    } catch (const std::exception& e) {
        TEST_ASSERT_EQUAL_STRING("[cobalt::core::ecs::ComponentRegistry] Error: Component not found for entity (0) with component: Position",
                                 e.what());
    }
    entity.kill();
    entity.kill();
}

void test_system() {
    World world;
    world.registerComponent<Position>();
    world.registerComponent<Velocity>();
    world.registerComponent<Mass>();
    world.addSystem<Query<Position&, Velocity&, const Mass&>>(DefaultSchedules::PreUpdate, [](auto query) {
        for (auto [position, velocity, mass] : query) {
            position.x += velocity.x;
            position.y += velocity.y;
            velocity.x += mass.mass;
            velocity.y += mass.mass;
        }
    });
    Entity& entity = world.spawn();
    entity.add<Position>(1, 2);
    entity.add<Velocity>(3, 4);
    entity.add<Mass>(5);
    world.update();
    TEST_ASSERT_EQUAL(4, entity.get<const Position&>().x);
    TEST_ASSERT_EQUAL(6, entity.get<const Position&>().y);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_entity);
    RUN_TEST(test_system);
    return UNITY_END();
}