//
// Created by tomas on 02-12-2023.
//

#include "core/gfx/window.h"
#include "core/gfx/render_context.h"
#include "core/input/input_manager.h"
#include "core/pch.h"


namespace cobalt {
    namespace core {
        static void windowCloseCallback(GLFWwindow* window) {
            CB_CORE_WARN("Window closed");
            CB_CORE_WARN("Shutting down");
        }

        Window::Window(
            const uint width,
            const uint height,
            const std::string& title,
            const bool vsync,
            const WindowMode mode,
            const bool resizable,
            const bool decorated,
            const bool lockAspectRatio,
            const CallbackSetter callbackSetter
        ) :
            width(width),
            height(height),
            title(title),
            vsync(vsync),
            mode(mode),
            resizable(resizable),
            decorated(decorated),
            lockAspectRatio(lockAspectRatio),
            aspectRatio((float) width / (float) height),
            defaultFBO(GLFramebufferAttachment::ColorDepth),
            callbackSetter(callbackSetter) {
            init();
        }

        void Window::init() {
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
                    if (Platform::isMacOS()) {
                        CB_CORE_WARN("Borderless window mode is not supported on macOS");
                        mode = WindowMode::Windowed;
                        init(); // Rewind, go back to windowed mode
                        return;
                    }
                    primaryMonitor = NULL;
                    this->width = videoMode->width;
                    this->height = videoMode->height;
                    glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);
                    CB_CORE_INFO("Running in borderless fullscreen mode");
                    break;
                case WindowMode::Fullscreen:
                    if (Platform::isMacOS()) {
                        CB_CORE_WARN("Fullscreen window mode is not supported on macOS");
                        mode = WindowMode::Windowed;
                        init(); // Rewind, go back to windowed mode
                        return;
                    }
                    this->width = videoMode->width;
                    this->height = videoMode->height;
                    glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);
                    CB_CORE_INFO("Running in fullscreen mode");
                    break;
                default:
                    throw GFXException("Invalid window mode");
            }
            
            RenderContext::recreateFromContext(RenderContext::getGLFWContext());
            glfwSwapInterval(vsync);
            glfwSetWindowTitle(RenderContext::getGLFWContext(), title.c_str());
            if (lockAspectRatio) {
                if (mode == WindowMode::Windowed) {
                    this->width = (uint) (this->height * aspectRatio);
                }
                glfwSetWindowAspectRatio(RenderContext::getGLFWContext(), this->width, this->height);
            }
            glfwSetWindowSize(RenderContext::getGLFWContext(), this->width, this->height);
            int framebufferWidth, framebufferHeight;
            glfwGetFramebufferSize(RenderContext::getGLFWContext(), &framebufferWidth, &framebufferHeight);
            defaultFBO.resize(framebufferWidth, framebufferHeight);
            if (callbackSetter != nullptr) {
                callbackSetter();
            }
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            glEnable(GL_BLEND);
            glDepthFunc(GL_LEQUAL);
            glEnable(GL_DEPTH_TEST);
            glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS); 
            CB_CORE_INFO("Created window");
        }

        Window::~Window() {
            CB_CORE_INFO("Destroyed window");
            glfwSetWindowShouldClose(RenderContext::getGLFWContext(), GLFW_TRUE);
        }

        void Window::swapBuffers() const {
            glfwSwapBuffers(RenderContext::getGLFWContext());
        }
        
        void Window::switchMode(const WindowMode mode) {
            this->mode = mode;
            init();
            show();
        }

        void Window::show() const {
            glfwShowWindow(RenderContext::getGLFWContext());
        }

        void Window::hide() const {
            glfwHideWindow(RenderContext::getGLFWContext());
        }

        void Window::clear() {
            defaultFBO.clear();
        }

        bool Window::shouldClose() const {
            return glfwWindowShouldClose(RenderContext::getGLFWContext());
        }

        void Window::setClearColor(const Color& color) {
            defaultFBO.setClearColor(color);
        }
        
        void Window::onResize(const uint width, const uint height) {
            defaultFBO.resize(width, height);
        }

        void Window::resize() {
            glfwSetWindowSize(RenderContext::getGLFWContext(), width, height);
        }

        const uint Window::getWidth() const {
            return width;
        }

        const uint Window::getHeight() const {
            return height;
        }

        DefaultFBO& Window::getDefaultFBO() {
            return defaultFBO;
        }

        const bool Window::isVsync() const {
            return vsync;
        }

        const WindowMode Window::getMode() const {
            return mode;
        }

        void Window::setDimensions(const uint width, const uint height) {
            this->width = width;
            this->height = height;
        }

        void Window::setVsync(const bool vsync) {
            this->vsync = vsync;
            glfwSwapInterval(vsync);
        }

        void Window::setMode(const WindowMode mode) {
            switchMode(mode);
        }

        void Window::setTitle(const std::string& title) {
            this->title = title;
            glfwSetWindowTitle(RenderContext::getGLFWContext(), title.c_str());
        }

        WindowBuilder::WindowBuilder() :
            width(800),
            height(600),
            title("cobalt window"),
            vsync(false),
            mode(WindowMode::Windowed),
            resizable(true),
            decorated(true),
            lockAspectRatio(false),
            callbackSetter(nullptr) {}

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

        WindowBuilder& WindowBuilder::setLockAspectRatio(const bool lockAspectRatio) {
            this->lockAspectRatio = lockAspectRatio;
            return *this;
        }

        WindowBuilder& WindowBuilder::setCallbackSetter(Window::CallbackSetter callbackSetter) {
            this->callbackSetter = callbackSetter;
            return *this;
        }

        Window WindowBuilder::build() const {
            return Window(width, height, title, vsync, mode, resizable, decorated, lockAspectRatio, callbackSetter);
        }
    }
}