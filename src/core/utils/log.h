//
// Created by tomas on 29-11-2023.
//

#pragma once

#include <memory>

#include "spdlog/spdlog.h"


namespace cobalt {
    class Log {
    public:
    static void init();

    inline static std::shared_ptr<spdlog::logger> &getCoreLogger() { return coreLogger; }
    inline static std::shared_ptr<spdlog::logger> &getEngineLogger() { return engineLogger; }

    private:
    static std::shared_ptr<spdlog::logger> coreLogger;
    static std::shared_ptr<spdlog::logger> engineLogger;
    
    };
}

#define CB_CORE_TRACE(...)  ::cobalt::Log::getCoreLogger()->trace(__VA_ARGS__)
#define CB_CORE_INFO(...)   ::cobalt::Log::getCoreLogger()->info(__VA_ARGS__)
#define CB_CORE_WARN(...)   ::cobalt::Log::getCoreLogger()->warn(__VA_ARGS__)
#define CB_CORE_ERROR(...)  ::cobalt::Log::getCoreLogger()->error(__VA_ARGS__)

#define CB_TRACE(...)  ::cobalt::Log::getEngineLogger()->trace(__VA_ARGS__)
#define CB_INFO(...)   ::cobalt::Log::getEngineLogger()->info(__VA_ARGS__)
#define CB_WARN(...)   ::cobalt::Log::getEngineLogger()->warn(__VA_ARGS__)
#define CB_ERROR(...)  ::cobalt::Log::getEngineLogger()->error(__VA_ARGS__)