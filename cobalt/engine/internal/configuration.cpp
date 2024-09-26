// Created by tomas on
// 07-12-2023

#include "engine/internal/configuration.h"

#include "core/core.h"

namespace cobalt {
    namespace engine {
        Configuration::Configuration(const core::io::Path& path) {
            CB_INFO("Loading configuration from '{}'", path.getPath());
            std::ifstream file(path.getPath());
            nlohmann::json json;
            try {
                file >> json;
            } catch (const nlohmann::json::parse_error& e) {
                CB_ERROR("Failed to parse configuration file '{}': {}", path.getPath(), e.what());
                return;
            }
            file.close();
            for (auto it = json.begin(); it != json.end(); ++it) {
                if (it->is_number_integer()) {
                    set(it.key(), it->get<int>());
                } else if (it->is_number_float()) {
                    set(it.key(), it->get<float>());
                } else if (it->is_number()) {
                    set(it.key(), it->get<double>());
                } else if (it->is_boolean()) {
                    set(it.key(), it->get<bool>());
                } else if (it->is_string()) {
                    set(it.key(), it->get<std::string>());
                } else {
                    throw ConfigurationException(it.key(), "unknown");
                }
            }
            log();
        }

        const bool Configuration::has(const std::string& key) const { return entries.find(key) != entries.end(); }

        void Configuration::serialize(const core::io::Path& path) const {
            CB_INFO("Serializing configuration to '{}'", path.getPath());
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

        void Configuration::merge(const Configuration& other) {
            for (auto& entry : other.entries) {
                if (has(entry.first)) {
                    if (entry.second.type() != entries.at(entry.first).type()) {
                        throw ConfigurationException(entry.first, "unknown");
                    }
                }
                set(entry.first, entry.second);
            }
        }

        void Configuration::log() const {
            CB_INFO("Configuration:");
            for (const auto& entry : entries) {
                if (entry.second.type() == typeid(int)) {
                    CB_INFO("  {} = {}", entry.first, std::any_cast<int>(entry.second));
                } else if (entry.second.type() == typeid(float)) {
                    CB_INFO("  {} = {}", entry.first, std::any_cast<float>(entry.second));
                } else if (entry.second.type() == typeid(double)) {
                    CB_INFO("  {} = {}", entry.first, std::any_cast<double>(entry.second));
                } else if (entry.second.type() == typeid(long)) {
                    CB_INFO("  {} = {}", entry.first, std::any_cast<long>(entry.second));
                } else if (entry.second.type() == typeid(long long)) {
                    CB_INFO("  {} = {}", entry.first, std::any_cast<long long>(entry.second));
                } else if (entry.second.type() == typeid(uint)) {
                    CB_INFO("  {} = {}", entry.first, std::any_cast<uint>(entry.second));
                } else if (entry.second.type() == typeid(unsigned long)) {
                    CB_INFO("  {} = {}", entry.first, std::any_cast<unsigned long>(entry.second));
                } else if (entry.second.type() == typeid(unsigned long long)) {
                    CB_INFO("  {} = {}", entry.first, std::any_cast<unsigned long long>(entry.second));
                } else if (entry.second.type() == typeid(bool)) {
                    CB_INFO("  {} = {}", entry.first, std::any_cast<bool>(entry.second));
                } else if (entry.second.type() == typeid(std::string)) {
                    CB_INFO("  {} = {}", entry.first, std::any_cast<std::string>(entry.second));
                } else {
                    throw ConfigurationException(entry.first, "unknown");
                }
            }
        }
    }  // namespace engine
}  // namespace cobalt