//
// Created by tomas on 03-12-2023.
//

#include "core/input/keyboard.h"


namespace cobalt {
    namespace core {
        const static std::unordered_map<int, KeyID> GLFW_TO_CB = {
            { GLFW_KEY_A, KeyID::A }, { GLFW_KEY_B, KeyID::B }, { GLFW_KEY_C, KeyID::C }, { GLFW_KEY_D, KeyID::D }, { GLFW_KEY_E, KeyID::E }, { GLFW_KEY_F, KeyID::F }, { GLFW_KEY_G, KeyID::G }, { GLFW_KEY_H, KeyID::H }, { GLFW_KEY_I, KeyID::I }, { GLFW_KEY_J, KeyID::J }, { GLFW_KEY_K, KeyID::K }, { GLFW_KEY_L, KeyID::L }, { GLFW_KEY_M, KeyID::M }, { GLFW_KEY_N, KeyID::N }, { GLFW_KEY_O, KeyID::O }, { GLFW_KEY_P, KeyID::P }, { GLFW_KEY_Q, KeyID::Q }, { GLFW_KEY_R, KeyID::R }, { GLFW_KEY_S, KeyID::S }, { GLFW_KEY_T, KeyID::T }, { GLFW_KEY_U, KeyID::U }, { GLFW_KEY_V, KeyID::V }, { GLFW_KEY_W, KeyID::W }, { GLFW_KEY_X, KeyID::X }, { GLFW_KEY_Y, KeyID::Y }, { GLFW_KEY_Z, KeyID::Z }, 
            { GLFW_KEY_0, KeyID::N0 }, { GLFW_KEY_1, KeyID::N1 }, { GLFW_KEY_2, KeyID::N2 }, { GLFW_KEY_3, KeyID::N3 }, { GLFW_KEY_4, KeyID::N4 }, { GLFW_KEY_5, KeyID::N5 }, { GLFW_KEY_6, KeyID::N6 }, { GLFW_KEY_7, KeyID::N7 }, { GLFW_KEY_8, KeyID::N8 }, { GLFW_KEY_9, KeyID::N9 }, 
            { GLFW_KEY_F1, KeyID::F1 }, { GLFW_KEY_F2, KeyID::F2 }, { GLFW_KEY_F3, KeyID::F3 }, { GLFW_KEY_F4, KeyID::F4 }, { GLFW_KEY_F5, KeyID::F5 }, { GLFW_KEY_F6, KeyID::F6 }, { GLFW_KEY_F7, KeyID::F7 }, { GLFW_KEY_F8, KeyID::F8 }, { GLFW_KEY_F9, KeyID::F9 }, { GLFW_KEY_F10, KeyID::F10 }, { GLFW_KEY_F11, KeyID::F11 }, { GLFW_KEY_F12, KeyID::F12 }, { GLFW_KEY_F13, KeyID::F13 }, { GLFW_KEY_F14, KeyID::F14 }, { GLFW_KEY_F15, KeyID::F15 }, { GLFW_KEY_F16, KeyID::F16 }, { GLFW_KEY_F17, KeyID::F17 }, { GLFW_KEY_F18, KeyID::F18 }, { GLFW_KEY_F19, KeyID::F19 }, { GLFW_KEY_F20, KeyID::F20 }, { GLFW_KEY_F21, KeyID::F21 }, { GLFW_KEY_F22, KeyID::F22 }, { GLFW_KEY_F23, KeyID::F23 }, { GLFW_KEY_F24, KeyID::F24 }, { GLFW_KEY_F25, KeyID::F25 },
            { GLFW_KEY_LEFT_SHIFT, KeyID::LSHIFT },
            { GLFW_KEY_RIGHT_SHIFT, KeyID::RSHIFT },
            { GLFW_KEY_LEFT_CONTROL, KeyID::LCTRL },
            { GLFW_KEY_RIGHT_CONTROL, KeyID::RCTRL },
            { GLFW_KEY_LEFT_ALT, KeyID::LALT },
            { GLFW_KEY_RIGHT_ALT, KeyID::RALT },
            { GLFW_KEY_SPACE, KeyID::SPACE },
            { GLFW_KEY_ENTER, KeyID::ENTER },
            { GLFW_KEY_ESCAPE, KeyID::ESCAPE },
            { GLFW_KEY_TAB, KeyID::TAB },
            { GLFW_KEY_BACKSPACE, KeyID::BACKSPACE },
            { GLFW_KEY_INSERT, KeyID::INSERT },
            { GLFW_KEY_DELETE, KeyID::DELETE },
            { GLFW_KEY_RIGHT, KeyID::RIGHT },
            { GLFW_KEY_LEFT, KeyID::LEFT },
            { GLFW_KEY_DOWN, KeyID::DOWN },
            { GLFW_KEY_UP, KeyID::UP }
        };

        const static KeyID glfwToCobalt(const int key) {
            auto it = GLFW_TO_CB.find(key);
            if (it != GLFW_TO_CB.end()) {
                return it->second;
            }
            return KeyID::COUNT;
        }

        bool KeyState::isDown() const {
            return down;
        }

        bool KeyState::isPolled() const {
            return polled;
        }

        KeyState::KeyState() : down(false), polled(true) {
        }

        Keyboard::Keyboard() : Peripheral() {
            for (size_t i = 0; i < static_cast<size_t>(KeyID::COUNT); i++) {
                keyStates[i] = KeyState();
            }
        }

        void Keyboard::onKeyPress(const int key, const int action) {
            KeyID id = glfwToCobalt(key);
            keyStates[static_cast<size_t>(id)].down = action != GLFW_RELEASE;
        }

        void Keyboard::pollEvents() {
            for (size_t i = 0; i < static_cast<size_t>(KeyID::COUNT); i++) {
                KeyState &state = keyStates[i];
                if (state.down) {
                    if (state.polled) {
                        auto it = bindings.find(static_cast<KeyID>(i));
                        if (it != bindings.end()) {
                            events.enqueue(it->second.get());
                            state.polled = false;
                        }
                    }
                } else {
                    state.polled = true;
                }
            }
        }

        void Keyboard::clearEvents() {
            while (!events.isEmpty()) {
                events.dequeue()->execute({ false, false, 0.0f });
            }
        }

        KeyState& Keyboard::getKey(const KeyID key) {
            return keyStates[static_cast<size_t>(key)];
        }
    }
}