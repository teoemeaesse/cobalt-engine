//
// Created
// by
// tomas
// on
// 03-12-2023.
//

#include "core/input/keyboard.h"

#include "core/exceptions/input_exception.h"

namespace cobalt {
    namespace core::input {
        const std::string Keyboard::NAME = "Keyboard";

        bool KeyState::isDown() const { return down; }

        bool KeyState::isPolled() const { return polled; }

        KeyState::KeyState() : down(false), polled(false) {}

        Keyboard::Keyboard(const DeviceID id) : Peripheral(id) {
            for (size_t i = 0; i < static_cast<size_t>(KeyboardInputID::COUNT); i++) {
                keyStates[i] = KeyState();
            }
        }

        void Keyboard::onKeyPress(const int key, const int action) {
            KeyboardInputID id = glfwToCobalt(key);
            if (id == KeyboardInputID::UNKNOWN) {
                throw InvalidInputException<KeyboardInputID>("Invalid key", id, this);
            }
            keyStates[static_cast<size_t>(id)].down = action != GLFW_RELEASE;
        }

        void Keyboard::pollEvents() {
            for (size_t i = 0; i < static_cast<size_t>(KeyboardInputID::COUNT); i++) {
                KeyState& state = keyStates[i];
                if (state.down) {
                    auto it = bindings.find(static_cast<KeyboardInputID>(i));
                    if (it != bindings.end()) {
                        events.push(it->second.get()->withInput({state.down, state.polled, 1.0f}));
                    }
                    if (!state.polled) {
                        state.polled = true;
                    }
                } else if (state.polled) {
                    state.polled = false;
                    auto it = bindings.find(static_cast<KeyboardInputID>(i));
                    if (it != bindings.end()) {
                        events.push(it->second.get()->withInput({state.down, state.polled, 1.0f}));
                    }
                }
            }
        }

        void Keyboard::clearEvents() {
            while (!events.empty()) {
                events.front()->execute();
                events.pop();
            }
        }

        KeyState& Keyboard::getKey(const KeyboardInputID key) { return keyStates[static_cast<size_t>(key)]; }

        const static UMap<int, KeyboardInputID> GLFW_TO_CB = {{GLFW_KEY_A, KeyboardInputID::A},
                                                              {GLFW_KEY_B, KeyboardInputID::B},
                                                              {GLFW_KEY_C, KeyboardInputID::C},
                                                              {GLFW_KEY_D, KeyboardInputID::D},
                                                              {GLFW_KEY_E, KeyboardInputID::E},
                                                              {GLFW_KEY_F, KeyboardInputID::F},
                                                              {GLFW_KEY_G, KeyboardInputID::G},
                                                              {GLFW_KEY_H, KeyboardInputID::H},
                                                              {GLFW_KEY_I, KeyboardInputID::I},
                                                              {GLFW_KEY_J, KeyboardInputID::J},
                                                              {GLFW_KEY_K, KeyboardInputID::K},
                                                              {GLFW_KEY_L, KeyboardInputID::L},
                                                              {GLFW_KEY_M, KeyboardInputID::M},
                                                              {GLFW_KEY_N, KeyboardInputID::N},
                                                              {GLFW_KEY_O, KeyboardInputID::O},
                                                              {GLFW_KEY_P, KeyboardInputID::P},
                                                              {GLFW_KEY_Q, KeyboardInputID::Q},
                                                              {GLFW_KEY_R, KeyboardInputID::R},
                                                              {GLFW_KEY_S, KeyboardInputID::S},
                                                              {GLFW_KEY_T, KeyboardInputID::T},
                                                              {GLFW_KEY_U, KeyboardInputID::U},
                                                              {GLFW_KEY_V, KeyboardInputID::V},
                                                              {GLFW_KEY_W, KeyboardInputID::W},
                                                              {GLFW_KEY_X, KeyboardInputID::X},
                                                              {GLFW_KEY_Y, KeyboardInputID::Y},
                                                              {GLFW_KEY_Z, KeyboardInputID::Z},
                                                              {GLFW_KEY_0, KeyboardInputID::N0},
                                                              {GLFW_KEY_1, KeyboardInputID::N1},
                                                              {GLFW_KEY_2, KeyboardInputID::N2},
                                                              {GLFW_KEY_3, KeyboardInputID::N3},
                                                              {GLFW_KEY_4, KeyboardInputID::N4},
                                                              {GLFW_KEY_5, KeyboardInputID::N5},
                                                              {GLFW_KEY_6, KeyboardInputID::N6},
                                                              {GLFW_KEY_7, KeyboardInputID::N7},
                                                              {GLFW_KEY_8, KeyboardInputID::N8},
                                                              {GLFW_KEY_9, KeyboardInputID::N9},
                                                              {GLFW_KEY_F1, KeyboardInputID::F1},
                                                              {GLFW_KEY_F2, KeyboardInputID::F2},
                                                              {GLFW_KEY_F3, KeyboardInputID::F3},
                                                              {GLFW_KEY_F4, KeyboardInputID::F4},
                                                              {GLFW_KEY_F5, KeyboardInputID::F5},
                                                              {GLFW_KEY_F6, KeyboardInputID::F6},
                                                              {GLFW_KEY_F7, KeyboardInputID::F7},
                                                              {GLFW_KEY_F8, KeyboardInputID::F8},
                                                              {GLFW_KEY_F9, KeyboardInputID::F9},
                                                              {GLFW_KEY_F10, KeyboardInputID::F10},
                                                              {GLFW_KEY_F11, KeyboardInputID::F11},
                                                              {GLFW_KEY_F12, KeyboardInputID::F12},
                                                              {GLFW_KEY_F13, KeyboardInputID::F13},
                                                              {GLFW_KEY_F14, KeyboardInputID::F14},
                                                              {GLFW_KEY_F15, KeyboardInputID::F15},
                                                              {GLFW_KEY_F16, KeyboardInputID::F16},
                                                              {GLFW_KEY_F17, KeyboardInputID::F17},
                                                              {GLFW_KEY_F18, KeyboardInputID::F18},
                                                              {GLFW_KEY_F19, KeyboardInputID::F19},
                                                              {GLFW_KEY_F20, KeyboardInputID::F20},
                                                              {GLFW_KEY_F21, KeyboardInputID::F21},
                                                              {GLFW_KEY_F22, KeyboardInputID::F22},
                                                              {GLFW_KEY_F23, KeyboardInputID::F23},
                                                              {GLFW_KEY_F24, KeyboardInputID::F24},
                                                              {GLFW_KEY_F25, KeyboardInputID::F25},
                                                              {GLFW_KEY_LEFT_SHIFT, KeyboardInputID::LSHIFT},
                                                              {GLFW_KEY_RIGHT_SHIFT, KeyboardInputID::RSHIFT},
                                                              {GLFW_KEY_LEFT_CONTROL, KeyboardInputID::LCTRL},
                                                              {GLFW_KEY_RIGHT_CONTROL, KeyboardInputID::RCTRL},
                                                              {GLFW_KEY_LEFT_ALT, KeyboardInputID::LALT},
                                                              {GLFW_KEY_RIGHT_ALT, KeyboardInputID::RALT},
                                                              {GLFW_KEY_SPACE, KeyboardInputID::SPACE},
                                                              {GLFW_KEY_ENTER, KeyboardInputID::ENTER},
                                                              {GLFW_KEY_ESCAPE, KeyboardInputID::ESCAPE},
                                                              {GLFW_KEY_TAB, KeyboardInputID::TAB},
                                                              {GLFW_KEY_BACKSPACE, KeyboardInputID::BACKSPACE},
                                                              {GLFW_KEY_INSERT, KeyboardInputID::INSERT},
                                                              {GLFW_KEY_DELETE, KeyboardInputID::DELETE},
                                                              {GLFW_KEY_RIGHT, KeyboardInputID::RIGHT},
                                                              {GLFW_KEY_LEFT, KeyboardInputID::LEFT},
                                                              {GLFW_KEY_DOWN, KeyboardInputID::DOWN},
                                                              {GLFW_KEY_UP, KeyboardInputID::UP}};
        const static UMap<KeyboardInputID, std::string> CB_TO_STR = {{KeyboardInputID::A, "Key A"},
                                                                     {KeyboardInputID::B, "Key B"},
                                                                     {KeyboardInputID::C, "Key C"},
                                                                     {KeyboardInputID::D, "Key D"},
                                                                     {KeyboardInputID::E, "Key E"},
                                                                     {KeyboardInputID::F, "Key F"},
                                                                     {KeyboardInputID::G, "Key G"},
                                                                     {KeyboardInputID::H, "Key H"},
                                                                     {KeyboardInputID::I, "Key I"},
                                                                     {KeyboardInputID::J, "Key J"},
                                                                     {KeyboardInputID::K, "Key K"},
                                                                     {KeyboardInputID::L, "Key L"},
                                                                     {KeyboardInputID::M, "Key M"},
                                                                     {KeyboardInputID::N, "Key N"},
                                                                     {KeyboardInputID::O, "Key O"},
                                                                     {KeyboardInputID::P, "Key P"},
                                                                     {KeyboardInputID::Q, "Key Q"},
                                                                     {KeyboardInputID::R, "Key R"},
                                                                     {KeyboardInputID::S, "Key S"},
                                                                     {KeyboardInputID::T, "Key T"},
                                                                     {KeyboardInputID::U, "Key U"},
                                                                     {KeyboardInputID::V, "Key V"},
                                                                     {KeyboardInputID::W, "Key W"},
                                                                     {KeyboardInputID::X, "Key X"},
                                                                     {KeyboardInputID::Y, "Key Y"},
                                                                     {KeyboardInputID::Z, "Key Z"},
                                                                     {KeyboardInputID::N0, "Number 0"},
                                                                     {KeyboardInputID::N1, "Number 1"},
                                                                     {KeyboardInputID::N2, "Number 2"},
                                                                     {KeyboardInputID::N3, "Number 3"},
                                                                     {KeyboardInputID::N4, "Number 4"},
                                                                     {KeyboardInputID::N5, "Number 5"},
                                                                     {KeyboardInputID::N6, "Number 6"},
                                                                     {KeyboardInputID::N7, "Number 7"},
                                                                     {KeyboardInputID::N8, "Number 8"},
                                                                     {KeyboardInputID::N9, "Number 9"},
                                                                     {KeyboardInputID::F1, "Function F1"},
                                                                     {KeyboardInputID::F2, "Function F2"},
                                                                     {KeyboardInputID::F3, "Function F3"},
                                                                     {KeyboardInputID::F4, "Function F4"},
                                                                     {KeyboardInputID::F5, "Function F5"},
                                                                     {KeyboardInputID::F6, "Function F6"},
                                                                     {KeyboardInputID::F7, "Function F7"},
                                                                     {KeyboardInputID::F8, "Function F8"},
                                                                     {KeyboardInputID::F9, "Function F9"},
                                                                     {KeyboardInputID::F10, "Function F10"},
                                                                     {KeyboardInputID::F11, "Function F11"},
                                                                     {KeyboardInputID::F12, "Function F12"},
                                                                     {KeyboardInputID::F13, "Function F13"},
                                                                     {KeyboardInputID::F14, "Function F14"},
                                                                     {KeyboardInputID::F15, "Function F15"},
                                                                     {KeyboardInputID::F16, "Function F16"},
                                                                     {KeyboardInputID::F17, "Function F17"},
                                                                     {KeyboardInputID::F18, "Function F18"},
                                                                     {KeyboardInputID::F19, "Function F19"},
                                                                     {KeyboardInputID::F20, "Function F20"},
                                                                     {KeyboardInputID::F21, "Function F21"},
                                                                     {KeyboardInputID::F22, "Function F22"},
                                                                     {KeyboardInputID::F23, "Function F23"},
                                                                     {KeyboardInputID::F24, "Function F24"},
                                                                     {KeyboardInputID::F25, "Function F25"},
                                                                     {KeyboardInputID::LSHIFT, "Left Shift"},
                                                                     {KeyboardInputID::RSHIFT, "Right Shift"},
                                                                     {KeyboardInputID::LCTRL, "Left Control"},
                                                                     {KeyboardInputID::RCTRL, "Right Control"},
                                                                     {KeyboardInputID::LALT, "Left Alt"},
                                                                     {KeyboardInputID::RALT, "Right Alt"},
                                                                     {KeyboardInputID::SPACE, "Space"},
                                                                     {KeyboardInputID::ENTER, "Enter"},
                                                                     {KeyboardInputID::ESCAPE, "Escape"},
                                                                     {KeyboardInputID::TAB, "Tab"},
                                                                     {KeyboardInputID::BACKSPACE, "Backspace"},
                                                                     {KeyboardInputID::INSERT, "Insert"},
                                                                     {KeyboardInputID::DELETE, "Delete"},
                                                                     {KeyboardInputID::RIGHT, "Right"},
                                                                     {KeyboardInputID::LEFT, "Left"},
                                                                     {KeyboardInputID::DOWN, "Down"},
                                                                     {KeyboardInputID::UP, "Up"},
                                                                     {KeyboardInputID::COUNT, "Count"},
                                                                     {KeyboardInputID::UNKNOWN, "Unknown"}};

        const std::string& Keyboard::toString() const { return NAME; }

        const KeyboardInputID Keyboard::glfwToCobalt(const int glfwCode) const {
            auto it = GLFW_TO_CB.find(glfwCode);
            if (it != GLFW_TO_CB.end()) {
                return it->second;
            }
            return KeyboardInputID::UNKNOWN;
        }

        const int Keyboard::cobaltToGlfw(const KeyboardInputID cobaltCode) const {
            for (const auto& [key, value] : GLFW_TO_CB) {
                if (value == cobaltCode) {
                    return key;
                }
            }
            return GLFW_KEY_UNKNOWN;
        }

        const std::string& Keyboard::cobaltToStr(const KeyboardInputID cobaltCode) const {
            auto it = CB_TO_STR.find(cobaltCode);
            if (it != CB_TO_STR.end()) {
                return it->second;
            }
            return CB_TO_STR.at(KeyboardInputID::UNKNOWN);
        }
    }  // namespace core
} // namespace cobalt