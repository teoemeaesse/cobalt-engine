/**
 * @file file.h
 * @brief File class to handle file I/O.
 * @author Tomás Marques
 * @date 07-12-2023
 */

#pragma once

#include "core/io/path.h"

namespace cobalt {
    namespace core::io {
        /**
         * @brief A class that encapsulates file operations.
         * The File class provides a high-level interface to perform various operations on files and directories, such as reading from and writing to
         * files, and checking their properties.
         */
        class File {
            public:
            /**
             * @brief Constructor that creates a File at the specified path.
             * The actual file or directory does not need to exist at the time of this object's creation.
             * @param path A Path to the file or directory.
             */
            explicit File(const Path& path);
            /**
             * @brief Default destructor.
             */
            ~File() = default;

            /**
             * @brief Reads the entire contents of the file as a string.
             * The file must exist and be readable.
             * @return A string containing the contents of the file.
             */
            std::string read() const;

            /**
             * @brief Writes the specified content to the file..
             * The file does not need to exist; if it does not, it will be created. However, the directory containing the file must exist and be
             * writable.
             * @param content The content to write to the file.
             */
            void write(const std::string& content) const;

            /**
             * @brief Gets the Path to this file.
             * @return The file's Path.
             */
            const Path& getPath() const;

            /**
             * @brief Gets the size of the file in bytes.
             * The file must exist and be a regular file.
             * @return The size of the file in bytes;
             */
            uint64_t getSize() const;

            /**
             * @brief Checks if the file exists.
             * @return True if the file exists, false otherwise.
             */
            bool exists() const;

            /**
             * @brief Checks if the file is a directory.
             * @return True if the file is a directory, false otherwise.
             */
            bool isDirectory() const;

            /**
             * @brief Checks if the file is a regular file and not a directory or any other type of file system object.
             * @return True if the file is a regular file, false otherwise.
             */
            bool isRegularFile() const;

            /**
             * @brief Checks if the file is readable by the current user.
             * @return True if the file is readable, false otherwise.
             */
            bool isReadable() const;

            /**
             * @brief Checks if the file is writable by the current user.
             * @return True if the file is writable, false otherwise.
             */
            bool isWritable() const;

            private:
            Path path;  ///< The path of the file represented by this File object.
        };
    }  // namespace core::io
}  // namespace cobalt