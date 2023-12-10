//
// Created by tomas on 07-12-2023.
//

#include "editor/persistency/cobalt_configuration.h"
#include "editor/input/bindings.h"
#include "core/gfx/render_node.h"


namespace cobalt {
    namespace editor {
        class Editor : public engine::Application {
            public:
            Editor() : engine::Application(1),
                       configuration(CobaltConfiguration())
            {
                configuration.configureWindow(getWindow());
                getWindow().setClearColor(COLOR(0.2f, 0.2f, 0.2f, 1.0f));
                getWindow().show();
                bindInput();

                getTextureLibrary().loadTextures(core::Path("cobalt/editor/assets/textures", true));
                getShaderLibrary().loadShaders(core::Path("cobalt/editor/assets/shaders", true));

                engine::TextureID testTextureID = getTextureLibrary().getTextureID("test_texture");
                const core::Texture& testTexture = getTextureLibrary().getTexture(testTextureID);
                engine::ShaderID testShaderID = getShaderLibrary().getShaderID("test_shader");
                core::Shader& testShader = getShaderLibrary().getShader(testShaderID);
                std::unique_ptr<core::Mesh> testMesh = std::make_unique<core::Mesh>(core::Mesh::createRectangle(10, 5, core::Material(testShader, testTexture, testTexture, testTexture)));
                scene.addMesh(std::move(testMesh));
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

                renderGraph.render(scene);
            }

            void bindInput() {
                getInputManager().getKeyboard().bind(core::KeyboardInputID::ESCAPE, std::make_unique<Quit>(this));
                getInputManager().getKeyboard().bind(core::KeyboardInputID::F9, std::make_unique<Windowed>(&getWindow()));
                getInputManager().getKeyboard().bind(core::KeyboardInputID::F10, std::make_unique<Borderless>(&getWindow()));
                getInputManager().getKeyboard().bind(core::KeyboardInputID::F11, std::make_unique<Fullscreen>(&getWindow()));
            }

            private:
            CobaltConfiguration configuration;
            core::Scene scene;
            core::RenderGraph renderGraph;
        };
    }
}

cobalt::engine::Application *cobalt::engine::createApplication() {
    return new cobalt::editor::Editor();
}