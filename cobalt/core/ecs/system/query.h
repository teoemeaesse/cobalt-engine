// Created by tomas on
// 27-01-2024

#pragma once

#include "core/ecs/entity/registry.h"

namespace cobalt {
    namespace core::ecs {
        /**
         * @brief: Interface for all queries. Just for static assertions.
         */
        class QueryInterface {
            public:
            /**
             * @brief: Default virtual destructor.
             * @return: void
             */
            virtual ~QueryInterface() noexcept = default;

            protected:
            QueryInterface() noexcept = default;
        };

        /**
         * @brief: Query class. Used to iterate over entities with specific components.
         * @tparam Components...: Components to query for. Must be reference types (use cobalt::RefMut<T> or cobalt::Ref<T>). Must be registered in
         * the world.
         */
        template <typename... Components>
        class Query : QueryInterface {
            static_assert((std::is_reference<Components>::value && ...), "All component types must be reference types.");

            public:
            /**
             * @brief: Creates a new query.
             * @param entityRegistry: The entity registry that the query will run on.
             * @return: A new query.
             */
            explicit Query(EntityRegistry& entityRegistry) noexcept : componentTuples(entityRegistry.getMany<Components...>()) {
                Component::validate<RemoveConstRef<Components>...>();
            }
            /**
             * @brief: Destroys the query.
             * @return: void
             */
            ~Query() noexcept = default;

            /**
             * @brief: Iterator for the queried entities.
             */
            class Iterator {
                public:
                explicit Iterator(Tuple<Components...>* ptr) : ptr(ptr) {}

                Tuple<Components...>& operator*() const { return *ptr; }
                Tuple<Components...>* operator->() { return ptr; }
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
                Tuple<Components...>* ptr;
            };
            Iterator begin() { return Iterator(&componentTuples[0]); }
            Iterator end() { return Iterator(&componentTuples[0] + componentTuples.size()); }

            private:
            Vec<Tuple<Components...>> componentTuples;
        };

        template <typename... Components>
        class Query<Ref<Entity>, Components...> {
            static_assert((std::is_reference<Components>::value && ...), "All component types must be reference types.");

            public:
            explicit Query(EntityRegistry& entityRegistry) noexcept : componentTuples(entityRegistry.getWithEntity<Components...>()) {}

            /**
             * @brief: Iterator for the queried entities.
             */
            class Iterator {
                public:
                Iterator(Tuple<Ref<Entity>, Components...>* ptr) : ptr(ptr) {}

                Tuple<Ref<Entity>, Components...>& operator*() const { return *ptr; }
                Tuple<Ref<Entity>, Components...>* operator->() { return ptr; }
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
                Tuple<Ref<Entity>, Components...>* ptr;
            };
            Iterator begin() { return Iterator(&componentTuples[0]); }
            Iterator end() { return Iterator(&componentTuples[0] + componentTuples.size()); }

            private:
            Vec<Tuple<Ref<Entity>, Components...>> componentTuples;
        };
    }  // namespace core::ecs
}  // namespace cobalt