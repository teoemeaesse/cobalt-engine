// Created by tomas on
// 28-01-2024.

#include "core/ecs/component/registry.h"
#include "core/ecs/entity/registry.h"
#include "unity/unity.h"

void setUp(void) {}

void tearDown(void) {}

void test_entity_registry_add() {
    cobalt::core::ecs::ComponentRegistry componentRegistry;
    cobalt::core::ecs::EntityRegistry entityRegistry;

    auto& entity = entityRegistry.add(componentRegistry);
    TEST_ASSERT_EQUAL_INT(0, entity.getID());
    TEST_ASSERT_EQUAL_INT(1, entity.getVersion());
    TEST_ASSERT_EQUAL_INT(1, entityRegistry.getSize());

    auto& entity2 = entityRegistry.add(componentRegistry);
    TEST_ASSERT_EQUAL_INT(1, entity2.getID());
    TEST_ASSERT_EQUAL_INT(1, entity2.getVersion());
    TEST_ASSERT_EQUAL_INT(2, entityRegistry.getSize());
}

void test_entity_registry_remove() {
    cobalt::core::ecs::ComponentRegistry componentRegistry;
    cobalt::core::ecs::EntityRegistry entityRegistry;

    auto& entity = entityRegistry.add(componentRegistry);
    TEST_ASSERT_EQUAL_INT(0, entity.getID());
    TEST_ASSERT_EQUAL_INT(1, entity.getVersion());
    TEST_ASSERT_EQUAL_INT(1, entityRegistry.getSize());

    entityRegistry.remove(entity);
    TEST_ASSERT_EQUAL_INT(0, entity.getID());
    TEST_ASSERT_EQUAL_INT(0, entity.getVersion());
    TEST_ASSERT_EQUAL_INT(1, entityRegistry.getSize());

    auto& entity2 = entityRegistry.add(componentRegistry);
    TEST_ASSERT_EQUAL_INT(0, entity2.getID());
    TEST_ASSERT_EQUAL_INT(2, entity2.getVersion());
    TEST_ASSERT_EQUAL_INT(1, entityRegistry.getSize());

    entityRegistry.remove(entity2);
    entityRegistry.remove(entity2);
    entityRegistry.remove(entity);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_entity_registry_add);
    RUN_TEST(test_entity_registry_remove);
    return UNITY_END();
}