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

                engine::TextureID testTextureID = CB_TEXTURE_LIBRARY.getTextureID("test_texture");
                const core::Texture& testTexture = CB_TEXTURE_LIBRARY.getTexture(testTextureID);
                engine::ShaderID testShaderID = CB_SHADER_LIBRARY.getShaderID("test_shader");
                core::Shader& testShader = CB_SHADER_LIBRARY.getShader(testShaderID);
                
                core::Material* material = new core::Material(CB_SHADER_LIBRARY.getShader(CB_SHADER_LIBRARY.getShaderID("test_shader")), CB_TEXTURE_LIBRARY.getTexture(CB_TEXTURE_LIBRARY.getTextureID("test_texture")), CB_TEXTURE_LIBRARY.getTexture(CB_TEXTURE_LIBRARY.getTextureID("test_texture")), CB_TEXTURE_LIBRARY.getTexture(CB_TEXTURE_LIBRARY.getTextureID("test_texture")));
                core::Mesh mesh = core::Mesh::createRectangle(100, 100, material);
                scene.addMesh(std::move(mesh));
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
                //outputCamera.resize(-(float) getWindow().getWidth() / 2, (float) getWindow().getWidth() / 2,
                //                    -(float) getWindow().getHeight() / 2, (float) getWindow().getHeight() / 2);


                scene.getMeshes()[0].rotate(glm::vec3(0.0f, 0.01f, 0.0f));

                getWindow().swapBuffers();

                renderGraph.execute();
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