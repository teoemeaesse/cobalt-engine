//
// Created by tomas on 02-12-2023.
//

#include "core/gfx/render_context.h"
#include "core/exceptions/gfx_exception.h"
#include "core/utils/log.h"


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
            instance = std::make_shared<RenderContext>();
            glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
            glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            glEnable(GL_BLEND);
            CB_CORE_INFO("Initialized render context");
        }
        
        void RenderContext::init(GLFWContext context) {
            if (instance) {
                throw GFXException("Render context already initialized");
            }
            instance = std::make_shared<RenderContext>(context);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            glEnable(GL_BLEND);
            CB_CORE_INFO("Initialized render context from GLFW context");
        }

        void RenderContext::destroy() {
            if (instance) {
                glfwDestroyWindow(instance->context);
            }
            glfwTerminate();
        }

        void RenderContext::recreate() {
            if (instance) {
                glfwDestroyWindow(instance->context);
            }
            instance->context = glfwCreateWindow(1, 1, "", nullptr, nullptr);
            if (!instance->context) {
                throw GFXException("Failed to recreate render context");
            }
            glfwMakeContextCurrent(instance->context);
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
            return instance->context;
        }

        RenderContext::RenderContext() :
            context() {
            context = glfwCreateWindow(1, 1, "", nullptr, nullptr);
            if (!context) {
                throw GFXException("Failed to create render context");
            }
            glfwMakeContextCurrent(context);
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