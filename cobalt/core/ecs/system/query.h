// Created by tomas on
// 27-01-2024

#pragma once

namespace cobalt {
    namespace core::ecs {
        class ECSWorld;

        template <typename... Components>
        class QueryMut {
            public:
            QueryMut(ECSWorld& world) noexcept;
            ~QueryMut() = default;

            private:
            ECSWorld& world;
        };

        template <typename... Components>
        class Query {
            public:
            Query(const ECSWorld& world) noexcept;
            ~Query() = default;

            private:
            const ECSWorld& world;
        };
    }  // namespace core::ecs
}  // namespace cobalt