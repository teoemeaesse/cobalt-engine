// Created by tomas on
// 02-04-2024

#include "engine/camera/manager.h"

#include "engine/camera/plugin.h"

namespace cobalt {
    namespace engine {
        CameraID::CameraID(const uint handle, const std::string& name, CameraManager& owner) noexcept : handle(handle), name(name), owner(owner) {}

        CameraID::CameraID(const CameraID& other) noexcept : handle(other.handle), name(other.name), owner(other.owner) {}

        CameraID::CameraID(CameraID&& other) noexcept : handle(other.handle), name(std::move(other.name)), owner(other.owner) {}

        CameraID& CameraID::operator=(const CameraID& other) noexcept {
            handle = other.handle;
            name = other.name;
            return *this;
        }

        CameraID& CameraID::operator=(CameraID&& other) noexcept {
            handle = other.handle;
            name = std::move(other.name);
            return *this;
        }

        bool CameraID::operator==(const CameraID& other) const { return handle == other.handle; }

        const uint CameraID::getHandle() const { return handle; }

        const std::string& CameraID::getName() const { return name; }

        CameraController& CameraID::getController() { return owner.getController(*this); }

        Camera& CameraID::getCamera() { return owner.getCamera(*this); }

        CameraController& CameraManager::getController(const CameraID& id) {
            try {
                return cameras.at(id);
            } catch (const std::out_of_range& e) {
                throw core::ecs::PluginException<CameraPlugin, CameraManager>("Camera with id " + std::to_string(id.handle) + " does not exist");
            }
        }

        const CameraController& CameraManager::getController(const CameraID& id) const {
            try {
                return cameras.at(id);
            } catch (const std::out_of_range& e) {
                throw core::ecs::PluginException<CameraPlugin, CameraManager>("Camera with id " + std::to_string(id.handle) + " does not exist");
            }
        }

        CameraController& CameraManager::getController(const std::string& name) {
            try {
                return cameras.at(cameraNames.at(name));
            } catch (const std::out_of_range& e) {
                throw core::ecs::PluginException<CameraPlugin, CameraManager>("Camera with name " + name + " does not exist");
            }
        }

        const CameraController& CameraManager::getController(const std::string& name) const {
            try {
                return cameras.at(cameraNames.at(name));
            } catch (const std::out_of_range& e) {
                throw core::ecs::PluginException<CameraPlugin, CameraManager>("Camera with name " + name + " does not exist");
            }
        }

        Camera& CameraManager::getCamera(const CameraID& id) {
            try {
                return cameras.at(id).getCamera();
            } catch (const std::out_of_range& e) {
                throw core::ecs::PluginException<CameraPlugin, CameraManager>("Camera with id " + std::to_string(id.handle) + " does not exist");
            }
        }

        const Camera& CameraManager::getCamera(const CameraID& id) const {
            try {
                return cameras.at(id).getCamera();
            } catch (const std::out_of_range& e) {
                throw core::ecs::PluginException<CameraPlugin, CameraManager>("Camera with id " + std::to_string(id.handle) + " does not exist");
            }
        }

        Camera& CameraManager::getCamera(const std::string& name) {
            try {
                return cameras.at(cameraNames.at(name)).getCamera();
            } catch (const std::out_of_range& e) {
                throw core::ecs::PluginException<CameraPlugin, CameraManager>("Camera with name " + name + " does not exist");
            }
        }

        const Camera& CameraManager::getCamera(const std::string& name) const {
            try {
                return cameras.at(cameraNames.at(name)).getCamera();
            } catch (const std::out_of_range& e) {
                throw core::ecs::PluginException<CameraPlugin, CameraManager>("Camera with name " + name + " does not exist");
            }
        }
    }  // namespace engine
}  // namespace cobalt