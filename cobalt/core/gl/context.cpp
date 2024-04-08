// Created by tomas on
// 02-12-2023

#include "core/gl/context.h"

#include "core/pch.h"

namespace cobalt {
    namespace core::gl {
        std::shared_ptr<Context> Context::instance = nullptr;

        void Context::init() {
            if (!glfwInit()) {
                throw GLException("Failed to initialize GLFW");
            }
            if (instance) {
                throw GLException("Render context already initialized");
            }
            glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
            glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
            glfwWindowHint(GLFW_SCALE_TO_MONITOR, GLFW_TRUE);
            instance = CreateShared<Context>();
            glewExperimental = GL_TRUE;  // Needed for core profile
            CB_CORE_INFO("Initialized render context");
        }

        void Context::init(GLFWContext context) {
            if (instance) {
                throw GLException("Render context already initialized");
            }
            instance = CreateShared<Context>(context);
            CB_CORE_INFO("Initialized render context from GLFW context");
        }

        void Context::destroy() {
            glfwTerminate();
            instance.reset();
            instance = nullptr;
        }

        void Context::recreate() {
            void* pointer = nullptr;
            if (instance && instance->context) {
                pointer = instance->getUserPointer();
                glfwDestroyWindow(instance->context);
                instance->context = nullptr;
            }
            instance->context = glfwCreateWindow(1, 1, "", nullptr, nullptr);
            if (!instance->context) {
                // check for glfw errors
                const char* error;
                glfwGetError(&error);
                throw GLException("Failed to recreate render context: " + std::string(error));
            }
            glfwMakeContextCurrent(instance->context);
            if (pointer) {
                setUserPointer(pointer);
            }
        }

        void Context::recreateFromContext(GLFWContext oldContext) {
            void* pointer = nullptr;
            if (instance && instance->context) {
                pointer = instance->getUserPointer();
                GLFWwindow* newContext = glfwCreateWindow(1, 1, "", nullptr, oldContext);
                if (!newContext) {
                    const char* error;
                    glfwGetError(&error);
                    throw GLException("Failed to recreate render context from old context: " + std::string(error));
                }
                glfwMakeContextCurrent(newContext);
                glfwDestroyWindow(oldContext);
                instance->context = newContext;
                if (pointer) {
                    setUserPointer(pointer);
                }
            } else {
                throw GLException("No existing render context to recreate from");
            }
        }

        void Context::setKeyCallback(GLFWkeyfun callback) { glfwSetKeyCallback(instance->context, callback); }

        void Context::setScrollCallback(GLFWscrollfun callback) { glfwSetScrollCallback(instance->context, callback); }

        void Context::setCursorPosCallback(GLFWcursorposfun callback) { glfwSetCursorPosCallback(instance->context, callback); }

        void Context::setMouseButtonCallback(GLFWmousebuttonfun callback) { glfwSetMouseButtonCallback(instance->context, callback); }

        void Context::setResizeCallback(GLFWwindowsizefun callback) { glfwSetWindowSizeCallback(instance->context, callback); }

        void Context::setFramebufferResizeCallback(GLFWframebuffersizefun callback) { glfwSetFramebufferSizeCallback(instance->context, callback); }

        void Context::setDebugCallback(GLDEBUGPROC callback) { glDebugMessageCallback(callback, nullptr); }

        void Context::setErrorCallback(GLFWerrorfun callback) { glfwSetErrorCallback(callback); }

        void Context::enableBlending() { glEnable(GL_BLEND); }

        void Context::disableBlending() { glDisable(GL_BLEND); }

        void Context::enableDepthTest() { glEnable(GL_DEPTH_TEST); }

        void Context::disableDepthTest() { glDisable(GL_DEPTH_TEST); }

        void Context::enableDepthWriting() { glDepthMask(GL_TRUE); }

        void Context::disableDepthWriting() { glDepthMask(GL_FALSE); }

        void Context::setUserPointer(void* pointer) { glfwSetWindowUserPointer(instance->context, pointer); }

        void* Context::getUserPointer() { return glfwGetWindowUserPointer(instance->context); }

        std::shared_ptr<Context>& Context::getInstance() {
            if (!instance) {
                throw GLException("Render context not initialized");
            }
            return instance;
        }

        GLFWContext Context::getGLFWContext() {
            if (!instance) {
                throw GLException("Render context not initialized");
            }
            return instance->context;
        }

        const char* Context::queryGLVersion() { return (const char*)glGetString(GL_VERSION); }

        const int Context::queryGLMajorVersion() {
            int major;
            glGetIntegerv(GL_MAJOR_VERSION, &major);
            return major;
        }

        const int Context::queryGLMinorVersion() {
            int minor;
            glGetIntegerv(GL_MINOR_VERSION, &minor);
            return minor;
        }

        const char* Context::queryGLSLVersion() { return (const char*)glGetString(GL_SHADING_LANGUAGE_VERSION); }

        const uint Context::queryMaxColorAttachments() {
            int max;
            glGetIntegerv(GL_MAX_COLOR_ATTACHMENTS, &max);
            return max;
        }

        const uint Context::queryMaxFragTextureUnits() {
            int max;
            glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &max);
            return max;
        }

        const uint Context::queryMaxTotalTextureUnits() {
            int max;
            glGetIntegerv(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS, &max);
            return max;
        }

        void Context::logQueries() {
            CB_CORE_INFO("OpenGL version: {0}", queryGLVersion());
            CB_CORE_INFO("GLSL version: {0}", queryGLSLVersion());
            CB_CORE_INFO("Max fragment texture units: {0}", queryMaxFragTextureUnits());
            CB_CORE_INFO("Max total texture units: {0}", queryMaxTotalTextureUnits());
        }

        void Context::clearGLErrors() {
            GLenum error;
            while ((error = glGetError()));
        }

        void Context::checkGLErrors() {
            GLenum error;
            while ((error = glGetError()) != GL_NO_ERROR) {
                CB_CORE_ERROR("GL error code: {0}", error);
            }
        }

        Context::Context() : context() {
            context = glfwCreateWindow(1, 1, "", nullptr, nullptr);
            if (!context) {
                throw GLException("Failed to create render context");
            }
            glfwMakeContextCurrent(context);
            GLenum err = glewInit();
            if (err != GLEW_OK) {
                throw GLException("Failed to initialize GLEW: " + std::string((const char*)glewGetErrorString(err)));
            }
            logQueries();
        }

        Context::Context(GLFWContext context) : context(context) {
            if (!context) {
                throw GLException("Failed to create render context");
            }
            glfwMakeContextCurrent(context);
        }

        Context::~Context() { glfwDestroyWindow(context); }
    }  // namespace core::gl
}  // namespace cobalt