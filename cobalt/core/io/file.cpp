//
// Created
// by
// tomas
// on
// 07-12-2023.
//

#include "core/io/file.h"

#include <filesystem>
#include <fstream>
#include <sstream>

namespace cobalt {
    namespace core {
        File::File(const Path& path) : path(path) {}

        std::string File::read() const {
            std::ifstream file(path.getPath());
            std::stringstream stream;
            stream << file.rdbuf();
            return stream.str();
        }

        void File::write(const std::string& content) const {
            std::ofstream file(path.getPath());
            file << content;
        }

        const Path& File::getPath() const { return path; }

        uint64_t File::getSize() const { return std::filesystem::file_size(path.getPath()); }

        bool File::exists() const { return std::filesystem::exists(path.getPath()); }

        bool File::isDirectory() const { return std::filesystem::is_directory(path.getPath()); }

        bool File::isRegularFile() const { return std::filesystem::is_regular_file(path.getPath()); }

        bool File::isReadable() const {
            std::ifstream file(path.getPath());
            return file.is_open() && file.good();
        }

        bool File::isWritable() const {
            std::ofstream file(path.getPath());
            return file.is_open() && file.good();
        }
    }  // namespace core
}  // namespace
   // cobalt