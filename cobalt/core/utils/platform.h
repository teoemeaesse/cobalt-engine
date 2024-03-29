// Created by tomas on
// 25-12-2023

#pragma once

// No
// win32
// support
#if defined(_WIN64)
#define PLATFORM_NAME \
    "Wi"              \
    "nd"              \
    "ow"              \
    "s"
#elif defined(__APPLE__) && defined(__MACH__)
#include <TargetConditionals.h>
#if TARGET_OS_MAC
#define PLATFORM_NAME \
    "Ma"              \
    "cO"              \
    "S"
#endif
#elif defined(__unix__)
#define PLATFORM_NAME \
    "Un"              \
    "ix"              \
    "-l"              \
    "ik"              \
    "e"
#else
#error "Platform not supported"
#endif

#include <cstring>

#include "core/utils/log.h"

namespace cobalt {
    namespace core {
        class Platform {
            public:
            /** 
             * @brief: Get the name of the platform
             * @return: The name of the platform
             */
            inline static const char* getName() { return PLATFORM_NAME; }

            inline static void log() { CB_CORE_INFO("Running on {0}", getName()); }

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
             * @brief: Check if the platform is windows
             * @return: True if the platform is windows, false otherwise
             */
            inline static bool isWindows() { return strcmp(getName(), "Windows") == 0; }

            /** 
             * @brief: Check if the platform is macos
             * @return: True if the platform is macos, false otherwise
             */
            inline static bool isMacOS() { return strcmp(getName(), "MacOS") == 0; }

            /** 
             * @brief: Check if the platform is unix-like
             * @return: True if the platform is unix-like, false otherwise
             */
            inline static bool isUnixLike() { return strcmp(getName(), "Unix-like") == 0; }
        };
    }  // namespace core
}  // namespace cobalt