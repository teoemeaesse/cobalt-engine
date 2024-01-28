// Created by tomas on
// 18-01-2024

#include "core/ecs/component/component.h"

#include <cxxabi.h>

namespace cobalt {
    namespace core::ecs {
        Component::Component(const ID id) noexcept : id(id) {}

        static const std::string demangle(const char* name) noexcept {
            int status = 42;
            std::unique_ptr<char, void (*)(void*)> res{abi::__cxa_demangle(name, nullptr, nullptr, &status), std::free};
            return (status == 0) ? res.get() : name;
        }

        const Component::Type Component::getType() noexcept {
            static const Component::Type type = typeid(*this).hash_code();
            return type;
        }

        const std::string& Component::getTypeName() noexcept {
            static const std::string typeName = demangle(typeid(*this).name());
            return typeName;
        }

        template <typename T>
        const Component::Type Component::getType() noexcept {
            static const Component::Type type = typeid(T).hash_code();
            return type;
        }

        template <typename T>
        const std::string& Component::getTypeName() noexcept {
            static const std::string typeName = demangle(typeid(T).name());
            return typeName;
        }

    }  // namespace core::ecs
}  // namespace cobalt