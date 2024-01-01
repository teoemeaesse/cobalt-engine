//
// Created by tomas on 02-12-2023.
//

#include "core/gfx/render_context.h"
#include "core/pch.h"


namespace cobalt {
    namespace core {
        std::shared_ptr<RenderContext> RenderContext::instance = nullptr;

        void RenderContext::init() {
            if (!glfwInit()) {
                throw GFXException("Failed to initialize GLFW");
            }
            if (instance) {
                throw GFXException("Render context already initialized");
            }
            glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
            glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
            glfwWindowHint(GLFW_SCALE_TO_MONITOR, GLFW_TRUE);
            instance = createRef<RenderContext>();
            glewExperimental = GL_TRUE; // Needed for core profile
            CB_CORE_INFO("Initialized render context");
        }
        
        void RenderContext::init(GLFWContext context) {
            if (instance) {
                throw GFXException("Render context already initialized");
            }
            instance = createRef<RenderContext>(context);
            CB_CORE_INFO("Initialized render context from GLFW context");
        }

        void RenderContext::destroy() {
            glfwTerminate();
            instance.reset();
            instance = nullptr;
        }

        void RenderContext::recreate() {
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
                throw GFXException("Failed to recreate render context: " + std::string(error));
            }
            glfwMakeContextCurrent(instance->context);
            if (pointer) {
                setUserPointer(pointer);
            }
        }
        
        void RenderContext::recreateFromContext(GLFWContext oldContext) {
            void* pointer = nullptr;
            if (instance && instance->context) {
                pointer = instance->getUserPointer();
                GLFWwindow* newContext = glfwCreateWindow(1, 1, "", nullptr, oldContext);
                if (!newContext) {
                    const char* error;
                    glfwGetError(&error);
                    throw GFXException("Failed to recreate render context from old context: " + std::string(error));
                }
                glfwMakeContextCurrent(newContext);
                glfwDestroyWindow(oldContext);
                instance->context = newContext;
                if (pointer) {
                    setUserPointer(pointer);
                }
            } else {
                throw GFXException("No existing render context to recreate from");
            }
        }

        void RenderContext::setKeyCallback(GLFWkeyfun callback) {
            glfwSetKeyCallback(instance->context, callback);
        }

        void RenderContext::setScrollCallback(GLFWscrollfun callback) {
            glfwSetScrollCallback(instance->context, callback);
        }

        void RenderContext::setCursorPosCallback(GLFWcursorposfun callback) {
            glfwSetCursorPosCallback(instance->context, callback);
        }

        void RenderContext::setMouseButtonCallback(GLFWmousebuttonfun callback) {
            glfwSetMouseButtonCallback(instance->context, callback);
        }

        void RenderContext::setResizeCallback(GLFWwindowsizefun callback) {
            glfwSetWindowSizeCallback(instance->context, callback);
        }

        void RenderContext::setFramebufferResizeCallback(GLFWframebuffersizefun callback) {
            glfwSetFramebufferSizeCallback(instance->context, callback);
        }

        void RenderContext::setDebugCallback(GLDEBUGPROC callback) {
            glDebugMessageCallback(callback, nullptr);
        }

        void RenderContext::setErrorCallback(GLFWerrorfun callback) {
            glfwSetErrorCallback(callback);
        }

        void RenderContext::enableBlending() {
            glEnable(GL_BLEND);
        }

        void RenderContext::disableBlending() {
            glDisable(GL_BLEND);
        }

        void RenderContext::enableDepthTest() {
            glEnable(GL_DEPTH_TEST);
        }

        void RenderContext::disableDepthTest() {
            glDisable(GL_DEPTH_TEST);
        }

        void RenderContext::enableDepthWriting() {
            glDepthMask(GL_TRUE);
        }

        void RenderContext::disableDepthWriting() {
            glDepthMask(GL_FALSE);
        }

        void RenderContext::setUserPointer(void* pointer) {
            glfwSetWindowUserPointer(instance->context, pointer);
        }

        void* RenderContext::getUserPointer() {
            return glfwGetWindowUserPointer(instance->context);
        }

        std::shared_ptr<RenderContext>& RenderContext::getInstance() {
            if (!instance) {
                throw GFXException("Render context not initialized");
            }
            return instance;
        }

        GLFWContext RenderContext::getGLFWContext() {
            if (!instance) {
                throw GFXException("Render context not initialized");
            }
            return instance->context;
        }

        const char* RenderContext::queryGLVersion() {
            return (const char*)glGetString(GL_VERSION);
        }    

        const char* RenderContext::queryGLSLVersion() {
            return (const char*)glGetString(GL_SHADING_LANGUAGE_VERSION);
        }

        uint RenderContext::queryMaxFragTextureUnits() {
            int max;
            glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &max);
            return max;
        }

        uint RenderContext::queryMaxTotalTextureUnits() {
            int max;
            glGetIntegerv(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS, &max);
            return max;
        }

        void RenderContext::logQueries() {
            CB_CORE_INFO("OpenGL version: {0}", queryGLVersion());
            CB_CORE_INFO("GLSL version: {0}", queryGLSLVersion());
            CB_CORE_INFO("Max fragment texture units: {0}", queryMaxFragTextureUnits());
            CB_CORE_INFO("Max total texture units: {0}", queryMaxTotalTextureUnits());
        }

        void RenderContext::clearGLErrors() {
            GLenum error;
            while((error = glGetError()));
        }

        void RenderContext::checkGLErrors() {
            GLenum error;
            while((error = glGetError()) != GL_NO_ERROR) {
                CB_CORE_ERROR("GL error code: {0}", error);
            }
        }

        RenderContext::RenderContext() :
            context() {
            context = glfwCreateWindow(1, 1, "", nullptr, nullptr);
            if (!context) {
                throw GFXException("Failed to create render context");
            }
            glfwMakeContextCurrent(context);
            GLenum err = glewInit();
            if (err != GLEW_OK) {
                throw GFXException("Failed to initialize GLEW: " + std::string((const char*)glewGetErrorString(err)));
            }
            logQueries();
        }

        RenderContext::RenderContext(GLFWContext context) :
            context(context) {
            if (!context) {
                throw GFXException("Failed to create render context");
            }
            glfwMakeContextCurrent(context);
        }

        RenderContext::~RenderContext() {
            glfwDestroyWindow(context);
        }
    }
}