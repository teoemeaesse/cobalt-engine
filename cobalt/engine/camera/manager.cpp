// Created by tomas on
// 02-04-2024

#include "engine/camera/manager.h"

namespace cobalt {
    namespace engine {
        CameraController& CameraManager::getController(const CameraID id) {
            try {
                return cameras.at(id);
            } catch (const std::out_of_range& e) {
                throw core::gfx::GFXException("Camera with id " + std::to_string(id) + " does not exist");
            }  // TODO: create plugin exception
        }

        const CameraController& CameraManager::getController(const CameraID id) const {
            try {
                return cameras.at(id);
            } catch (const std::out_of_range& e) {
                throw core::gfx::GFXException("Camera with id " + std::to_string(id) + " does not exist");
            }
        }

        CameraController& CameraManager::getController(const std::string& name) {
            try {
                return cameras.at(cameraNames.at(name));
            } catch (const std::out_of_range& e) {
                throw core::gfx::GFXException("Camera with name " + name + " does not exist");
            }
        }

        const CameraController& CameraManager::getController(const std::string& name) const {
            try {
                return cameras.at(cameraNames.at(name));
            } catch (const std::out_of_range& e) {
                throw core::gfx::GFXException("Camera with name " + name + " does not exist");
            }
        }
    }  // namespace engine
}  // namespace cobalt