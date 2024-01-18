//
// Created
// by
// tomas
// on
// 07-12-2023.
//

#pragma once

#include "core/io/path.h"

namespace cobalt {
    namespace core {
        class File {
            public:
            /** @brief: Create a file from a path.
             * @param path: The path to the file.
             * @return: The file.
             */
            explicit File(const Path& path);
            /** @brief: Destroy the file.
             */
            ~File() = default;

            /** @brief: Read the contents of the file.
             * @return: The contents.
             */
            std::string read() const;
            /** @brief: Write to the file.
             * @param content: The content to write.
             */
            void write(const std::string& content) const;

            /** @brief: Get the path to the file.
             * @return: The path.
             */
            const Path& getPath() const;
            /** @brief: Get the size of the file.
             * @return: The size.
             */
            uint64_t getSize() const;

            /** @brief: Check if the file exists.
             * @return: True if the file exists, false otherwise.
             */
            bool exists() const;
            /** @brief: Check if the file is a directory.
             * @return: True if the file is a directory, false otherwise.
             */
            bool isDirectory() const;
            /** @brief: Check if the file is a regular file.
             * @return: True if the file is a regular file, false otherwise.
             */
            bool isRegularFile() const;
            /** @brief: Check if the file is readable.
             * @return: True if the file is readable, false otherwise.
             */
            bool isReadable() const;
            /** @brief: Check if the file is writable.
             * @return: True if the file is writable, false otherwise.
             */
            bool isWritable() const;

            private:
            Path path;
        };
    }  // namespace core
}  // namespace
   // cobalt