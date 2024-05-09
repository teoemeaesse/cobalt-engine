/**
 * @file log.h
 * @brief Logging utilities using spdlog.
 * @author Tomás Marques
 * @date 29-11-2023
 */

#pragma once

#include <memory>

#include "spdlog/spdlog.h"

namespace cobalt {
    namespace core {
        /**
         * @brief Singleton class to manage logging using spdlog (should be thread-safe). Has 3 loggers: core, engine and editor.
         */
        class Log {
            public:
            /**
             * @brief Initializes the loggers.
             */
            static void init();

            /**
             * @brief Get the core logger.
             * @return Shared pointer to the core logger.
             */
            inline static std::shared_ptr<spdlog::logger>& getCoreLogger() { return coreLogger; }
            /**
             * @brief Get the engine logger.
             * @return Shared pointer to the engine logger.
             */
            inline static std::shared_ptr<spdlog::logger>& getEngineLogger() { return engineLogger; }
            /**
             * @brief Get the editor logger.
             * @return Shared pointer to the editor logger.
             */
            inline static std::shared_ptr<spdlog::logger>& getEditorLogger() { return editorLogger; }

            private:
            static std::shared_ptr<spdlog::logger> coreLogger;    ///< Core logger. Should only be used by the core module.
            static std::shared_ptr<spdlog::logger> engineLogger;  ///< Engine logger. Should only be used by the engine module.
            static std::shared_ptr<spdlog::logger> editorLogger;  ///< Editor logger. Should only be used by the editor module.
        };
    }  // namespace core
}  // namespace cobalt

#define CB_CORE_TRACE(...) ::cobalt::core::Log::getCoreLogger()->trace(__VA_ARGS__)
#define CB_CORE_INFO(...) ::cobalt::core::Log::getCoreLogger()->info(__VA_ARGS__)
#define CB_CORE_WARN(...) ::cobalt::core::Log::getCoreLogger()->warn(__VA_ARGS__)
#define CB_CORE_ERROR(...) ::cobalt::core::Log::getCoreLogger()->error(__VA_ARGS__)

#define CB_EDITOR_TRACE(...) ::cobalt::core::Log::getEditorLogger()->trace(__VA_ARGS__)
#define CB_EDITOR_INFO(...) ::cobalt::core::Log::getEditorLogger()->info(__VA_ARGS__)
#define CB_EDITOR_WARN(...) ::cobalt::core::Log::getEditorLogger()->warn(__VA_ARGS__)
#define CB_EDITOR_ERROR(...) ::cobalt::core::Log::getEditorLogger()->error(__VA_ARGS__)

#define CB_TRACE(...) ::cobalt::core::Log::getEngineLogger()->trace(__VA_ARGS__)
#define CB_INFO(...) ::cobalt::core::Log::getEngineLogger()->info(__VA_ARGS__)
#define CB_WARN(...) ::cobalt::core::Log::getEngineLogger()->warn(__VA_ARGS__)
#define CB_ERROR(...) ::cobalt::core::Log::getEngineLogger()->error(__VA_ARGS__)