//
// Created by tomas on 29-11-2023.
//

#include "core/utils/log.h"

#include "spdlog/sinks/stdout_color_sinks.h"


namespace cobalt {
    std::shared_ptr<spdlog::logger> Log::coreLogger;
    std::shared_ptr<spdlog::logger> Log::engineLogger;

    void Log::init() {
        spdlog::set_pattern("%^[%T] %n: %v%$");
        coreLogger = spdlog::stdout_color_mt("CORE");
        coreLogger->set_level(spdlog::level::trace);
        engineLogger = spdlog::stdout_color_mt("ENGINE");
        engineLogger->set_level(spdlog::level::trace);
    }
}