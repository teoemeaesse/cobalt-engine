//
// Created by tomas on 07-12-2023.
//

#pragma once

#include <exception>
#include <unordered_map>
#include <any>

#include "core/io/path.h"


namespace cobalt {
    namespace engine {
        class ConfigurationException : public std::exception {
        public:
            ConfigurationException(const std::string& key, const std::string& typeName) : key(key), typeName(typeName) {}
            const char* what() const noexcept override {
                std::string message = "Failed to cast value of key '" + key + "' to type '" + typeName + "'";
                return message.c_str();
            }
        private:
            std::string key;        // The key that was attempted to be casted.
            std::string typeName;   // The type that was attempted to be casted to.
        };

        class Configuration {
            public:
            /* Create a configuration from a file.
             * @param path: The path to the file.
             * @return: The configuration.
             */
            explicit Configuration(const core::Path& path);
            /* Create an empty configuration.
             * @return: The configuration.
             */
            Configuration() = default;
            /* Destroy the configuration.
             */
            ~Configuration() = default;

            /* Set a value in the configuration.
             * @param key: The key to set the value for.
             * @param value: The value to set.
             */
            template <typename T>
            void set(const std::string& key, const T& value) {
                checkType<T>();
                entries[key] = value;
            }
            /* Get a value from the configuration.
             * @param key: The key to get the value for.
             * @return: The value.
             */
            template <typename T>
            const T get(const std::string& key) const {
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
            /* Check if the configuration has a value for a key.
             * @param key: The key to check.
             * @return: True if the configuration has a value for the key, false otherwise.
             */
            const bool has(const std::string& key) const;

            /* Write the configuration to a file as JSON.
             * @param path: The path to write the configuration to.
             */
            void serialize(const core::Path& path) const;
            /* Merge another configuration into this one.
             * Overrides values in this configuration with values from the other configuration.
             * @param other: The other configuration.
             */
            void merge(const Configuration& other);
            /* Log the configuration to the console.
             */
            void log() const;

            private:
            std::unordered_map<std::string, std::any> entries;

            /* Check if a type is supported.
             * @param T: The type to check.
             */
            template <typename T>
            static void checkType() {
                static_assert(std::is_same<T, int>::value || 
                              std::is_same<T, float>::value || 
                              std::is_same<T, double>::value || 
                              std::is_same<T, long>::value ||
                              std::is_same<T, long long>::value ||
                              std::is_same<T, uint>::value || 
                              std::is_same<T, unsigned long>::value ||
                              std::is_same<T, unsigned long long>::value ||
                              std::is_same<T, bool>::value ||
                              std::is_same<T, std::string>::value ||
                              std::is_same<T, std::any>::value,
                              "Unsupported type");
            }
        };
    }
}