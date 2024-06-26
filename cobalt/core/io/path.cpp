/**
 * @file path.cpp
 * @brief A class representing a path to a filesystem object.
 * @author Tomás Marques
 * @date 01-12-2023
 */

#include "core/io/path.h"

namespace cobalt {
    namespace core::io {
        Path::Path(const std::string& path, const bool relative = true) {
            if (relative) {
                fsPath = std::filesystem::current_path().string() + "/" + path;
            } else {
                fsPath = path;
            }
        }

        Path::Path(const char* path, const bool relative = true) {
            if (relative) {
                fsPath = std::filesystem::current_path().string() + "/" + path;
            } else {
                fsPath = path;
            }
        }

        const bool Path::exists() const { return std::filesystem::exists(fsPath); }

        const bool Path::isFile() const { return std::filesystem::is_regular_file(fsPath); }

        const bool Path::isDirectory() const { return std::filesystem::is_directory(fsPath); }

        const std::string Path::getExtension() const { return fsPath.extension().string(); }

        const std::string Path::getFileName() const { return fsPath.filename().string(); }

        const std::string Path::getFileNameWithoutExtension() const { return fsPath.stem().string(); }

        const std::string Path::getDirectory() const { return fsPath.parent_path().string(); }

        const std::string Path::getPath() const { return fsPath.string(); }

        Path Path::operator+(const Path& other) const {
            std::string path = fsPath.string() + "/" + other.fsPath.string();
            return Path(path, false);
        }

        Path Path::operator+(const std::string& other) const {
            std::string path = fsPath.string() + "/" + other;
            return Path(path, false);
        }

        Path& Path::operator+=(const Path& other) {
            fsPath += "/" + other.fsPath.string();
            return *this;
        }

        Path& Path::operator+=(const std::string& other) {
            fsPath += "/" + other;
            return *this;
        }
    }  // namespace core::io
}  // namespace cobalt