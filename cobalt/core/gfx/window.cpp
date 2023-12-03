//
// Created by tomas on 02-12-2023.
//

#include "core/gfx/window.h"
#include "core/gfx/render_context.h"
#include "core/exceptions/gfx_exception.h"
#include "core/utils/log.h"


namespace cobalt {
    namespace core {
        static void windowCloseCallback(GLFWwindow* window) {
            CB_WARN("Window closed");
            CB_WARN("Shutting down");
        }

        Window::Window(
            const uint width,
            const uint height,
            const std::string& title,
            const bool vsync,
            const WindowMode mode,
            const bool resizable,
            const bool decorated
        ) :
            width(width),
            height(height),
            title(title),
            vsync(vsync),
            defaultFBO(0, 0) {
            glfwWindowHint(GLFW_RESIZABLE, resizable);
            glfwSetWindowCloseCallback(RenderContext::getGLFWContext(), windowCloseCallback);
            GLFWmonitor* primaryMonitor = glfwGetPrimaryMonitor();
            const GLFWvidmode* videoMode = glfwGetVideoMode(primaryMonitor);
            switch (mode) {
                case WindowMode::Windowed:
                    primaryMonitor = NULL;
                    glfwWindowHint(GLFW_DECORATED, decorated);
                    CB_CORE_INFO("Running in windowed mode");
                    break;
                case WindowMode::Borderless:
                    primaryMonitor = NULL;
                    this->width = videoMode->width;
                    this->height = videoMode->height;
                    glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);
                    CB_CORE_INFO("Running in borderless fullscreen mode");
                    break;
                case WindowMode::Fullscreen:
                    this->width = videoMode->width;
                    this->height = videoMode->height;
                    glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);
                    CB_CORE_INFO("Running in fullscreen mode");
                    break;
                default:
                    throw GFXException("Invalid window mode");
            }
            RenderContext::setUserPointer(this);
            RenderContext::recreate();
            glfwSwapInterval(vsync);
            glfwSetWindowSize(RenderContext::getGLFWContext(), this->width, this->height);
            glfwSetWindowTitle(RenderContext::getGLFWContext(), title.c_str());
            defaultFBO.resize(this->width, this->height);
            CB_CORE_INFO("Created window");
        }

        Window::~Window() {
            CB_CORE_INFO("Destroyed window");
            glfwSetWindowShouldClose(RenderContext::getGLFWContext(), GLFW_TRUE);
        }

        void Window::swapBuffers() const {
            glfwSwapBuffers(RenderContext::getGLFWContext());
        }

        void Window::pollEvents() const {
            glfwPollEvents();
        }

        void Window::show() const {
            glfwShowWindow(RenderContext::getGLFWContext());
        }

        void Window::hide() const {
            glfwHideWindow(RenderContext::getGLFWContext());
        }

        bool Window::shouldClose() const {
            return glfwWindowShouldClose(RenderContext::getGLFWContext());
        }

        WindowBuilder::WindowBuilder() :
            width(800),
            height(600),
            title("cobalt window"),
            vsync(false),
            mode(WindowMode::Windowed),
            resizable(true),
            decorated(true) {}

        WindowBuilder& WindowBuilder::setWidth(const uint width) {
            this->width = width;
            return *this;
        }

        WindowBuilder& WindowBuilder::setHeight(const uint height) {
            this->height = height;
            return *this;
        }

        WindowBuilder& WindowBuilder::setTitle(const std::string& title) {
            this->title = title;
            return *this;
        }

        WindowBuilder& WindowBuilder::setVsync(const bool vsync) {
            this->vsync = vsync;
            return *this;
        }

        WindowBuilder& WindowBuilder::setMode(const WindowMode mode) {
            this->mode = mode;
            return *this;
        }

        WindowBuilder& WindowBuilder::setResizable(const bool resizable) {
            this->resizable = resizable;
            return *this;
        }

        WindowBuilder& WindowBuilder::setDecorated(const bool decorated) {
            this->decorated = decorated;
            return *this;
        }

        Window WindowBuilder::build() const {
            return Window(width, height, title, vsync, mode, resizable, decorated);
        }
    }
}