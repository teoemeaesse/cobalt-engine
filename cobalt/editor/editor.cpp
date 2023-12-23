//
// Created by tomas on 07-12-2023.
//

#include "editor/input/bindings.h"
#include "editor/editor.h"


namespace cobalt {
    namespace editor {
        Editor::Editor() : engine::Application(144),
                    configuration(CobaltConfiguration()),
                    renderGraph(scene, getWindow().getDefaultFBO())
        {
            configuration.configureWindow(getWindow());
            getWindow().setClearColor(COLOR(0.2f, 0.2f, 0.2f, 1.0f));
            getWindow().show();
            bindInput();

            CB_TEXTURE_LIBRARY.loadTextures(core::Path("cobalt/editor/assets/textures", true));
            CB_SHADER_LIBRARY.loadShaders(core::Path("cobalt/editor/assets/shaders", true));

            createScene();

            renderGraph.init();
        }

        Editor::~Editor() {
            configuration.set("width", getWindow().getWidth());
            configuration.set("height", getWindow().getHeight());
            configuration.set("vsync", getWindow().isVsync());
            configuration.set("mode", static_cast<size_t>(getWindow().getMode()));
            configuration.serialize(core::Path("cobalt-config.json", true));
        }

        void Editor::fixedTimeStep() {
            getInputManager().pollEvents();
            getInputManager().clearEvents();

            getWindow().setTitle("Cobalt Editor - " + std::to_string(getFramerate()) + " FPS");
        }

        void Editor::variableTimeStep(const float delta) {
            if (getWindow().shouldClose()) {
                stop();
            }
            getWindow().clear();

            scene.getMeshes()[0].rotate(glm::vec3(0.3f, 0.05f, 0.2f));
            renderGraph.execute();

            getWindow().swapBuffers();
        }

        void Editor::onResize(const float width, const float height) {
            renderGraph.onResize(width, height);
            scene.getCamera().resize(width / height);
        }

        void Editor::bindInput() {
            getInputManager().getKeyboard().bind(core::KeyboardInputID::ESCAPE, std::make_unique<Quit>(this));
            getInputManager().getKeyboard().bind(core::KeyboardInputID::F9, std::make_unique<Windowed>(this));
            getInputManager().getKeyboard().bind(core::KeyboardInputID::F10, std::make_unique<Borderless>(this));
            getInputManager().getKeyboard().bind(core::KeyboardInputID::F11, std::make_unique<Fullscreen>(this));
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

            getInputManager().getKeyboard().bind(core::KeyboardInputID::P, std::make_unique<Spawn>(&scene));
        }

        void Editor::createScene() {
            scene.clear();
            scene.setSkybox(
                core::Skybox::create(
                    CB_TEXTURE_LIBRARY.getTexture3D(CB_TEXTURE_LIBRARY.getTextureID("skybox")),
                    CB_SHADER_LIBRARY.getShader(CB_SHADER_LIBRARY.getShaderID("skybox"))
                )
            );
            const core::Texture& woodAlbedo = CB_TEXTURE_LIBRARY.getTexture2D(CB_TEXTURE_LIBRARY.getTextureID("wood-albedo"));
            const core::Texture& woodNormal = CB_TEXTURE_LIBRARY.getTexture2D(CB_TEXTURE_LIBRARY.getTextureID("wood-normal"));
            const core::Texture& woodMrao = CB_TEXTURE_LIBRARY.getTexture2D(CB_TEXTURE_LIBRARY.getTextureID("wood-mrao"));
            const core::Texture& steelAlbedo = CB_TEXTURE_LIBRARY.getTexture2D(CB_TEXTURE_LIBRARY.getTextureID("steel-albedo"));
            const core::Texture& steelNormal = CB_TEXTURE_LIBRARY.getTexture2D(CB_TEXTURE_LIBRARY.getTextureID("steel-normal"));
            const core::Texture& steelMrao = CB_TEXTURE_LIBRARY.getTexture2D(CB_TEXTURE_LIBRARY.getTextureID("steel-mrao"));
            core::Shader& shader = CB_SHADER_LIBRARY.getShader(CB_SHADER_LIBRARY.getShaderID("scene_shader"));
            core::Material* woodMaterial = new core::Material(shader, woodAlbedo, woodNormal, woodMrao);
            core::Material* steelMaterial = new core::Material(shader, steelAlbedo, steelNormal, steelMrao);
            core::Mesh mesh = core::Mesh::createRectangle(10, 10, woodMaterial);
            core::Mesh ground = core::Mesh::createRectangle(100, 100, woodMaterial);
            core::Mesh sphere = core::Mesh::createSphere(5.0f, woodMaterial);
            ground.translate(glm::vec3(0.0f, -50.0f, 0.0f));
            ground.rotate(glm::vec3(90.0f, 0.0f, 0.0f));
            sphere.translate(glm::vec3(10.0f, 0.0f, 0.0f));
            mesh.translate(glm::vec3(-10.0f, 0.0f, 0.0f));
            scene.addMesh(std::move(mesh));
            scene.addMesh(std::move(ground));
            scene.addMesh(std::move(sphere));
        }
    }
}

cobalt::engine::Application *cobalt::engine::createApplication() {
    return new cobalt::editor::Editor();
}