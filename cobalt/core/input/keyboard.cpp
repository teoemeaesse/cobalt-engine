//
// Created by tomas on 03-12-2023.
//

#include <map>

#include "core/input/keyboard.h"


namespace cobalt {
    namespace core {
        const static std::map<int, Key> GLFW_TO_CB = {
            { GLFW_KEY_A, Key::A }, { GLFW_KEY_B, Key::B }, { GLFW_KEY_C, Key::C }, { GLFW_KEY_D, Key::D }, { GLFW_KEY_E, Key::E }, { GLFW_KEY_F, Key::F }, { GLFW_KEY_G, Key::G }, { GLFW_KEY_H, Key::H }, { GLFW_KEY_I, Key::I }, { GLFW_KEY_J, Key::J }, { GLFW_KEY_K, Key::K }, { GLFW_KEY_L, Key::L }, { GLFW_KEY_M, Key::M }, { GLFW_KEY_N, Key::N }, { GLFW_KEY_O, Key::O }, { GLFW_KEY_P, Key::P }, { GLFW_KEY_Q, Key::Q }, { GLFW_KEY_R, Key::R }, { GLFW_KEY_S, Key::S }, { GLFW_KEY_T, Key::T }, { GLFW_KEY_U, Key::U }, { GLFW_KEY_V, Key::V }, { GLFW_KEY_W, Key::W }, { GLFW_KEY_X, Key::X }, { GLFW_KEY_Y, Key::Y }, { GLFW_KEY_Z, Key::Z }, 
            { GLFW_KEY_0, Key::N0 }, { GLFW_KEY_1, Key::N1 }, { GLFW_KEY_2, Key::N2 }, { GLFW_KEY_3, Key::N3 }, { GLFW_KEY_4, Key::N4 }, { GLFW_KEY_5, Key::N5 }, { GLFW_KEY_6, Key::N6 }, { GLFW_KEY_7, Key::N7 }, { GLFW_KEY_8, Key::N8 }, { GLFW_KEY_9, Key::N9 }, 
            { GLFW_KEY_F1, Key::F1 }, { GLFW_KEY_F2, Key::F2 }, { GLFW_KEY_F3, Key::F3 }, { GLFW_KEY_F4, Key::F4 }, { GLFW_KEY_F5, Key::F5 }, { GLFW_KEY_F6, Key::F6 }, { GLFW_KEY_F7, Key::F7 }, { GLFW_KEY_F8, Key::F8 }, { GLFW_KEY_F9, Key::F9 }, { GLFW_KEY_F10, Key::F10 }, { GLFW_KEY_F11, Key::F11 }, { GLFW_KEY_F12, Key::F12 }, { GLFW_KEY_F13, Key::F13 }, { GLFW_KEY_F14, Key::F14 }, { GLFW_KEY_F15, Key::F15 }, { GLFW_KEY_F16, Key::F16 }, { GLFW_KEY_F17, Key::F17 }, { GLFW_KEY_F18, Key::F18 }, { GLFW_KEY_F19, Key::F19 }, { GLFW_KEY_F20, Key::F20 }, { GLFW_KEY_F21, Key::F21 }, { GLFW_KEY_F22, Key::F22 }, { GLFW_KEY_F23, Key::F23 }, { GLFW_KEY_F24, Key::F24 }, { GLFW_KEY_F25, Key::F25 },
            { GLFW_KEY_LEFT_SHIFT, Key::LSHIFT },
            { GLFW_KEY_RIGHT_SHIFT, Key::RSHIFT },
            { GLFW_KEY_LEFT_CONTROL, Key::LCTRL },
            { GLFW_KEY_RIGHT_CONTROL, Key::RCTRL },
            { GLFW_KEY_LEFT_ALT, Key::LALT },
            { GLFW_KEY_RIGHT_ALT, Key::RALT },
            { GLFW_KEY_SPACE, Key::SPACE },
            { GLFW_KEY_ENTER, Key::ENTER },
            { GLFW_KEY_ESCAPE, Key::ESCAPE },
            { GLFW_KEY_TAB, Key::TAB },
            { GLFW_KEY_BACKSPACE, Key::BACKSPACE },
            { GLFW_KEY_INSERT, Key::INSERT },
            { GLFW_KEY_DELETE, Key::DELETE },
            { GLFW_KEY_RIGHT, Key::RIGHT },
            { GLFW_KEY_LEFT, Key::LEFT },
            { GLFW_KEY_DOWN, Key::DOWN },
            { GLFW_KEY_UP, Key::UP }
        };

        bool KeyState::isDown() const {
            return down;
        }

        bool KeyState::isPolled() const {
            return polled;
        }

        KeyState::KeyState() : down(false), polled(true) {
        }

        void Keyboard::onKeyPressed(const int key, const int action) {
            auto it = GLFW_TO_CB.find(key);
            if (it != GLFW_TO_CB.end()) {
                KeyState &state = keyStates[static_cast<size_t>(it->second)];
                state.down = action != GLFW_RELEASE;
            }
        }

        KeyState& Keyboard::getKey(const Key key) {
            return keyStates[static_cast<size_t>(key)];
        }
    }
}