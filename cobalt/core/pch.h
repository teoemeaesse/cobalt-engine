/**
 * @file pch.h
 * @brief Precompiled main library interfaces for the Cobalt core, providing various utilities such as STL and OpenGL wrappers.
 * @author Tomás Marques
 * @date 22-12-2023
 */

#pragma once

#include <cxxabi.h>
#include <signal.h>
#include <time.h>

#include <algorithm>
#include <any>
#include <bitset>
#include <cstddef>
#include <cstring>
#include <deque>
#include <fstream>
#include <iostream>
#include <limits>
#include <list>
#include <memory>
#include <optional>
#include <queue>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <string>
#include <tuple>
#include <type_traits>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "core/gl/gl.h"
#include "core/io/file.h"
#include "core/io/path.h"
#include "core/memory/arena.h"
#include "core/memory/heap.h"
#include "core/memory/pool.h"
#include "core/utils/color.h"
#include "core/utils/log.h"
#include "core/utils/platform.h"
#include "json/json.hpp"

/**
 * @brief Macro to create a new scoped pointer.
 */
#define CB_CREATE_SCOPE(T, ...) std::unique_ptr<T>(new T(__VA_ARGS__))
/**
 * @brief Macro to create a new shared pointer.
 */
#define CB_CREATE_SHARED(T, ...) std::shared_ptr<T>(new T(__VA_ARGS__))

/**
 * @brief The Cobalt namespace encapsulates all functionality of the Cobalt engine.
 */
namespace cobalt {
    /**
     * @brief Scoped pointer for automatic resource management.
     * @tparam T Type of the object managed by the scope.
     */
    template <typename T>
    using Scope = std::unique_ptr<T>;
    /**
     * @brief Creates a new scoped pointer.
     * @tparam T Type of the object managed by the scope.
     * @tparam Args Types of the arguments to pass to the constructor.
     * @param args Arguments to pass to the constructor.
     * @return The new scoped pointer.
     */
    template <typename T, typename... Args>
    constexpr Scope<T> CreateScope(Args&&... args) {
        return std::make_unique<T>(std::forward<Args>(args)...);
    }
    /**
     * @brief Shared pointer for shared resource management.
     * @tparam T Type of the object managed by the shared pointer.
     */
    template <typename T>
    using Shared = std::shared_ptr<T>;
    /**
     * @brief Creates a new shared pointer.
     * @tparam T Type of the object managed by the shared pointer.
     * @tparam Args Types of the arguments to pass to the constructor.
     * @param args Arguments to pass to the constructor.
     * @return The new shared pointer.
     */
    template <typename T, typename... Args>
    constexpr Shared<T> CreateShared(Args&&... args) {
        return std::make_shared<T>(std::forward<Args>(args)...);
    }
    /**
     * @brief Reference wrapper for reference management.
     * @tparam T Type of the object managed by the reference wrapper.
     */
    template <typename T>
    using Wrap = std::reference_wrapper<T>;
    /**
     * @brief Const reference wrapper for reference management.
     * @tparam T Type of the object managed by the reference wrapper.
     */
    template <typename T>
    using ConstWrap = std::reference_wrapper<const T>;
    /**
     * @brief Creates a new reference wrapper.
     * @tparam T Type of the object managed by the reference wrapper.
     * @param ref Reference to wrap.
     * @return The new reference wrapper.
     */
    template <typename T>
    constexpr Wrap<T> CreateWrap(T& ref) {
        return std::ref(ref);
    }
    /**
     * @brief Creates a new const reference wrapper.
     * @tparam T Type of the object managed by the reference wrapper.
     * @param ref Reference to wrap.
     * @return The new const reference wrapper.
     */
    template <typename T>
    constexpr ConstWrap<T> CreateConstWrap(const T& ref) {
        return std::cref(ref);
    }
    /**
     * @brief Wrapper for std::unordered_map.
     * @tparam T Type of the key.
     * @tparam S Type of the value.
     */
    template <typename T, typename S>
    using UMap = std::unordered_map<T, S>;
    /**
     * @brief Wrapper for std::unordered_set.
     * @tparam T Type of the element.
     * @tparam S Type of the hash function.
     */
    template <typename T, typename S>
    using USet = std::unordered_set<T, S>;
    /**
     * @brief Wrapper for std::optional.
     * @tparam T Type of the object managed by the optional.
     */
    template <typename T>
    using Opt = std::optional<T>;
    /**
     * @brief Wrapper for std::nullopt.
     */
    inline constexpr auto& None = std::nullopt;
    /**
     * @brief Wrapper for std::tuple.
     * @tparam T Types of the elements.
     */
    template <typename... T>
    using Tuple = std::tuple<T...>;
    /**
     * @brief Wrapper for std::vector.
     * @tparam T Type of the elements.
     */
    template <typename T>
    using Vec = std::vector<T>;
    /**
     * @brief Wrapper for std::list.
     * @tparam T Type of the elements.
     */
    template <typename T>
    using List = std::list<T>;
    /**
     * @brief Wrapper for std::deque.
     * @tparam T Type of the elements.
     */
    template <typename T>
    using Deque = std::deque<T>;
    /**
     * @brief Wrapper for std::stack.
     * @tparam T Type of the elements.
     */
    template <typename T>
    using Stack = std::stack<T>;
    /**
     * @brief Wrapper for std::queue.
     * @tparam T Type of the elements.
     */
    template <typename T>
    using Queue = std::queue<T>;
    /**
     * @brief Wrapper for std::bitset.
     * @tparam N Number of bits.
     */
    template <unsigned int N>
    using Mask = std::bitset<N>;
    /**
     * @brief Wrapper for std::function.
     * @tparam T Type of the function.
     */
    template <typename T>
    using Func = std::function<T>;
    /**
     * @brief Wrapper for std::pair.
     * @tparam T Type of the first element.
     * @tparam S Type of the second element.
     */
    template <typename T, typename S>
    using Pair = std::pair<T, S>;
    /**
     * @brief Alias for an unsigned char.
     */
    using uchar = unsigned char;
    /**
     * @brief Alias for a signed 64-bit integer.
     */
    using int64 = int64_t;
    /**
     * @brief Alias for an unsigned 64-bit integer.
     */
    using uint64 = uint64_t;
    /**
     * @brief Alias for an unsigned 32-bit integer.
     */
    using uint = uint32_t;

    /**
     * @brief Removes the const and reference qualifiers from a type.
     * @tparam T Type to remove the qualifiers from.
     */
    template <typename T>
    using RemoveConstRef = std::remove_const_t<std::remove_reference_t<T>>;
    // /**
    //  * @brief Checks if a type is const qualified.
    //  * @tparam T Type to check.
    //  */
    // template <typename T>
    // struct IsConst : std::integral_constant<bool, std::is_const<T>::value || std::is_const<typename std::remove_reference<T>::type>::value> {};

    /**
     * @brief Wrapper for std::move.
     * @tparam T Type of the object.
     * @param arg Object to move.
     * @return The moved object.
     */
    template <typename T>
    constexpr typename std::remove_reference<T>::type&& Move(T&& arg) noexcept {
        return std::move(arg);
    }
    /**
     * @brief Demangles the type name string (from typeid(T).name()).
     * @param name The mangled name to demangle.
     * @return A string containing the demangled name.
     */
    static inline const std::string demangle(const char* name) noexcept {
        int status = 42;
        std::unique_ptr<char, void (*)(void*)> res{abi::__cxa_demangle(name, nullptr, nullptr, &status), std::free};
        return (status == 0) ? res.get() : name;
    }

    /**
     * @brief Namespace for numerical constants.
     *
     * This namespace includes a series of numeric limits for different data types,
     * as well as some mathematical constants.
     */
    namespace num {
        static inline constexpr uint64_t MAX_UINT64 = std::numeric_limits<uint64_t>::max();  ///< Maximum possible value for uint64_t.
        static inline constexpr int64_t MAX_INT64 = std::numeric_limits<int64_t>::max();     ///< Maximum possible value for int64_t.
        static inline constexpr uint64_t MIN_UINT64 = std::numeric_limits<uint64_t>::min();  ///< Minimum possible value for uint64_t.
        static inline constexpr int64_t MIN_INT64 = std::numeric_limits<int64_t>::min();     ///< Minimum possible value for int64_t.
        static inline constexpr uint32_t MAX_UINT32 = std::numeric_limits<uint32_t>::max();  ///< Maximum possible value for uint32_t.
        static inline constexpr int32_t MAX_INT32 = std::numeric_limits<int32_t>::max();     ///< Maximum possible value for int32_t.
        static inline constexpr uint32_t MIN_UINT32 = std::numeric_limits<uint32_t>::min();  ///< Minimum possible value for uint32_t.
        static inline constexpr int32_t MIN_INT32 = std::numeric_limits<int32_t>::min();     ///< Minimum possible value for int32_t.
        static inline constexpr float MAX_FLOAT = std::numeric_limits<float>::max();         ///< Maximum possible value for float.
        static inline constexpr float MIN_FLOAT = std::numeric_limits<float>::min();         ///< Minimum possible value for float.
        static inline constexpr double MAX_DOUBLE = std::numeric_limits<double>::max();      ///< Maximum possible value for double.
        static inline constexpr double MIN_DOUBLE = std::numeric_limits<double>::min();      ///< Minimum possible value for double.
        static inline constexpr float PI = 3.14159265358979323846f;                          ///< Value of Pi.
        static inline constexpr float TWO_PI = 6.28318530717958647692f;                      ///< Value of two times Pi.
        static inline constexpr float HALF_PI = 1.57079632679489661923f;                     ///< Value of half Pi.
        static inline constexpr float QUARTER_PI = 0.78539816339744830961f;                  ///< Value of a quarter Pi.
        static inline constexpr float E = 2.71828182845904523536f;                           ///< Euler's number.
        static inline constexpr float SQRT_2 = 1.41421356237309504880f;                      ///< Square root of 2.
        static inline constexpr float SQRT_3 = 1.73205080756887729352f;
    }  // namespace num
}  // namespace cobalt