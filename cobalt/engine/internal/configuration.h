// Created by tomas on
// 07-12-2023

#pragma once

#include "core/pch.h"

namespace cobalt {
    namespace engine {
        class ConfigurationException : public std::exception {
            public:
            ConfigurationException(const std::string& key, const std::string& typeName) {
                message = std::string("Failed to cast value of key '" + key + "' to type '" + typeName + "'");
            }
            const char* what() const noexcept override { return message.c_str(); }

            private:
            std::string message;
        };

        class Configuration {
            public:
            /** @brief: Create a configuration from a file.
             * @param path: The path to the file.
             * @return: The configuration.
             */
            explicit Configuration(const core::io::Path& path);
            /** @brief: Create an empty configuration.
             * @return: The configuration.
             */
            Configuration() = default;
            /** @brief: Destroy the configuration.
             */
            ~Configuration() = default;

            /** @brief: Set a value in the configuration.
             * @param key: The key to set the value for.
             * @param value: The value to set.
             */
            template <typename T>
            void set(const std::string& key, const T& value) {
                checkType<T>();
                entries[key] = value;
            }
            /** @brief: Get a value from the configuration.
             * @param key: The key to get the value for.
             * @return: The value.
             */
            template <typename T>
            const T get(std::string& key) const {
                checkType<T>();
                auto it = entries.find(key);
                if (it != entries.end()) {
                    try {
                        return std::any_cast<T>(it->second);
                    } catch (const std::bad_any_cast& e) {
                        throw ConfigurationException(key, typeid(T).name());
                    }
                } else {
                    throw ConfigurationException(key, typeid(T).name());
                }
            }
            /** @brief: Get a value from the configuration.
             * @param key: The key to get the value for.
             * @return: The value.
             */
            template <typename T>
            const T get(const char* key) const {
                std::string keyString(key);
                return get<T>(keyString);
            }
            /** @brief: Check if the configuration has a value for a key.
             * @param key: The key to check.
             * @return: True if the configuration has a value for the key, false
             * otherwise.
             */
            const bool has(const std::string& key) const;

            /** @brief: Write the configuration to a file as JSON.
             * @param path: The path to write the configuration to.
             */
            void serialize(const core::io::Path& path) const;
            /** @brief: Merge another configuration into this one.
             * Overrides values in this configuration with values from the other
             * configuration.
             * @param other: The other configuration.
             */
            void merge(const Configuration& other);
            /** @brief: Log the configuration to the console.
             */
            void log() const;

            private:
            UMap<std::string, std::any> entries;

            /** @brief: Check if a type is supported.
             * @param T: The type to check.
             */
            template <typename T>
            static void checkType() {
                static_assert(std::is_same<T, int>::value || std::is_same<T, float>::value || std::is_same<T, double>::value ||
                                  std::is_same<T, long>::value || std::is_same<T, long long>::value || std::is_same<T, uint>::value ||
                                  std::is_same<T, unsigned long>::value || std::is_same<T, unsigned long long>::value ||
                                  std::is_same<T, bool>::value || std::is_same<T, std::string>::value || std::is_same<T, std::any>::value,
                              "Unsupported type");
            }
        };
    }  // namespace engine
}  // namespace cobalt