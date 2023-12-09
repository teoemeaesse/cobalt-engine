//
// Created by tomas on 07-12-2023.
//

#include "engine/cobalt.h"
#include "editor/persistency/configuration.h"
#include "editor/input/bindings.h"
#include "core/gfx/render_node.h"



namespace cobalt {
    namespace editor {
        class Editor : public engine::Application {
            public:
            Editor() : engine::Application(1),
                       configuration(CobaltConfiguration())
            {
                getWindow().setClearColor(COLOR(0.2f, 0.2f, 0.2f, 1.0f));
                try {
                    getWindow().setDimensions(configuration.get<int>("width"), configuration.get<int>("height"));
                    getWindow().setVsync(configuration.get<bool>("vsync"));
                    getWindow().setMode(static_cast<core::WindowMode>(configuration.get<int>("mode")));
                } catch (const engine::ConfigurationException& e) {
                    CB_WARN("Failed to load Cobalt configuration: {}", e.what());
                }
                getWindow().show();
                bindInput();
            }

            ~Editor() override {
                configuration.set("width", getWindow().getWidth());
                configuration.set("height", getWindow().getHeight());
                configuration.set("vsync", getWindow().isVsync());
                configuration.set("mode", static_cast<size_t>(getWindow().getMode()));
                configuration.serialize(core::Path("cobalt-config.json", true));
            }

            void fixedTimeStep() override {
                CB_INFO("Fps: {0}", getFramerate());
            }

            void variableTimeStep(float delta) override {
                if (getWindow().shouldClose()) {
                    stop();
                }
                getWindow().clear();

                getInputManager().pollEvents();
                getInputManager().clearEvents();

                getWindow().swapBuffers();
            }

            void bindInput() {
                getInputManager().getKeyboard().bind(core::KeyboardInputID::ESCAPE, std::make_unique<Quit>(this));
                getInputManager().getKeyboard().bind(core::KeyboardInputID::F9, std::make_unique<Windowed>(&getWindow()));
                getInputManager().getKeyboard().bind(core::KeyboardInputID::F10, std::make_unique<Borderless>(&getWindow()));
                getInputManager().getKeyboard().bind(core::KeyboardInputID::F11, std::make_unique<Fullscreen>(&getWindow()));
            }

            private:
            CobaltConfiguration configuration;
        };
    }
}

cobalt::engine::Application *cobalt::engine::createApplication() {
    return new cobalt::editor::Editor();
}