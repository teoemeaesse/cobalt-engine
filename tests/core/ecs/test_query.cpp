// Created by tomas on
// 28-01-2024.

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

void test_query() {
    World world;
    world.registerComponent<Position>();
    world.registerComponent<Velocity>();
    world.registerComponent<Mass>();

    Entity& e1 = world.spawn();
    Entity& e2 = world.spawn();
    Entity& e3 = world.spawn();

    e1.add<Position>(1, 2);
    e1.add<Velocity>(3, 4);
    e1.add<Mass>(5);

    e2.add<Position>(6, 7);
    e2.add<Mass>(10);

    e3.add<Position>(11, 12);
    e3.add<Velocity>(13, 14);

    auto query = world.makeQuery<Ref<Position>, Ref<Velocity>>();
    uint count = 0;
    for (auto [position, velocity] : query) {
        TEST_ASSERT_EQUAL_INT(position.x, velocity.x - 2);
        TEST_ASSERT_EQUAL_INT(position.y, velocity.y - 2);
        count++;
    }
    TEST_ASSERT_EQUAL_INT(count, 2);

    auto query2 = world.makeQuery<RefMut<Position>, Ref<Velocity>>();
    for (auto [position, velocity] : query2) {
        position.x += velocity.x;
        position.y += velocity.y;
    }
    auto [x, y] = e1.get<Ref<Position>>();
    TEST_ASSERT_EQUAL_INT(x, 4);
    TEST_ASSERT_EQUAL_INT(y, 6);
    auto [x2, y2] = e3.get<Ref<Position>>();
    TEST_ASSERT_EQUAL_INT(x2, 24);
    TEST_ASSERT_EQUAL_INT(y2, 26);
}

void test_entity_query() {
    World world;
    world.registerComponent<Position>();
    world.registerComponent<Velocity>();
    world.registerComponent<Mass>();

    Entity& e1 = world.spawn();
    Entity& e2 = world.spawn();
    Entity& e3 = world.spawn();

    e1.add<Position>(1, 2);
    e2.add<Position>(6, 7);
    e3.add<Position>(11, 12);

    auto query = world.makeQuery<Ref<Entity>, Ref<Position>>();
    for (auto [entity, position] : query) {
        switch (entity.getID()) {
            case 0:
                TEST_ASSERT_EQUAL_INT(position.x, 1);
                TEST_ASSERT_EQUAL_INT(position.y, 2);
                break;
            case 1:
                TEST_ASSERT_EQUAL_INT(position.x, 6);
                TEST_ASSERT_EQUAL_INT(position.y, 7);
                break;
            case 2:
                TEST_ASSERT_EQUAL_INT(position.x, 11);
                TEST_ASSERT_EQUAL_INT(position.y, 12);
                break;
            default:
                TEST_FAIL_MESSAGE("Invalid entity id");
        }
    }
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_query);
    RUN_TEST(test_entity_query);
    return UNITY_END();
}