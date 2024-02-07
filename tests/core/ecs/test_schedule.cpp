// Created by tomas on
// 28-01-2024.

#include "core/ecs/component/registry.h"
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
    MovementSystem(EntityRegistry& entityRegistry, ResourceRegistry& resourceRegistry)
        : System<Query<RefMut<Position>, Ref<Velocity>>>(entityRegistry, resourceRegistry) {}
    void run(Query<RefMut<Position>, Ref<Velocity>> query) override {
        for (auto [position, velocity] : query) {
            position.x += velocity.x;
            position.y += velocity.y;
        }
    }
};

class MultiSystem : public System<Query<RefMut<Position>, Ref<Velocity>>, Query<RefMut<Position>, Ref<Mass>>> {
    public:
    MultiSystem(EntityRegistry& entityRegistry, ResourceRegistry& resourceRegistry)
        : System<Query<RefMut<Position>, Ref<Velocity>>, Query<RefMut<Position>, Ref<Mass>>>(entityRegistry, resourceRegistry) {}
    void run(Query<RefMut<Position>, Ref<Velocity>> query1, Query<RefMut<Position>, Ref<Mass>> query2) override {
        for (auto [position, velocity] : query1) {
            position.x += velocity.x;
            position.y += velocity.y;
        }
        for (auto [position, mass] : query2) {
            position.x *= mass.mass;
            position.y *= mass.mass;
        }
    }
};

class MyResource : public Resource {
    public:
    MyResource() noexcept : valueInt(2), valueFloat(3.141) {}
    explicit MyResource(int valueInt) noexcept : valueInt(valueInt), valueFloat(0.577) {}

    int valueInt;
    float valueFloat;
};

class MixedSystem : public System<Query<RefMut<Position>, Ref<Velocity>>, ReadRequest<MyResource>> {
    public:
    MixedSystem(EntityRegistry& entityRegistry, ResourceRegistry& resourceRegistry)
        : System<Query<RefMut<Position>, Ref<Velocity>>, ReadRequest<MyResource>>(entityRegistry, resourceRegistry) {}
    void run(Query<RefMut<Position>, Ref<Velocity>> query, ReadRequest<MyResource> request) override {
        for (auto [position, velocity] : query) {
            position.x += velocity.x;
            position.y += velocity.y;
            const MyResource& resource = request.get();
            position.x *= resource.valueInt;
            position.y *= resource.valueInt;
        }
    }
};

void setUp(void) {}

void tearDown(void) {}

void test_single_system() {
    EntityRegistry entityRegistry;
    ComponentRegistry componentRegistry;
    ResourceRegistry resourceRegistry;
    componentRegistry.registerComponent<Position>();
    componentRegistry.registerComponent<Velocity>();
    componentRegistry.registerComponent<Mass>();

    Entity& e1 = entityRegistry.add(componentRegistry);
    Entity& e2 = entityRegistry.add(componentRegistry);
    Entity& e3 = entityRegistry.add(componentRegistry);
    e1.add<Position>(1, 2);
    e1.add<Velocity>(3, 4);
    e1.add<Mass>(5);
    e2.add<Position>(6, 7);
    e2.add<Mass>(10);
    e3.add<Position>(11, 12);
    e3.add<Velocity>(13, 14);

    Schedule schedule(entityRegistry, resourceRegistry);
    schedule.addSystem<MovementSystem>();
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

void test_multi_system() {
    EntityRegistry entityRegistry;
    ComponentRegistry componentRegistry;
    ResourceRegistry resourceRegistry;
    componentRegistry.registerComponent<Position>();
    componentRegistry.registerComponent<Velocity>();
    componentRegistry.registerComponent<Mass>();

    Entity& e1 = entityRegistry.add(componentRegistry);
    Entity& e2 = entityRegistry.add(componentRegistry);
    Entity& e3 = entityRegistry.add(componentRegistry);
    e1.add<Position>(1, 2);
    e1.add<Velocity>(3, 4);
    e1.add<Mass>(5);
    e2.add<Position>(6, 7);
    e2.add<Mass>(10);
    e3.add<Position>(11, 12);
    e3.add<Velocity>(13, 14);

    Schedule schedule(entityRegistry, resourceRegistry);
    schedule.addSystem<MultiSystem>();
    schedule.run();
    TEST_ASSERT_EQUAL_INT(20, e1.get<Ref<Position>>().x);
    TEST_ASSERT_EQUAL_INT(30, e1.get<Ref<Position>>().y);
    TEST_ASSERT_EQUAL_INT(60, e2.get<Ref<Position>>().x);
    TEST_ASSERT_EQUAL_INT(70, e2.get<Ref<Position>>().y);
    TEST_ASSERT_EQUAL_INT(24, e3.get<Ref<Position>>().x);
    TEST_ASSERT_EQUAL_INT(26, e3.get<Ref<Position>>().y);
    schedule.run();
    TEST_ASSERT_EQUAL_INT(115, e1.get<Ref<Position>>().x);
    TEST_ASSERT_EQUAL_INT(170, e1.get<Ref<Position>>().y);
    TEST_ASSERT_EQUAL_INT(600, e2.get<Ref<Position>>().x);
    TEST_ASSERT_EQUAL_INT(700, e2.get<Ref<Position>>().y);
    TEST_ASSERT_EQUAL_INT(37, e3.get<Ref<Position>>().x);
    TEST_ASSERT_EQUAL_INT(40, e3.get<Ref<Position>>().y);
}

void test_mixed_system() {
    EntityRegistry entityRegistry;
    ComponentRegistry componentRegistry;
    ResourceRegistry resourceRegistry;
    componentRegistry.registerComponent<Position>();
    componentRegistry.registerComponent<Velocity>();
    componentRegistry.registerComponent<Mass>();
    resourceRegistry.add<MyResource>();

    Entity& e1 = entityRegistry.add(componentRegistry);
    Entity& e2 = entityRegistry.add(componentRegistry);
    Entity& e3 = entityRegistry.add(componentRegistry);
    e1.add<Position>(1, 2);
    e1.add<Velocity>(3, 4);
    e1.add<Mass>(5);
    e2.add<Position>(6, 7);
    e2.add<Mass>(10);
    e3.add<Position>(11, 12);
    e3.add<Velocity>(13, 14);

    Schedule schedule(entityRegistry, resourceRegistry);
    schedule.addSystem<MixedSystem>();
    schedule.run();
    TEST_ASSERT_EQUAL_INT(8, e1.get<Ref<Position>>().x);
    TEST_ASSERT_EQUAL_INT(12, e1.get<Ref<Position>>().y);
    TEST_ASSERT_EQUAL_INT(6, e2.get<Ref<Position>>().x);
    TEST_ASSERT_EQUAL_INT(7, e2.get<Ref<Position>>().y);
    TEST_ASSERT_EQUAL_INT(48, e3.get<Ref<Position>>().x);
    TEST_ASSERT_EQUAL_INT(52, e3.get<Ref<Position>>().y);
    schedule.run();
    TEST_ASSERT_EQUAL_INT(22, e1.get<Ref<Position>>().x);
    TEST_ASSERT_EQUAL_INT(32, e1.get<Ref<Position>>().y);
    TEST_ASSERT_EQUAL_INT(6, e2.get<Ref<Position>>().x);
    TEST_ASSERT_EQUAL_INT(7, e2.get<Ref<Position>>().y);
    TEST_ASSERT_EQUAL_INT(122, e3.get<Ref<Position>>().x);
    TEST_ASSERT_EQUAL_INT(132, e3.get<Ref<Position>>().y);
}

void test_lambda_system() {
    EntityRegistry entityRegistry;
    ComponentRegistry componentRegistry;
    ResourceRegistry resourceRegistry;
    componentRegistry.registerComponent<Position>();
    componentRegistry.registerComponent<Velocity>();
    componentRegistry.registerComponent<Mass>();
    resourceRegistry.add<MyResource>();

    Entity& e1 = entityRegistry.add(componentRegistry);
    Entity& e2 = entityRegistry.add(componentRegistry);
    Entity& e3 = entityRegistry.add(componentRegistry);
    e1.add<Position>(1, 2);
    e1.add<Velocity>(3, 4);
    e1.add<Mass>(5);
    e2.add<Position>(6, 7);
    e2.add<Mass>(10);
    e3.add<Position>(11, 12);
    e3.add<Velocity>(13, 14);

    Schedule schedule(entityRegistry, resourceRegistry);
    schedule.addSystem<Query<RefMut<Position>, Ref<Velocity>>, ReadRequest<MyResource>>([](auto query, auto request) {
        for (auto [position, velocity] : query) {
            position.x += velocity.x;
            position.y += velocity.y;
            const MyResource& resource = request.get();
            position.x *= resource.valueInt;
            position.y *= resource.valueInt;
        }
    });
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
    RUN_TEST(test_single_system);
    RUN_TEST(test_multi_system);
    RUN_TEST(test_mixed_system);
    return UNITY_END();
}