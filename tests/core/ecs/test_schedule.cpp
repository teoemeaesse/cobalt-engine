// Created by tomas on
// 28-01-2024.

#include "core/ecs/system/schedule.h"
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

class MovementSystem : public System<Query<RefMut<Position>, Ref<Velocity>>> {
    public:
    MovementSystem(const World& world) : System<Query<RefMut<Position>, Ref<Velocity>>>(world) {}
    void run(Query<RefMut<Position>, Ref<Velocity>> query) override {
        for (auto [position, velocity] : query) {
            position.x += velocity.x;
            position.y += velocity.y;
        }
    }
};

void setUp(void) {}

void tearDown(void) {}

void test_scheduled_system() {
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

    Schedule schedule(world);
    schedule.addSystem<MovementSystem>(world);
    schedule.run();
    TEST_ASSERT_EQUAL_INT(4, e1.get<Ref<Position>>().x);
    TEST_ASSERT_EQUAL_INT(6, e1.get<Ref<Position>>().y);
    TEST_ASSERT_EQUAL_INT(6, e2.get<Ref<Position>>().x);
    TEST_ASSERT_EQUAL_INT(7, e2.get<Ref<Position>>().y);
    TEST_ASSERT_EQUAL_INT(24, e3.get<Ref<Position>>().x);
    TEST_ASSERT_EQUAL_INT(26, e3.get<Ref<Position>>().y);
    schedule.run();
    TEST_ASSERT_EQUAL_INT(7, e1.get<Ref<Position>>().x);
    TEST_ASSERT_EQUAL_INT(10, e1.get<Ref<Position>>().y);
    TEST_ASSERT_EQUAL_INT(6, e2.get<Ref<Position>>().x);
    TEST_ASSERT_EQUAL_INT(7, e2.get<Ref<Position>>().y);
    TEST_ASSERT_EQUAL_INT(37, e3.get<Ref<Position>>().x);
    TEST_ASSERT_EQUAL_INT(40, e3.get<Ref<Position>>().y);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_scheduled_system);
    return UNITY_END();
}