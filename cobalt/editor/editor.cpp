//
// Created
// by
// tomas
// on
// 07-12-2023.
//

#include "editor/editor.h"

#include "editor/input/bindings.h"

namespace cobalt {
    namespace editor {
        Editor::Editor() : engine::Application(144), configuration(CobaltConfiguration()), renderGraph(scene, getWindow().getDefaultFBO()) {
            configuration.configureWindow(getWindow());
            getWindow().setClearColor(COLOR(0.2f, 0.2f, 0.2f, 1.0f));
            getWindow().show();
            bindInput();

            CB_TEXTURE_LIBRARY.loadTextures(core::io::Path("cobalt/editor/assets/textures", true));
            CB_SHADER_LIBRARY.loadShaders(core::io::Path("cobalt/editor/assets/shaders", true));

            createScene();

            renderGraph.init();
        }

        Editor::~Editor() {
            configuration.set("width", getWindow().getWidth());
            configuration.set("height", getWindow().getHeight());
            configuration.set("vsync", getWindow().isVsync());
            configuration.set("mode", static_cast<size_t>(getWindow().getMode()));
            configuration.serialize(core::io::Path("cobalt-config.json", true));
        }

        void Editor::fixedTimeStep() {
            getInputManager().pollEvents();
            getInputManager().clearEvents();

            scene.getCameraController().update();

            getWindow().setTitle("Cobalt Editor - " + std::to_string(getFramerate()) + " FPS");
        }

        void Editor::variableTimeStep(const float delta) {
            if (getWindow().shouldClose()) {
                stop();
            }
            getWindow().clear();

            scene.getMeshes()[0].rotate(glm::vec3(30.0f * delta, 5.0f * delta, 20.0f * delta));
            static float cubeXOffset = 0.0f;
            static float cubeYOffset = 0.0f;
            static float time = 0.0f;
            time += delta;
            cubeXOffset = sin(time) * 25.0f * delta;
            cubeYOffset = cos(time) * 25.0f * delta;
            scene.getMeshes()[4].translate(glm::vec3(cubeXOffset, 0.0f, cubeYOffset));
            renderGraph.execute();

            getWindow().swapBuffers();
        }

        void Editor::onResize(const uint width, const uint height) {
            renderGraph.onResize(width, height);
            scene.getCameraController().resize((float)width / (float)height);
        }

        void Editor::bindInput() {
            try {
                core::input::Keyboard& keyboard = getInputManager().getPeripheral<core::input::Keyboard>(core::input::Keyboard::NAME);
                keyboard.bind(core::input::KeyboardInputID::ESCAPE, createScope<Quit>(this));
                keyboard.bind(core::input::KeyboardInputID::F9, createScope<Windowed>(this));
                keyboard.bind(core::input::KeyboardInputID::F10, createScope<Borderless>(this));
                keyboard.bind(core::input::KeyboardInputID::F11, createScope<Fullscreen>(this));
                keyboard.bind(core::input::KeyboardInputID::W, createScope<PanIn>(&scene.getCameraController()));
                keyboard.bind(core::input::KeyboardInputID::A, createScope<PanLeft>(&scene.getCameraController()));
                keyboard.bind(core::input::KeyboardInputID::S, createScope<PanOut>(&scene.getCameraController()));
                keyboard.bind(core::input::KeyboardInputID::D, createScope<PanRight>(&scene.getCameraController()));
                keyboard.bind(core::input::KeyboardInputID::SPACE, createScope<PanUp>(&scene.getCameraController()));
                keyboard.bind(core::input::KeyboardInputID::LCTRL, createScope<PanDown>(&scene.getCameraController()));
                keyboard.bind(core::input::KeyboardInputID::UP, createScope<PanUp>(&scene.getCameraController()));
                keyboard.bind(core::input::KeyboardInputID::LEFT, createScope<PanLeft>(&scene.getCameraController()));
                keyboard.bind(core::input::KeyboardInputID::DOWN, createScope<PanDown>(&scene.getCameraController()));
                keyboard.bind(core::input::KeyboardInputID::RIGHT, createScope<PanRight>(&scene.getCameraController()));
                keyboard.bind(core::input::KeyboardInputID::P, createScope<Spawn>(&scene));
            } catch (const core::input::PeripheralNotFoundException& e) {
                CB_EDITOR_ERROR(e.what());
            }

            try {
                core::input::Mouse& mouse = getInputManager().getPeripheral<core::input::Mouse>(core::input::Mouse::NAME);
                mouse.bind(core::input::MouseInputID::RIGHT_X, createScope<RotateX>(&scene.getCameraController()));
                mouse.bind(core::input::MouseInputID::RIGHT_Y, createScope<RotateY>(&scene.getCameraController()));
                mouse.bind(core::input::MouseInputID::SCROLL_Y, createScope<Zoom>(&scene.getCameraController()));
            } catch (const core::input::PeripheralNotFoundException& e) {
                CB_EDITOR_ERROR(e.what());
            }
        }

        void Editor::createScene() {
            scene.clear();
            scene.setSkybox(core::gfx::Skybox::create(CB_TEXTURE_LIBRARY.getTexture3D("skybox"), CB_SHADER_LIBRARY.getShader("skybox")));
            const engine::TextureID woodAlbedo = CB_TEXTURE_LIBRARY.getTextureID("wood-albedo");
            const engine::TextureID woodNormal = CB_TEXTURE_LIBRARY.getTextureID("wood-normal");
            const engine::TextureID woodMrao = CB_TEXTURE_LIBRARY.getTextureID("wood-mrao");
            const engine::TextureID steelAlbedo = CB_TEXTURE_LIBRARY.getTextureID("steel-albedo");
            const engine::TextureID steelNormal = CB_TEXTURE_LIBRARY.getTextureID("steel-normal");
            const engine::TextureID steelMrao = CB_TEXTURE_LIBRARY.getTextureID("steel-mrao");
            const core::gl::Texture2D& woodAlbedoTexture = CB_TEXTURE_LIBRARY.getTexture2D(woodAlbedo);
            const core::gl::Texture2D& woodNormalTexture = CB_TEXTURE_LIBRARY.getTexture2D(woodNormal);
            const core::gl::Texture2D& woodMraoTexture = CB_TEXTURE_LIBRARY.getTexture2D(woodMrao);
            const core::gl::Texture2D& steelAlbedoTexture = CB_TEXTURE_LIBRARY.getTexture2D(steelAlbedo);
            const core::gl::Texture2D& steelNormalTexture = CB_TEXTURE_LIBRARY.getTexture2D(steelNormal);
            const core::gl::Texture2D& steelMraoTexture = CB_TEXTURE_LIBRARY.getTexture2D(steelMrao);

            core::gfx::Material& woodMaterial =
                CB_MATERIAL_LIBRARY.getMaterial(CB_MATERIAL_LIBRARY.makePBR("wood", woodAlbedo, woodNormal, woodMrao));
            core::gfx::Material& steelMaterial =
                CB_MATERIAL_LIBRARY.getMaterial(CB_MATERIAL_LIBRARY.makePBR("steel", steelAlbedo, steelNormal, steelMrao));
            core::gfx::Material& whiteRough = CB_MATERIAL_LIBRARY.getMaterial(CB_MATERIAL_LIBRARY.makePBR("white", COLOR_WHITE, 0.0f, 1.0f, 1.0f));
            core::gfx::Material& whiteSmooth = CB_MATERIAL_LIBRARY.getMaterial(CB_MATERIAL_LIBRARY.makePBR("white", COLOR_WHITE, 0.0f, 0.0f, 1.0f));
            core::gfx::Material& orangeMedium =
                CB_MATERIAL_LIBRARY.getMaterial(CB_MATERIAL_LIBRARY.makePBR("orange", COLOR_ORANGE, 0.0f, 0.5f, 1.0f));
            core::gfx::Mesh mesh = core::gfx::Mesh::createRectangle(10, 10, woodMaterial);
            core::gfx::Mesh ground = core::gfx::Mesh::createRectangle(100, 100, woodMaterial);
            core::gfx::Mesh sphere = core::gfx::Mesh::createSphere(5, woodMaterial);
            core::gfx::Mesh cube0 = core::gfx::Mesh::createCube(10, whiteRough);
            core::gfx::Mesh cube1 = core::gfx::Mesh::createCube(10, whiteSmooth);
            core::gfx::Mesh cube2 = core::gfx::Mesh::createCube(10, orangeMedium);
            ground.translate(glm::vec3(0.0f, -50.0f, 0.0f));
            ground.rotate(glm::vec3(90.0f, 0.0f, 0.0f));
            sphere.translate(glm::vec3(10.0f, 0.0f, 0.0f));
            mesh.translate(glm::vec3(-10.0f, 0.0f, 0.0f));
            cube0.translate(glm::vec3(0.0f, -45.0f, 25.0f));
            cube1.translate(glm::vec3(-25.0f, -30.0f, 0.0f));
            cube2.translate(glm::vec3(0.0f, -45.0f, -40.0f));
            cube0.rotate(glm::vec3(0.0f, 30.0f, 0.0f));
            cube1.rotate(glm::vec3(0.0f, 15.0f, 0.0f));
            cube2.rotate(glm::vec3(0.0f, 45.0f, 0.0f));
            scene.addMesh(std::move(mesh));
            scene.addMesh(std::move(ground));
            scene.addMesh(std::move(sphere));
            scene.addMesh(std::move(cube0));
            scene.addMesh(std::move(cube1));
            scene.addMesh(std::move(cube2));
        }
    }  // namespace editor
}  // namespace cobalt

cobalt::engine::Application* cobalt::engine::createApplication() { return new cobalt::editor::Editor(); }