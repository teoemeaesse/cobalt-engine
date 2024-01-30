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

            class Proxy {
                public:
                Proxy(const Tuple<Components...>& tuple) : tuple(tuple) {}

                template <typename Comp>
                Comp& get() const {
                    return std::get<Comp>(tuple);
                }

                private:
                const Tuple<Components...>& tuple;
            };

            class Iterator {
                public:
                Iterator(typename std::vector<Tuple<Components...>>::iterator it) : it(it) {}

                Iterator& operator++() {
                    ++it;
                    return *this;
                }

                bool operator!=(const Iterator& other) const { return it != other.it; }

                Proxy operator*() const { return Proxy(*it); }

                private:
                typename std::vector<Tuple<Components...>>::iterator it;
            };

            Iterator begin() { return Iterator(componentTuples.begin()); }

            Iterator end() { return Iterator(componentTuples.end()); }

            private:
            typename std::vector<Tuple<Components...>> componentTuples;
        };
    }  // namespace core::ecs
}  // namespace cobalt