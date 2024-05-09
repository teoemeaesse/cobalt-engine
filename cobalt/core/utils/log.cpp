/**
 * @file log.h
 * @brief Logging utilities using spdlog.
 * @author Tomás Marques
 * @date 29-11-2023
 */

#include "core/utils/log.h"

#include "spdlog/sinks/stdout_color_sinks.h"

namespace cobalt {
    namespace core {
        std::shared_ptr<spdlog::logger> Log::coreLogger;
        std::shared_ptr<spdlog::logger> Log::engineLogger;
        std::shared_ptr<spdlog::logger> Log::editorLogger;

        void Log::init() {
            spdlog::set_pattern("[%r] %^%n: %v%$");
            coreLogger = spdlog::stdout_color_mt("CORE");
            coreLogger->set_level(spdlog::level::trace);
            engineLogger = spdlog::stdout_color_mt("ENGINE");
            engineLogger->set_level(spdlog::level::trace);
            editorLogger = spdlog::stdout_color_mt("EDITOR");
            editorLogger->set_level(spdlog::level::trace);
        }
    }  // namespace core
}  // namespace cobalt