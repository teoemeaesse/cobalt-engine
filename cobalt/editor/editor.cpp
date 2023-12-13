//
// Created by tomas on 07-12-2023.
//

#include "editor/persistency/cobalt_configuration.h"
#include "editor/input/bindings.h"


namespace cobalt {
    namespace editor {
        class Editor : public engine::Application {
            public:
            Editor() : engine::Application(1),
                       configuration(CobaltConfiguration()),
                       renderGraph(scene, getWindow().getDefaultFBO())
            {
                configuration.configureWindow(getWindow());
                getWindow().setClearColor(COLOR(0.2f, 0.2f, 0.2f, 1.0f));
                getWindow().show();
                bindInput();

                CB_TEXTURE_LIBRARY.loadTextures(core::Path("cobalt/editor/assets/textures", true));
                CB_SHADER_LIBRARY.loadShaders(core::Path("cobalt/editor/assets/shaders", true));

                const core::Texture& testTexture = CB_TEXTURE_LIBRARY.getTexture(CB_TEXTURE_LIBRARY.getTextureID("test_texture"));
                engine::ShaderID testShaderID = CB_SHADER_LIBRARY.getShaderID("scene_shader");
                core::Shader& testShader = CB_SHADER_LIBRARY.getShader(testShaderID);
                
                core::Material* material = new core::Material(testShader, testTexture, testTexture, testTexture);
                core::Mesh mesh = core::Mesh::createRectangle(10, 10, material);
                scene.addMesh(std::move(mesh));

                renderGraph.init();
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

            void variableTimeStep(const float delta) override {
                if (getWindow().shouldClose()) {
                    stop();
                }
                getWindow().clear();

                getInputManager().pollEvents();
                getInputManager().clearEvents();

                scene.getMeshes()[0].rotate(glm::vec3(0.03f, 0.0005f, 0.0f));
                renderGraph.execute();

                getWindow().swapBuffers();

            }

            void onResize(const uint width, const uint height) override {
                renderGraph.resize((float) width, (float) height);
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
            engine::DefaultGraph renderGraph;
        };
    }
}

cobalt::engine::Application *cobalt::engine::createApplication() {
    return new cobalt::editor::Editor();
}