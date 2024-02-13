// Created by tomas on
// 02-12-2023

#include "core/gfx/window.h"

#include "core/ecs/world.h"
#include "core/gl/context.h"
#include "core/input/input_manager.h"
#include "core/pch.h"

namespace cobalt {
    namespace core::gfx {
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
              title(title),
              vsync(vsync),
              mode(mode),
              resizable(resizable),
              decorated(decorated),
              lockAspectRatio(lockAspectRatio),
              aspectRatio((float)width / (float)height),
              defaultFBO(),
              keyCallback(keyCallback),
              cursorCallback(cursorCallback),
              mouseButtonCallback(mouseButtonCallback),
              scrollCallback(scrollCallback),
              framebufferResizeCallback(framebufferResizeCallback),
              resizeCallback(resizeCallback) {}

        void Window::init() {
            glfwWindowHint(GLFW_RESIZABLE, resizable);
            glfwSetWindowCloseCallback(gl::Context::getGLFWContext(), windowCloseCallback);
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
                    if (Platform::isMacOS()) {
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
                    throw GFXException("Invalid window mode");
            }

            gl::Context::recreateFromContext(gl::Context::getGLFWContext());
            glfwSwapInterval(vsync);
            glfwSetWindowTitle(gl::Context::getGLFWContext(), title.c_str());
            if (lockAspectRatio) {
                if (mode == WindowMode::Windowed) {
                    this->width = (uint)(this->height * aspectRatio);
                }
                glfwSetWindowAspectRatio(gl::Context::getGLFWContext(), this->width, this->height);
            }
            glfwSetWindowSize(gl::Context::getGLFWContext(), this->width, this->height);
            int framebufferWidth, framebufferHeight;
            glfwGetFramebufferSize(gl::Context::getGLFWContext(), &framebufferWidth, &framebufferHeight);
            defaultFBO.resize(framebufferWidth, framebufferHeight);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            glEnable(GL_BLEND);
            glDepthFunc(GL_LEQUAL);
            glEnable(GL_DEPTH_TEST);
            glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
            gl::Context::setKeyCallback([](GLFWwindow* window, int key, int scancode, int action, int mods) {
                try {
                    core::input::InputManager& manager =
                        static_cast<ecs::World*>(core::gl::Context::getUserPointer())->getResource<core::input::InputManager>();
                    core::gfx::Window& window = static_cast<ecs::World*>(core::gl::Context::getUserPointer())->getResource<core::gfx::Window>();
                    window.onKey(manager, manager.getPeripheral<core::input::Keyboard>(core::input::Keyboard::NAME).glfwToCobalt(key),
                                 action != GLFW_RELEASE);
                } catch (core::ecs::ResourceNotFoundException<core::input::InputManager>& e) {
                    throw core::ecs::PluginNotFoundException("Input");
                } catch (core::ecs::ResourceNotFoundException<core::gfx::Window>& e) {
                    throw core::ecs::PluginNotFoundException("Window");
                }
            });
            gl::Context::setCursorPosCallback([](GLFWwindow* window, double xpos, double ypos) {
                try {
                    core::input::InputManager& manager =
                        static_cast<ecs::World*>(core::gl::Context::getUserPointer())->getResource<core::input::InputManager>();
                    core::gfx::Window& window = static_cast<ecs::World*>(core::gl::Context::getUserPointer())->getResource<core::gfx::Window>();
                    window.onCursor(manager, (float)xpos, (float)ypos);
                } catch (core::ecs::ResourceNotFoundException<core::input::InputManager>& e) {
                    throw core::ecs::PluginNotFoundException("Input");
                } catch (core::ecs::ResourceNotFoundException<core::gfx::Window>& e) {
                    throw core::ecs::PluginNotFoundException("Window");
                }
            });
            gl::Context::setMouseButtonCallback([](GLFWwindow* window, int button, int action, int mods) {
                try {
                    core::input::InputManager& manager =
                        static_cast<ecs::World*>(core::gl::Context::getUserPointer())->getResource<core::input::InputManager>();
                    core::gfx::Window& window = static_cast<ecs::World*>(core::gl::Context::getUserPointer())->getResource<core::gfx::Window>();
                    window.onMouseButton(manager, manager.getPeripheral<core::input::Mouse>(core::input::Mouse::NAME).glfwToCobalt(button),
                                         action != GLFW_RELEASE);
                } catch (core::ecs::ResourceNotFoundException<core::input::InputManager>& e) {
                    throw core::ecs::PluginNotFoundException("Input");
                } catch (core::ecs::ResourceNotFoundException<core::gfx::Window>& e) {
                    throw core::ecs::PluginNotFoundException("Window");
                }
            });
            gl::Context::setScrollCallback([](GLFWwindow* window, double xoffset, double yoffset) {
                try {
                    core::input::InputManager& manager =
                        static_cast<ecs::World*>(core::gl::Context::getUserPointer())->getResource<core::input::InputManager>();
                    core::gfx::Window& window = static_cast<ecs::World*>(core::gl::Context::getUserPointer())->getResource<core::gfx::Window>();
                    window.onScroll(manager, (float)xoffset, (float)yoffset);
                } catch (core::ecs::ResourceNotFoundException<core::input::InputManager>& e) {
                    throw core::ecs::PluginNotFoundException("Input");
                } catch (core::ecs::ResourceNotFoundException<core::gfx::Window>& e) {
                    throw core::ecs::PluginNotFoundException("Window");
                }
            });
            gl::Context::setFramebufferResizeCallback([](GLFWwindow* window, int width, int height) {
                try {
                    core::gfx::Window& window = static_cast<ecs::World*>(core::gl::Context::getUserPointer())->getResource<core::gfx::Window>();
                    window.onFramebufferResize(width, height);
                } catch (core::ecs::ResourceNotFoundException<core::gfx::Window>& e) {
                    throw core::ecs::PluginNotFoundException("Window");
                }
            });
            gl::Context::setResizeCallback([](GLFWwindow* window, int width, int height) {
                try {
                    core::gfx::Window& window = static_cast<ecs::World*>(core::gl::Context::getUserPointer())->getResource<core::gfx::Window>();
                    window.onResize(width, height);
                } catch (core::ecs::ResourceNotFoundException<core::gfx::Window>& e) {
                    throw core::ecs::PluginNotFoundException("Window");
                }
            });
            CB_CORE_INFO("Created window");
        }

        Window::~Window() {
            CB_CORE_INFO("Destroyed window");
            glfwSetWindowShouldClose(gl::Context::getGLFWContext(), GLFW_TRUE);
        }

        void Window::swapBuffers() const { glfwSwapBuffers(gl::Context::getGLFWContext()); }

        void Window::switchMode(const WindowMode mode) {
            this->mode = mode;
            init();
            show();
        }

        void Window::show() const { glfwShowWindow(gl::Context::getGLFWContext()); }

        void Window::hide() const { glfwHideWindow(gl::Context::getGLFWContext()); }

        void Window::clear() { defaultFBO.clear(); }

        bool Window::shouldClose() const { return glfwWindowShouldClose(gl::Context::getGLFWContext()); }

        void Window::setClearColor(const Color& color) { defaultFBO.setClearColor(color); }

        void Window::resize() { glfwSetWindowSize(gl::Context::getGLFWContext(), width, height); }

        const uint Window::getWidth() const { return width; }

        const uint Window::getHeight() const { return height; }

        gl::FBO& Window::getDefaultFBO() { return defaultFBO; }

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
            glfwSetWindowTitle(gl::Context::getGLFWContext(), title.c_str());
        }

        void Window::setKeyCallback(const KeyCallback callback) { keyCallback = callback; }

        void Window::setCursorCallback(const CursorCallback callback) { cursorCallback = callback; }

        void Window::setMouseButtonCallback(const MouseButtonCallback callback) { mouseButtonCallback = callback; }

        void Window::setScrollCallback(const ScrollCallback callback) { scrollCallback = callback; }

        void Window::setFramebufferResizeCallback(const FramebufferResizeCallback callback) { framebufferResizeCallback = callback; }

        void Window::setResizeCallback(const ResizeCallback callback) { resizeCallback = callback; }

        void Window::onKey(core::input::InputManager& manager, const core::input::KeyboardInputID key, const bool down) {
            if (keyCallback) {
                keyCallback(manager, key, down);
            }
        }

        void Window::onCursor(core::input::InputManager& manager, const float xpos, const float ypos) {
            if (cursorCallback) {
                cursorCallback(manager, xpos, ypos);
            }
        }

        void Window::onMouseButton(core::input::InputManager& manager, const core::input::MouseInputID button, const bool down) {
            if (mouseButtonCallback) {
                mouseButtonCallback(manager, button, down);
            }
        }

        void Window::onScroll(core::input::InputManager& manager, const float xoffset, const float yoffset) {
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
            defaultFBO.resize(width, height);
            if (resizeCallback) {
                resizeCallback(*this, width, height);
            }
        }

        WindowBuilder::WindowBuilder()
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

        WindowBuilder& WindowBuilder::setKeyCallback(const Window::KeyCallback callback) {
            this->keyCallback = callback;
            return *this;
        }

        WindowBuilder& WindowBuilder::setCursorCallback(const Window::CursorCallback callback) {
            this->cursorCallback = callback;
            return *this;
        }

        WindowBuilder& WindowBuilder::setMouseButtonCallback(const Window::MouseButtonCallback callback) {
            this->mouseButtonCallback = callback;
            return *this;
        }

        WindowBuilder& WindowBuilder::setScrollCallback(const Window::ScrollCallback callback) {
            this->scrollCallback = callback;
            return *this;
        }

        WindowBuilder& WindowBuilder::setFramebufferResizeCallback(const Window::FramebufferResizeCallback callback) {
            this->framebufferResizeCallback = callback;
            return *this;
        }

        WindowBuilder& WindowBuilder::setResizeCallback(const Window::ResizeCallback callback) {
            this->resizeCallback = callback;
            return *this;
        }

        Window WindowBuilder::build() const {
            return Window(width, height, title, vsync, mode, resizable, decorated, lockAspectRatio, keyCallback, cursorCallback, mouseButtonCallback,
                          scrollCallback, framebufferResizeCallback, resizeCallback);
        }
    }  // namespace core::gfx
}  // namespace cobalt