// Created by tomas on
// 02-12-2023

#include "engine/window/window.h"

#include "core/gl/context.h"
#include "engine/window/plugin.h"

namespace cobalt {
    namespace engine {
        static void windowCloseCallback(GLFWwindow* window) {
            CB_CORE_WARN("Window closed");
            CB_CORE_WARN("Shutting down");
        }

        Window::Window(const uint width, const uint height, const std::string& title, const bool vsync, const WindowMode mode, const bool resizable,
                       const bool decorated, const bool lockAspectRatio, const KeyCallback keyCallback, const CursorCallback cursorCallback,
                       const MouseButtonCallback mouseButtonCallback, const ScrollCallback scrollCallback,
                       const FramebufferResizeCallback framebufferResizeCallback, const ResizeCallback resizeCallback)
            : width(width),
              height(height),
              defaultFBO(),
              title(title),
              vsync(vsync),
              mode(mode),
              resizable(resizable),
              decorated(decorated),
              lockAspectRatio(lockAspectRatio),
              aspectRatio((float)width / (float)height),
              keyCallback(keyCallback),
              cursorCallback(cursorCallback),
              mouseButtonCallback(mouseButtonCallback),
              scrollCallback(scrollCallback),
              framebufferResizeCallback(framebufferResizeCallback),
              resizeCallback(resizeCallback) {}

        Window Window::create(const WindowProperties& properties) noexcept { return properties.getWindow(); }

        Window::Window(Window&& other) noexcept
            : width(other.width),
              height(other.height),
              title(Move(other.title)),
              vsync(other.vsync),
              mode(other.mode),
              resizable(other.resizable),
              decorated(other.decorated),
              lockAspectRatio(other.lockAspectRatio),
              aspectRatio(other.aspectRatio),
              defaultFBO(Move(other.defaultFBO)),
              keyCallback(Move(other.keyCallback)),
              cursorCallback(Move(other.cursorCallback)),
              mouseButtonCallback(Move(other.mouseButtonCallback)),
              scrollCallback(Move(other.scrollCallback)),
              framebufferResizeCallback(Move(other.framebufferResizeCallback)),
              resizeCallback(Move(other.resizeCallback)) {
            other.title = "void";
        }

        void Window::init() {
            try {
                static_cast<core::ecs::World*>(core::gl::Context::getUserPointer())->getResource<Window>();
            } catch (const core::ecs::ResourceNotFoundException<Window>& e) {
                throw core::ecs::PluginNotFoundException("Window");
            }
            glfwWindowHint(GLFW_RESIZABLE, resizable);
            glfwSetWindowCloseCallback(core::gl::Context::getGLFWContext(), windowCloseCallback);
            GLFWmonitor* primaryMonitor = glfwGetPrimaryMonitor();
            const GLFWvidmode* videoMode = glfwGetVideoMode(primaryMonitor);
            switch (mode) {
                case WindowMode::Windowed:
                    primaryMonitor = NULL;
                    glfwWindowHint(GLFW_DECORATED, decorated);
                    CB_CORE_INFO("Running in windowed mode");
                    break;
                case WindowMode::Borderless:
                    if (core::Platform::isMacOS()) {
                        CB_CORE_WARN("Borderless window mode is not supported on macOS");
                        mode = WindowMode::Windowed;
                        init();  // Rewind, go back to windowed mode
                        return;
                    }
                    primaryMonitor = NULL;
                    this->width = videoMode->width;
                    this->height = videoMode->height;
                    glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);
                    CB_CORE_INFO("Running in borderless fullscreen mode");
                    break;
                case WindowMode::Fullscreen:
                    if (core::Platform::isMacOS()) {
                        CB_CORE_WARN("Fullscreen window mode is not supported on macOS");
                        mode = WindowMode::Windowed;
                        init();  // Rewind, go back to windowed mode
                        return;
                    }
                    this->width = videoMode->width;
                    this->height = videoMode->height;
                    glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);
                    CB_CORE_INFO("Running in fullscreen mode");
                    break;
                default:
                    throw core::ecs::PluginException<WindowPlugin>("Invalid window mode");
            }

            core::gl::Context::recreateFromContext(core::gl::Context::getGLFWContext());
            glfwSwapInterval(vsync);
            glfwSetWindowTitle(core::gl::Context::getGLFWContext(), title.c_str());
            if (lockAspectRatio) {
                if (mode == WindowMode::Windowed) {
                    this->width = (uint)(this->height * aspectRatio);
                }
                glfwSetWindowAspectRatio(core::gl::Context::getGLFWContext(), this->width, this->height);
            }
            glfwSetWindowSize(core::gl::Context::getGLFWContext(), this->width, this->height);
            int framebufferWidth, framebufferHeight;
            glfwGetFramebufferSize(core::gl::Context::getGLFWContext(), &framebufferWidth, &framebufferHeight);
            defaultFBO.resize(framebufferWidth, framebufferHeight);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            glEnable(GL_BLEND);
            glDepthFunc(GL_LEQUAL);
            glEnable(GL_DEPTH_TEST);
            glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
            if (static_cast<core::ecs::World*>(core::gl::Context::getUserPointer())->isPlugin("Input")) {
                core::gl::Context::setKeyCallback([](GLFWwindow* handle, int key, int scancode, int action, int mods) {
                    InputManager& manager = static_cast<core::ecs::World*>(core::gl::Context::getUserPointer())->getResource<InputManager>();
                    Window& window = static_cast<core::ecs::World*>(core::gl::Context::getUserPointer())->getResource<Window>();
                    window.onKey(manager, key, action != GLFW_RELEASE);
                });
                core::gl::Context::setCursorPosCallback([](GLFWwindow* handle, double xpos, double ypos) {
                    InputManager& manager = static_cast<core::ecs::World*>(core::gl::Context::getUserPointer())->getResource<InputManager>();
                    Window& window = static_cast<core::ecs::World*>(core::gl::Context::getUserPointer())->getResource<Window>();
                    window.onCursor(manager, (float)xpos, (float)ypos);
                });
                core::gl::Context::setMouseButtonCallback([](GLFWwindow* handle, int button, int action, int mods) {
                    InputManager& manager = static_cast<core::ecs::World*>(core::gl::Context::getUserPointer())->getResource<InputManager>();
                    Window& window = static_cast<core::ecs::World*>(core::gl::Context::getUserPointer())->getResource<Window>();
                    window.onMouseButton(manager, button, action != GLFW_RELEASE);
                });
                core::gl::Context::setScrollCallback([](GLFWwindow* handle, double xoffset, double yoffset) {
                    InputManager& manager = static_cast<core::ecs::World*>(core::gl::Context::getUserPointer())->getResource<InputManager>();
                    Window& window = static_cast<core::ecs::World*>(core::gl::Context::getUserPointer())->getResource<Window>();
                    window.onScroll(manager, (float)xoffset, (float)yoffset);
                });
            }

            core::gl::Context::setFramebufferResizeCallback([](GLFWwindow* handle, int width, int height) {
                Window& window = static_cast<core::ecs::World*>(core::gl::Context::getUserPointer())->getResource<Window>();
                window.getDefaultFBO().resize((uint)width, (uint)height);
                window.onFramebufferResize((uint)width, (uint)height);
            });
            core::gl::Context::setResizeCallback([](GLFWwindow* handle, int width, int height) {
                Window& window = static_cast<core::ecs::World*>(core::gl::Context::getUserPointer())->getResource<Window>();
                window.setDimensions((uint)width, (uint)height);
                window.onResize((uint)width, (uint)height);
            });
            CB_CORE_INFO("Created window");
        }

        Window::~Window() {
            if (title != "void") {
                CB_CORE_INFO("Destroyed window");
                glfwSetWindowShouldClose(core::gl::Context::getGLFWContext(), GLFW_TRUE);
            }
        }

        void Window::swapBuffers() const { glfwSwapBuffers(core::gl::Context::getGLFWContext()); }

        void Window::switchMode(const WindowMode mode) {
            this->mode = mode;
            init();
            show();
        }

        void Window::show() const { glfwShowWindow(core::gl::Context::getGLFWContext()); }

        void Window::hide() const { glfwHideWindow(core::gl::Context::getGLFWContext()); }

        void Window::clear() { defaultFBO.clear(); }

        bool Window::shouldClose() const { return glfwWindowShouldClose(core::gl::Context::getGLFWContext()); }

        void Window::setClearColor(const core::Color& color) { defaultFBO.setClearColor(color); }

        void Window::resize() { glfwSetWindowSize(core::gl::Context::getGLFWContext(), width, height); }

        const uint Window::getWidth() const { return width; }

        const uint Window::getHeight() const { return height; }

        core::gl::FBO& Window::getDefaultFBO() { return defaultFBO; }

        const core::gl::FBO& Window::getDefaultFBO() const { return defaultFBO; }

        const bool Window::isVsync() const { return vsync; }

        const WindowMode Window::getMode() const { return mode; }

        void Window::setDimensions(const uint width, const uint height) {
            this->width = width;
            this->height = height;
        }

        void Window::setVsync(const bool vsync) {
            this->vsync = vsync;
            glfwSwapInterval(vsync);
        }

        void Window::setMode(const WindowMode mode) { switchMode(mode); }

        void Window::setTitle(const std::string& title) {
            this->title = title;
            glfwSetWindowTitle(core::gl::Context::getGLFWContext(), title.c_str());
        }

        void Window::setKeyCallback(const KeyCallback callback) { keyCallback = callback; }

        void Window::setCursorCallback(const CursorCallback callback) { cursorCallback = callback; }

        void Window::setMouseButtonCallback(const MouseButtonCallback callback) { mouseButtonCallback = callback; }

        void Window::setScrollCallback(const ScrollCallback callback) { scrollCallback = callback; }

        void Window::setFramebufferResizeCallback(const FramebufferResizeCallback callback) { framebufferResizeCallback = callback; }

        void Window::setResizeCallback(const ResizeCallback callback) { resizeCallback = callback; }

        void Window::onKey(InputManager& manager, const int key, const bool down) {
            if (keyCallback) {
                keyCallback(manager, key, down);
            }
        }

        void Window::onCursor(InputManager& manager, const float xpos, const float ypos) {
            if (cursorCallback) {
                cursorCallback(manager, xpos, ypos);
            }
        }

        void Window::onMouseButton(InputManager& manager, const int button, const bool down) {
            if (mouseButtonCallback) {
                mouseButtonCallback(manager, button, down);
            }
        }

        void Window::onScroll(InputManager& manager, const float xoffset, const float yoffset) {
            if (scrollCallback) {
                scrollCallback(manager, xoffset, yoffset);
            }
        }

        void Window::onFramebufferResize(const uint width, const uint height) {
            if (framebufferResizeCallback) {
                framebufferResizeCallback(*this, width, height);
            }
        }

        void Window::onResize(const uint width, const uint height) {
            if (resizeCallback) {
                resizeCallback(*this, width, height);
            }
        }

        WindowProperties::WindowProperties()
            : width(800),
              height(600),
              title("cobalt window"),
              vsync(false),
              mode(WindowMode::Windowed),
              resizable(true),
              decorated(true),
              lockAspectRatio(false),
              keyCallback(nullptr),
              cursorCallback(nullptr),
              mouseButtonCallback(nullptr),
              scrollCallback(nullptr),
              framebufferResizeCallback(nullptr),
              resizeCallback(nullptr) {}

        WindowProperties& WindowProperties::setWidth(const uint width) {
            this->width = width;
            return *this;
        }

        WindowProperties& WindowProperties::setHeight(const uint height) {
            this->height = height;
            return *this;
        }

        WindowProperties& WindowProperties::setTitle(const std::string& title) {
            this->title = title;
            return *this;
        }

        WindowProperties& WindowProperties::setVsync(const bool vsync) {
            this->vsync = vsync;
            return *this;
        }

        WindowProperties& WindowProperties::setMode(const WindowMode mode) {
            this->mode = mode;
            return *this;
        }

        WindowProperties& WindowProperties::setResizable(const bool resizable) {
            this->resizable = resizable;
            return *this;
        }

        WindowProperties& WindowProperties::setDecorated(const bool decorated) {
            this->decorated = decorated;
            return *this;
        }

        WindowProperties& WindowProperties::setLockAspectRatio(const bool lockAspectRatio) {
            this->lockAspectRatio = lockAspectRatio;
            return *this;
        }

        WindowProperties& WindowProperties::setKeyCallback(const Window::KeyCallback callback) {
            this->keyCallback = callback;
            return *this;
        }

        WindowProperties& WindowProperties::setCursorCallback(const Window::CursorCallback callback) {
            this->cursorCallback = callback;
            return *this;
        }

        WindowProperties& WindowProperties::setMouseButtonCallback(const Window::MouseButtonCallback callback) {
            this->mouseButtonCallback = callback;
            return *this;
        }

        WindowProperties& WindowProperties::setScrollCallback(const Window::ScrollCallback callback) {
            this->scrollCallback = callback;
            return *this;
        }

        WindowProperties& WindowProperties::setFramebufferResizeCallback(const Window::FramebufferResizeCallback callback) {
            this->framebufferResizeCallback = callback;
            return *this;
        }

        WindowProperties& WindowProperties::setResizeCallback(const Window::ResizeCallback callback) {
            this->resizeCallback = callback;
            return *this;
        }

        Window WindowProperties::getWindow() const {
            return Window(width, height, title, vsync, mode, resizable, decorated, lockAspectRatio, keyCallback, cursorCallback, mouseButtonCallback,
                          scrollCallback, framebufferResizeCallback, resizeCallback);
        }
    }  // namespace engine
}  // namespace cobalt