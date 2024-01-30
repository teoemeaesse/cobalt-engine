// Created by tomas on
// 27-01-2024

#pragma once

#include "core/ecs/world.h"

namespace cobalt {
    namespace core::ecs {
        template <typename... Components>
        class Query {
            static_assert((std::is_reference<Components>::value && ...), "All component types must be reference types.");

            public:
            Query(const World& world) noexcept : componentTuples(world.get<Components...>()) {}

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