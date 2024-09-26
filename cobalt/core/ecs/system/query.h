/**
 * @file query.h
 * @brief A Query iterates over entities with specific components in a given World.
 * @author Tomás Marques
 * @date 27-01-2024
 */

#pragma once

#include "core/ecs/entity/registry.h"
#include "core/ecs/system/parameter.h"

namespace cobalt {
    namespace core::ecs {
        class ResourceRegistry;
        class SystemManager;

        /**
         * @brief A Query iterates over entities with specific components in a given World.
         * @tparam Components... The components to query for. Must be reference types and be registered in the world.
         */
        template <typename... Components>
        class Query : SystemParameter {
            static_assert((std::is_reference<Components>::value && ...), "All component types must be reference types.");

            public:
            /**
             * @brief Creates a new Query.
             * @param entityRegistry The entity registry that the query will run on.
             * @param resourceRegistry The resource registry that the query will run on. Unused.
             * @param systemManager The system manager that the query will run on. Unused.
             * @param eventManager The event manager that the query will run on. Unused.
             */
            explicit Query(EntityRegistry& entityRegistry, ResourceRegistry& resourceRegistry, SystemManager& systemManager,
                           EventManager& eventManager) noexcept
                : SystemParameter(entityRegistry, resourceRegistry, systemManager, eventManager),
                  componentTuples(entityRegistry.getMany<Components...>()) {
                Component::validate<std::remove_const_t<std::remove_reference_t<Components>>...>();
            }
            /**
             * @brief Default destructor.
             */
            ~Query() noexcept = default;

            /**
             * @brief Iterator for easy access to the queried entities.
             * Example:
             *
             *          for (auto [position, velocity] : myQuery) {
             *              position.x += velocity.x;
             *              position.y += velocity.y;
             *          }
             *          // Do something with the updated components.
             */
            class Iterator {
                public:
                explicit Iterator(std::tuple<Components...>* ptr) : ptr(ptr) {}

                std::tuple<Components...>& operator*() const { return *ptr; }
                std::tuple<Components...>* operator->() { return ptr; }
                Iterator& operator++() {
                    ptr++;
                    return *this;
                }
                Iterator operator++(int) {
                    Iterator tmp = *this;
                    ++(*this);
                    return tmp;
                }
                friend bool operator==(const Iterator& a, const Iterator& b) { return a.ptr == b.ptr; }
                friend bool operator!=(const Iterator& a, const Iterator& b) { return a.ptr != b.ptr; }

                private:
                std::tuple<Components...>* ptr;
            };
            Iterator begin() { return Iterator(&componentTuples[0]); }
            Iterator end() { return Iterator(&componentTuples[0] + componentTuples.size()); }

            private:
            std::vector<std::tuple<Components...>> componentTuples;  ///< The tuples of components for each entity.
        };

        /**
         * @brief A Query iterates over entities with specific components in a given World. This version of the Query is a specialization for const
         * the inclusion of an Entity reference in the query. Each one of the entities owns the queried components.
         * @tparam Components... The components to query for. Must be reference types and be registered in the world.
         */
        template <typename... Components>
        class Query<const Entity&, Components...> : SystemParameter {
            static_assert((std::is_reference<Components>::value && ...), "All component types must be reference types.");

            public:
            /**
             * @brief Creates a new Query.
             * @param entityRegistry The entity registry that the query will run on.
             * @param resourceRegistry The resource registry that the query will run on. Unused.
             * @param systemManager The system manager that the query will run on. Unused.
             * @param eventManager The event manager that the query will run on. Unused.
             */
            explicit Query(EntityRegistry& entityRegistry, ResourceRegistry& resourceRegistry, SystemManager& systemManager,
                           EventManager& eventManager) noexcept
                : SystemParameter(entityRegistry, resourceRegistry, systemManager, eventManager),
                  componentTuples(entityRegistry.getWithEntity<Components...>()) {}
            /**
             * @brief Default destructor.
             */
            ~Query() noexcept = default;

            /**
             * @brief Iterator for easy access to the queried entities.
             * Example:
             *
             *          for (auto [position, velocity] : myQuery) {
             *              position.x += velocity.x;
             *              position.y += velocity.y;
             *          }
             *          // Do something with the updated components.
             */
            class Iterator {
                public:
                explicit Iterator(std::tuple<const Entity&, Components...>* ptr) : ptr(ptr) {}

                std::tuple<const Entity&, Components...>& operator*() const { return *ptr; }
                std::tuple<const Entity&, Components...>* operator->() { return ptr; }
                Iterator& operator++() {
                    ptr++;
                    return *this;
                }
                Iterator operator++(int) {
                    Iterator tmp = *this;
                    ++(*this);
                    return tmp;
                }
                friend bool operator==(const Iterator& a, const Iterator& b) { return a.ptr == b.ptr; }
                friend bool operator!=(const Iterator& a, const Iterator& b) { return a.ptr != b.ptr; }

                private:
                std::tuple<const Entity&, Components...>* ptr;
            };
            Iterator begin() { return Iterator(&componentTuples[0]); }
            Iterator end() { return Iterator(&componentTuples[0] + componentTuples.size()); }

            private:
            std::vector<std::tuple<const Entity&, Components...>> componentTuples;  ///< The tuples of components for each entity.
        };
    }  // namespace core::ecs
}  // namespace cobalt