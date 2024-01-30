// Created by tomas on
// 28-01-2024.

#include "core/ecs/system/query.h"
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

void test_const_query() {
    World world;
    world.registerComponent<Position>();
    world.registerComponent<Velocity>();
    world.registerComponent<Mass>();

    Entity& e1 = world.createEntity();
    Entity& e2 = world.createEntity();
    Entity& e3 = world.createEntity();

    e1.add<Position>(1, 2);
    e1.add<Velocity>(3, 4);
    e1.add<Mass>(5);

    e2.add<Position>(6, 7);
    e2.add<Mass>(10);

    e3.add<Position>(11, 12);
    e3.add<Velocity>(13, 14);

    Query<Ref<Position>, Ref<Velocity>> query(world);
    uint count = 0;
    for (auto [position, velocity] : query) {
        TEST_ASSERT_EQUAL_INT(position.x, velocity.x - 2);
        TEST_ASSERT_EQUAL_INT(position.y, velocity.y - 2);
        count++;
    }
    TEST_ASSERT_EQUAL_INT(count, 2);

    Query<MutRef<Position>, Ref<Velocity>> query2(world);
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

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_const_query);
    // RUN_TEST(test_const_query);
    return UNITY_END();
}