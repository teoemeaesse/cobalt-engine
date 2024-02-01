// Created by tomas on
// 27-01-2024

#pragma once

#include "core/ecs/world.h"

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
             * @param world: The world that the query will run on.
             * @return: A new query.
             */
            explicit Query(const World& world) noexcept : componentTuples(world.get<Components...>()) {}
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
                Iterator(Tuple<Components...>* ptr) : ptr(ptr) {}

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
    }  // namespace core::ecs
}  // namespace cobalt