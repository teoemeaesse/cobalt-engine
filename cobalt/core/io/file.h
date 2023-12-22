//
// Created by tomas on 07-12-2023.
//

#pragma once

#include "core/io/path.h"


namespace cobalt {
    namespace core {
        class File {
            public:
            /* Create a file from a path.
             * @param path: The path to the file.
             * @return: The file.
             */
            explicit File(const Path& path);
            /* Destroy the file.
             */
            ~File() = default;

            /* Read the contents of the file.
             * @return: The contents.
             */
            std::string read() const;
            /* Write to the file.
             * @param content: The content to write.
             */
            void write(const std::string& content) const;

            /* Get the path to the file.
             * @return: The path.
             */
            const Path& getPath() const;
            /* Get the size of the file.
             * @return: The size.
             */
            uint64 getSize() const;

            /* Check if the file exists.
             * @return: True if the file exists, false otherwise.
             */
            bool exists() const;
            /* Check if the file is a directory.
             * @return: True if the file is a directory, false otherwise.
             */
            bool isDirectory() const;
            /* Check if the file is a regular file.
             * @return: True if the file is a regular file, false otherwise.
             */
            bool isRegularFile() const;
            /* Check if the file is readable.
             * @return: True if the file is readable, false otherwise.
             */
            bool isReadable() const;
            /* Check if the file is writable.
             * @return: True if the file is writable, false otherwise.
             */
            bool isWritable() const;

            private:
            Path path;
        };
    }
}