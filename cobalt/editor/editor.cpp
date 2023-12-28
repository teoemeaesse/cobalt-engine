//
// Created by tomas on 07-12-2023.
//

#include "editor/input/bindings.h"
#include "editor/editor.h"


namespace cobalt {
    namespace editor {
        Editor::Editor() :
            engine::Application(144),
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
            scene.getCamera().resize((float) width / (float) height);
        }

        void Editor::bindInput() {
            try {
                core::Keyboard& keyboard = getInputManager().getPeripheral<core::Keyboard>(core::Keyboard::NAME);
                keyboard.bind(core::KeyboardInputID::ESCAPE, std::make_unique<Quit>(this));
                keyboard.bind(core::KeyboardInputID::F9, std::make_unique<Windowed>(this));
                keyboard.bind(core::KeyboardInputID::F10, std::make_unique<Borderless>(this));
                keyboard.bind(core::KeyboardInputID::F11, std::make_unique<Fullscreen>(this));
                keyboard.bind(core::KeyboardInputID::W, std::make_unique<PanIn>(&scene.getCamera()));
                keyboard.bind(core::KeyboardInputID::A, std::make_unique<PanLeft>(&scene.getCamera()));
                keyboard.bind(core::KeyboardInputID::S, std::make_unique<PanOut>(&scene.getCamera()));
                keyboard.bind(core::KeyboardInputID::D, std::make_unique<PanRight>(&scene.getCamera()));
                keyboard.bind(core::KeyboardInputID::SPACE, std::make_unique<PanUp>(&scene.getCamera()));
                keyboard.bind(core::KeyboardInputID::LCTRL, std::make_unique<PanDown>(&scene.getCamera()));
                keyboard.bind(core::KeyboardInputID::UP, std::make_unique<PanUp>(&scene.getCamera()));
                keyboard.bind(core::KeyboardInputID::LEFT, std::make_unique<PanLeft>(&scene.getCamera()));
                keyboard.bind(core::KeyboardInputID::DOWN, std::make_unique<PanDown>(&scene.getCamera()));
                keyboard.bind(core::KeyboardInputID::RIGHT, std::make_unique<PanRight>(&scene.getCamera()));
                keyboard.bind(core::KeyboardInputID::P, std::make_unique<Spawn>(&scene));
            } catch (const core::PeripheralNotFoundException& e) {
                CB_EDITOR_ERROR(e.what());
            }

            try {
                core::Mouse& mouse = getInputManager().getPeripheral<core::Mouse>(core::Mouse::NAME);
                mouse.bind(core::MouseInputID::RIGHT_X, std::make_unique<RotateX>(&scene.getCamera()));
                mouse.bind(core::MouseInputID::RIGHT_Y, std::make_unique<RotateY>(&scene.getCamera()));
                mouse.bind(core::MouseInputID::SCROLL_Y, std::make_unique<Zoom>(&scene.getCamera()));
            } catch (const core::PeripheralNotFoundException& e) {
                CB_EDITOR_ERROR(e.what());
            }
        }

        void Editor::createScene() {
            scene.clear();
            scene.setSkybox(
                core::Skybox::create(
                    CB_TEXTURE_LIBRARY.getTexture3D("skybox"),
                    CB_SHADER_LIBRARY.getShader("skybox")
                )
            );
            const engine::TextureID woodAlbedo = CB_TEXTURE_LIBRARY.getTextureID("wood-albedo");
            const engine::TextureID woodNormal = CB_TEXTURE_LIBRARY.getTextureID("wood-normal");
            const engine::TextureID woodMrao = CB_TEXTURE_LIBRARY.getTextureID("wood-mrao");
            const engine::TextureID steelAlbedo = CB_TEXTURE_LIBRARY.getTextureID("steel-albedo");
            const engine::TextureID steelNormal = CB_TEXTURE_LIBRARY.getTextureID("steel-normal");
            const engine::TextureID steelMrao = CB_TEXTURE_LIBRARY.getTextureID("steel-mrao");
            const core::Texture2D& woodAlbedoTexture = CB_TEXTURE_LIBRARY.getTexture2D(woodAlbedo);
            const core::Texture2D& woodNormalTexture = CB_TEXTURE_LIBRARY.getTexture2D(woodNormal);
            const core::Texture2D& woodMraoTexture = CB_TEXTURE_LIBRARY.getTexture2D(woodMrao);
            const core::Texture2D& steelAlbedoTexture = CB_TEXTURE_LIBRARY.getTexture2D(steelAlbedo);
            const core::Texture2D& steelNormalTexture = CB_TEXTURE_LIBRARY.getTexture2D(steelNormal);
            const core::Texture2D& steelMraoTexture = CB_TEXTURE_LIBRARY.getTexture2D(steelMrao);

            core::Material& woodMaterial = CB_MATERIAL_LIBRARY.getMaterial(CB_MATERIAL_LIBRARY.makePBR("wood", woodAlbedo, woodNormal, woodMrao));
            core::Material& steelMaterial = CB_MATERIAL_LIBRARY.getMaterial(CB_MATERIAL_LIBRARY.makePBR("steel", steelAlbedo, steelNormal, steelMrao));
            core::Material& whiteRough = CB_MATERIAL_LIBRARY.getMaterial(CB_MATERIAL_LIBRARY.makePBR("white", COLOR_WHITE, 0.0f, 1.0f, 1.0f));
            core::Material& whiteSmooth = CB_MATERIAL_LIBRARY.getMaterial(CB_MATERIAL_LIBRARY.makePBR("white", COLOR_WHITE, 0.0f, 0.0f, 1.0f));
            core::Material& orangeMedium = CB_MATERIAL_LIBRARY.getMaterial(CB_MATERIAL_LIBRARY.makePBR("orange", COLOR_ORANGE, 0.0f, 0.5f, 1.0f));
            core::Mesh mesh = core::Mesh::createRectangle(10, 10, woodMaterial);
            core::Mesh ground = core::Mesh::createRectangle(100, 100, woodMaterial);
            core::Mesh sphere = core::Mesh::createSphere(5, woodMaterial);
            core::Mesh cube0 = core::Mesh::createCube(10, whiteRough);
            core::Mesh cube1 = core::Mesh::createCube(10, whiteSmooth);
            core::Mesh cube2 = core::Mesh::createCube(10, orangeMedium);
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
    }
}

cobalt::engine::Application *cobalt::engine::createApplication() {
    return new cobalt::editor::Editor();
}