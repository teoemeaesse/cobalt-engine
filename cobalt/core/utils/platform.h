/**
 * @file log.h
 * @brief Platform information utilities.
 * @author Tomás Marques
 * @date 25-12-2023
 */

#pragma once

// No win32 support
#if defined(_WIN64)
#define PLATFORM_NAME "Windows"
#elif defined(__APPLE__) && defined(__MACH__)
#include <TargetConditionals.h>
#if TARGET_OS_MAC
#define PLATFORM_NAME "MacOS"
#endif
#elif defined(__unix__)
#define PLATFORM_NAME "Unix-like"
#else
#error "Platform not supported"
#endif

#include <cstring>

#include "core/utils/log.h"

namespace cobalt {
    namespace core {
        /**
         * @brief Class representing the current platform.
         */
        class Platform {
            public:
            /**
             * @brief Get the name of the current platform.
             * @return The name of the current platform.
             */
            inline static const char* getName() { return PLATFORM_NAME; }

            /**
             * @brief Log the current platform.
             */
            inline static void log() { CB_CORE_INFO("Running on {0}", getName()); }

            /**
             * @brief Check if the platform is compatible with cobalt.
             */
            inline static void checkCompatibility() {
                if (isWindows()) {
                    CB_CORE_ERROR("Windows is not yet supported");
                    exit(1);
                }
                if (sizeof(size_t) < sizeof(uint64_t)) {
                    CB_CORE_INFO("32-bit systems are not supported");
                    exit(1);
                }
            }

            /**
             * @brief Check if the platform is Windows.
             * @return True if the platform is Windows, false otherwise.
             */
            inline static bool isWindows() { return strcmp(getName(), "Windows") == 0; }

            /**
             * @brief Check if the platform is macos.
             * @return True if the platform is macos, false otherwise.
             */
            inline static bool isMacOS() { return strcmp(getName(), "MacOS") == 0; }

            /**
             * @brief Check if the platform is unix-like.
             * @return True if the platform is unix-like, false otherwise.
             */
            inline static bool isUnixLike() { return strcmp(getName(), "Unix-like") == 0; }
        };
    }  // namespace core
}  // namespace cobalt