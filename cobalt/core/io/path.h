/**
 * @file path.h
 * @brief A class representing a path to a filesystem object, providing a high-level
 *        interface to handle file system paths more easily.
 * @author Tomás Marques
 * @date 01-12-2023
 */

#pragma once

#include <filesystem>
#include <string>

namespace cobalt {
    namespace core::io {
        /**
         * @brief This class encapsulates a filesystem path, providing utility functions to interact with it. Essentially a wrapper around
         * std::filesystem::path.
         */
        class Path {
            public:
            /**
             * @brief Constructs a Path from a string.
             * @param path A string representing the Path.
             * @param relative If true, treats the path as relative; otherwise, it is treated as absolute. True by default.
             */
            Path(const std::string& path, const bool relative);

            /**
             * @brief Constructs a Path from a C-string representing the path.
             * @param path A C-string representing the Path.
             * @param relative If true, treats the path as relative; otherwise, it is treated as absolute. True by default.
             */
            Path(const char* path, const bool relative);
            /**
             * @brief Default destructor.
             */
            ~Path() = default;

            /**
             * @brief Checks if the Path points to an existing filesystem object (file or directory).
             * @return True if the filesystem object exists at the Path, false otherwise.
             */
            const bool exists() const;

            /**
             * @brief Checks if the Path points to a regular file.
             * @return True if the Path points to a file, false otherwise.
             */
            const bool isFile() const;

            /**
             * @brief Checks if the Path points to a directory.
             * @return True if the Path points to a directory, false otherwise.
             */
            const bool isDirectory() const;

            /**
             * @brief Returns the file extension of the Path, if any.
             * @return The file extension as a string (without the dot), or an empty string if there is none.
             */
            const std::string getExtension() const;

            /**
             * @brief Returns the file name from the Path.
             * @return The file name as a string.
             */
            const std::string getFileName() const;

            /**
             * @brief Returns the file name without its extension.
             * @return The file name without the extension.
             */
            const std::string getFileNameWithoutExtension() const;

            /**
             * @brief Returns the directory part of the Path, without the file name.
             * @return The absolute path of the directory containing the file or directory the Path points to.
             */
            const std::string getDirectory() const;

            /**
             * @brief Returns the string representation of the absolute path.
             * @return The string representation of the absolute path.
             */
            const std::string getPath() const;

            /**
             * @brief Concatenates this Path with another Path and returns the resulting Path.
             * @param other The Path to concatenate.
             * @return A new Path representing the concatenated Path.
             */
            Path operator+(const Path& other) const;

            /**
             * @brief Concatenates this Path with another Path represented as a string and returns the resulting Path.
             * @param other A string representing the Path to concatenate.
             * @return The concatenated Path.
             */
            Path operator+(const std::string& other) const;

            /**
             * @brief Concatenates another Path with this Path.
             * @param other The Path to concatenate.
             * @return A reference to this Path after concatenation.
             */
            Path& operator+=(const Path& other);

            /**
             * @brief Concatenates the other Path represented as a string with this Path.
             * @param other A string representing the Path to concatenate.
             * @return A reference to this Path after concatenation.
             */
            Path& operator+=(const std::string& other);

            private:
            std::filesystem::path fsPath;  ///< Internal std::filesystem::path object used to manage filesystem paths.
        };
    }  // namespace core::io
}  // namespace cobalt
