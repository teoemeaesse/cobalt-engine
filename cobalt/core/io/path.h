//
// Created by tomas on 01-12-2023.
//

#pragma once

#include <filesystem>

#include "core/types/types.h"


namespace cobalt {
    namespace core {
        /* A class representing a path to a file or directory.
         * Just a wrapper around std::filesystem::path.
         */
        class Path {
            public:
            /* Creates a path from the given string.
             * @param path: The string represenation of the path.
             * @return: The path.
             */
            Path(std::string& path, bool relative);
            /* Creates a path from the given string.
             * @param path: The string represenation of the path.
             * @return: The path.
             */
            Path(const char* path, bool relative);
            /* Destroys the path.
             */
            ~Path() = default;

            /* Checks if there is a directory or file at the path destination.
             * @return: True if the path exists, false otherwise.
             */
            const bool exists() const;
            /* Checks if the path is a file.
             * @return: True if the path is to a file, false otherwise.
             */
            const bool isFile() const;
            /* Checks if the path is a directory.
             * @return: True if the path is to a directory, false otherwise.
             */
            const bool isDirectory() const;
            /* Returns the file extension of the path.
             * @return: The file extension.
             */
            const std::string getExtension() const;
            /* Returns the file name of the path.
             * @return: The file name.
             */
            const std::string getFileName() const;
            /* Returns the file name of the path without the extension.
             * @return: The file name without the extension.
             */
            const std::string getFileNameWithoutExtension() const;
            /* Returns the containing directory of the path.
             * e.g. Path("foo/bar") -> "/home/user/cobalt/foo"
             * @return: The absoulte path of the directory containing.
             */
            const std::string getDirectory() const;
            /* Returns the string representation of the absolute path.
             * @return: The string representation of the absolute path.
             */
            const std::string getPath() const;

            /* Overloads the + operator to concatenate two paths.
             * e.g. Path("foo") + Path("bar") = Path("foo/bar")
             * @param other: The other path to concatenate.
             * @return: The concatenated path.
             */
            Path operator+(const Path& other) const;

            private:
            std::filesystem::path fsPath;   // The path.
        };
    }
}