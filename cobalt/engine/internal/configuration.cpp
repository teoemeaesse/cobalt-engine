//
// Created by tomas on 07-12-2023.
//

#include <fstream>

#include "json/json.hpp"

#include "engine/internal/configuration.h"


namespace cobalt {
    namespace engine {
        const bool Configuration::has(const std::string& key) const {
            return entries.find(key) != entries.end();
        }

        void Configuration::serialize(const core::Path& path) const {
            nlohmann::json json;
            for (const auto& entry : entries) {
                // Disgusting
                if (entry.second.type() == typeid(int)) {
                    json[entry.first] = std::any_cast<int>(entry.second);
                } else if (entry.second.type() == typeid(float)) {
                    json[entry.first] = std::any_cast<float>(entry.second);
                } else if (entry.second.type() == typeid(double)) {
                    json[entry.first] = std::any_cast<double>(entry.second);
                } else if (entry.second.type() == typeid(long)) {
                    json[entry.first] = std::any_cast<long>(entry.second);
                } else if (entry.second.type() == typeid(long long)) {
                    json[entry.first] = std::any_cast<long long>(entry.second);
                } else if (entry.second.type() == typeid(uint)) {
                    json[entry.first] = std::any_cast<uint>(entry.second);
                } else if (entry.second.type() == typeid(unsigned long)) {
                    json[entry.first] = std::any_cast<unsigned long>(entry.second);
                } else if (entry.second.type() == typeid(unsigned long long)) {
                    json[entry.first] = std::any_cast<unsigned long long>(entry.second);
                } else if (entry.second.type() == typeid(bool)) {
                    json[entry.first] = std::any_cast<bool>(entry.second);
                } else if (entry.second.type() == typeid(std::string)) {
                    json[entry.first] = std::any_cast<std::string>(entry.second);
                } else {
                    throw ConfigurationException(entry.first, "unknown");
                }
            }
            std::ofstream file(path.getPath());
            file << json.dump(4, ' ', true);
            file.close();
        }
    }
}