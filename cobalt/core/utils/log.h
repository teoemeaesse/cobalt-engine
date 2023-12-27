//
// Created by tomas on 29-11-2023.
//

#pragma once

#include <memory>

#include "spdlog/spdlog.h"


namespace cobalt {
    namespace core {
        class Log {
            public:
            static void init();

            inline static std::shared_ptr<spdlog::logger>& getCoreLogger() { return coreLogger; }
            inline static std::shared_ptr<spdlog::logger>& getEngineLogger() { return engineLogger; }
            inline static std::shared_ptr<spdlog::logger>& getEditorLogger() { return editorLogger; }

            private:
            static std::shared_ptr<spdlog::logger> coreLogger;
            static std::shared_ptr<spdlog::logger> engineLogger;
            static std::shared_ptr<spdlog::logger> editorLogger;
        };
    }
}

#define CB_CORE_TRACE(...)  ::cobalt::core::Log::getCoreLogger()->trace(__VA_ARGS__)
#define CB_CORE_INFO(...)   ::cobalt::core::Log::getCoreLogger()->info(__VA_ARGS__)
#define CB_CORE_WARN(...)   ::cobalt::core::Log::getCoreLogger()->warn(__VA_ARGS__)
#define CB_CORE_ERROR(...)  ::cobalt::core::Log::getCoreLogger()->error(__VA_ARGS__)

#define CB_EDITOR_TRACE(...)  ::cobalt::core::Log::getEditorLogger()->trace(__VA_ARGS__)
#define CB_EDITOR_INFO(...)   ::cobalt::core::Log::getEditorLogger()->info(__VA_ARGS__)
#define CB_EDITOR_WARN(...)   ::cobalt::core::Log::getEditorLogger()->warn(__VA_ARGS__)
#define CB_EDITOR_ERROR(...)  ::cobalt::core::Log::getEditorLogger()->error(__VA_ARGS__)

#define CB_TRACE(...)  ::cobalt::core::Log::getEngineLogger()->trace(__VA_ARGS__)
#define CB_INFO(...)   ::cobalt::core::Log::getEngineLogger()->info(__VA_ARGS__)
#define CB_WARN(...)   ::cobalt::core::Log::getEngineLogger()->warn(__VA_ARGS__)
#define CB_ERROR(...)  ::cobalt::core::Log::getEngineLogger()->error(__VA_ARGS__)