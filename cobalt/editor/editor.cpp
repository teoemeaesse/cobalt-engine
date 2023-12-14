//
// Created by tomas on 07-12-2023.
//

#include "editor/persistency/cobalt_configuration.h"
#include "editor/input/bindings.h"


namespace cobalt {
    namespace editor {
        class Editor : public engine::Application {
            public:
            Editor() : engine::Application(144),
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
                core::Mesh ground = core::Mesh::createRectangle(100, 100, material);
                ground.translate(glm::vec3(0.0f, -50.0f, 0.0f));
                ground.rotate(glm::vec3(90.0f, 0.0f, 0.0f));
                scene.addMesh(std::move(mesh));
                scene.addMesh(std::move(ground));

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
                getInputManager().pollEvents();
                getInputManager().clearEvents();
                CB_INFO("Fps: {0}", getFramerate());
            }

            void variableTimeStep(const float delta) override {
                if (getWindow().shouldClose()) {
                    stop();
                }
                getWindow().clear();


                scene.getMeshes()[0].rotate(glm::vec3(0.3f, 0.05f, 0.2f));
                renderGraph.execute();

                getWindow().swapBuffers();
            }

            void onResize(const float width, const float height) override {
                renderGraph.onResize(width, height);
                scene.getCamera().resize(width / height);
            }

            void bindInput() {
                getInputManager().getKeyboard().bind(core::KeyboardInputID::ESCAPE, std::make_unique<Quit>(this));
                getInputManager().getKeyboard().bind(core::KeyboardInputID::F9, std::make_unique<Windowed>(&getWindow()));
                getInputManager().getKeyboard().bind(core::KeyboardInputID::F10, std::make_unique<Borderless>(&getWindow()));
                getInputManager().getKeyboard().bind(core::KeyboardInputID::F11, std::make_unique<Fullscreen>(&getWindow()));
                getInputManager().getKeyboard().bind(core::KeyboardInputID::W, std::make_unique<PanIn>(&scene.getCamera()));
                getInputManager().getKeyboard().bind(core::KeyboardInputID::A, std::make_unique<PanLeft>(&scene.getCamera()));
                getInputManager().getKeyboard().bind(core::KeyboardInputID::S, std::make_unique<PanOut>(&scene.getCamera()));
                getInputManager().getKeyboard().bind(core::KeyboardInputID::D, std::make_unique<PanRight>(&scene.getCamera()));
                getInputManager().getKeyboard().bind(core::KeyboardInputID::SPACE, std::make_unique<PanUp>(&scene.getCamera()));
                getInputManager().getKeyboard().bind(core::KeyboardInputID::LCTRL, std::make_unique<PanDown>(&scene.getCamera()));
                getInputManager().getKeyboard().bind(core::KeyboardInputID::UP, std::make_unique<PanUp>(&scene.getCamera()));
                getInputManager().getKeyboard().bind(core::KeyboardInputID::LEFT, std::make_unique<PanLeft>(&scene.getCamera()));
                getInputManager().getKeyboard().bind(core::KeyboardInputID::DOWN, std::make_unique<PanDown>(&scene.getCamera()));
                getInputManager().getKeyboard().bind(core::KeyboardInputID::RIGHT, std::make_unique<PanRight>(&scene.getCamera()));

                getInputManager().getMouse().bind(core::MouseInputID::RIGHT_X, std::make_unique<RotateX>(&scene.getCamera()));
                getInputManager().getMouse().bind(core::MouseInputID::RIGHT_Y, std::make_unique<RotateY>(&scene.getCamera()));
                getInputManager().getMouse().bind(core::MouseInputID::SCROLL_Y, std::make_unique<Zoom>(&scene.getCamera()));
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