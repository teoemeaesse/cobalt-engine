// Created by tomas on
// 07-12-2023

#include "editor/editor.h"

#include "editor/input/bindings.h"
#include "engine/ecs/plugin/window.h"

namespace cobalt {
    namespace editor {
        using namespace cobalt::core;
        using namespace cobalt::engine;

        Editor::Editor() : Application(144), configuration(CobaltConfiguration()) {
            configuration.configureWindow(getWindow());
            getWindow().setClearColor(COLOR(0.2f, 0.2f, 0.2f, 1.0f));
            getWindow().show();
            world.addHook<ecs::ReadRequest<gfx::Window>, ecs::WriteRequest<DefaultGraph>, ecs::WriteRequest<scene::Scene>>(
                WindowPlugin::FRAMEBUFFER_RESIZE_EVENT, [](auto window, auto graph, auto scene) {
                    const uint width = window.get().getDefaultFBO().getWidth();
                    const uint height = window.get().getDefaultFBO().getHeight();
                    graph.get().onResize(width, height);
                    scene.get().getCameraController().resize((float)width / (float)height);
                });

            CB_TEXTURE_LIBRARY.loadTextures(io::Path("cobalt/editor/assets/textures", true));
            CB_SHADER_LIBRARY.loadShaders(io::Path("cobalt/editor/assets/shaders", true));

            world.addResource<scene::Scene>();
            createScene();

            world.addResource<DefaultGraph>(world.getResource<scene::Scene>(), getWindow().getDefaultFBO());
            world.getResource<DefaultGraph>().init();

            bindInput();
        }

        Editor::~Editor() {
            configuration.set("width", getWindow().getWidth());
            configuration.set("height", getWindow().getHeight());
            configuration.set("vsync", getWindow().isVsync());
            configuration.set("mode", static_cast<size_t>(getWindow().getMode()));
            configuration.serialize(io::Path("cobalt-config.json", true));
        }

        void Editor::fixedTimeStep() {
            world.getResource<scene::Scene>().getCameraController().update();
            getWindow().setTitle("Cobalt Editor - " + std::to_string(getFramerate()) + " FPS");
        }

        void Editor::variableTimeStep(const float delta) {
            world.getResource<scene::Scene>().getMeshes()[0].rotate(glm::vec3(30.0f * delta, 5.0f * delta, 20.0f * delta));
            static float cubeXOffset = 0.0f;
            static float cubeYOffset = 0.0f;
            static float time = 0.0f;
            time += delta;
            cubeXOffset = sin(time) * 25.0f * delta;
            cubeYOffset = cos(time) * 25.0f * delta;
            world.getResource<scene::Scene>().getMeshes()[4].translate(glm::vec3(cubeXOffset, 0.0f, cubeYOffset));
            world.getResource<DefaultGraph>().execute();
        }

        void Editor::bindInput() {
            try {
                input::Keyboard& keyboard = getInputManager().getPeripheral<input::Keyboard>(input::Keyboard::NAME);
                scene::Scene& scene = world.getResource<scene::Scene>();
                keyboard.bind(input::KeyboardInputID::ESCAPE, createScope<Quit>(this));
                keyboard.bind(input::KeyboardInputID::F9, createScope<Windowed>(this));
                keyboard.bind(input::KeyboardInputID::F10, createScope<Borderless>(this));
                keyboard.bind(input::KeyboardInputID::F11, createScope<Fullscreen>(this));
                keyboard.bind(input::KeyboardInputID::W, createScope<PanIn>(&scene.getCameraController()));
                keyboard.bind(input::KeyboardInputID::A, createScope<PanLeft>(&scene.getCameraController()));
                keyboard.bind(input::KeyboardInputID::S, createScope<PanOut>(&scene.getCameraController()));
                keyboard.bind(input::KeyboardInputID::D, createScope<PanRight>(&scene.getCameraController()));
                keyboard.bind(input::KeyboardInputID::SPACE, createScope<PanUp>(&scene.getCameraController()));
                keyboard.bind(input::KeyboardInputID::LCTRL, createScope<PanDown>(&scene.getCameraController()));
                keyboard.bind(input::KeyboardInputID::UP, createScope<PanUp>(&scene.getCameraController()));
                keyboard.bind(input::KeyboardInputID::LEFT, createScope<PanLeft>(&scene.getCameraController()));
                keyboard.bind(input::KeyboardInputID::DOWN, createScope<PanDown>(&scene.getCameraController()));
                keyboard.bind(input::KeyboardInputID::RIGHT, createScope<PanRight>(&scene.getCameraController()));
                keyboard.bind(input::KeyboardInputID::P, createScope<Spawn>(&scene));
            } catch (const input::PeripheralNotFoundException& e) {
                CB_EDITOR_ERROR(e.what());
            }

            try {
                input::Mouse& mouse = getInputManager().getPeripheral<input::Mouse>(input::Mouse::NAME);
                scene::Scene& scene = world.getResource<scene::Scene>();
                mouse.bind(input::MouseInputID::RIGHT_X, createScope<RotateX>(&scene.getCameraController()));
                mouse.bind(input::MouseInputID::RIGHT_Y, createScope<RotateY>(&scene.getCameraController()));
                mouse.bind(input::MouseInputID::SCROLL_Y, createScope<Zoom>(&scene.getCameraController()));
            } catch (const input::PeripheralNotFoundException& e) {
                CB_EDITOR_ERROR(e.what());
            }
        }

        void Editor::createScene() {
            scene::Scene& scene = world.getResource<scene::Scene>();
            scene.clear();
            scene.setSkybox(gfx::Skybox::create(CB_TEXTURE_LIBRARY.getTexture3D("skybox"), CB_SHADER_LIBRARY.getShader("skybox")));
            const TextureID woodAlbedo = CB_TEXTURE_LIBRARY.getTextureID("wood-albedo");
            const TextureID woodNormal = CB_TEXTURE_LIBRARY.getTextureID("wood-normal");
            const TextureID woodMrao = CB_TEXTURE_LIBRARY.getTextureID("wood-mrao");
            const TextureID steelAlbedo = CB_TEXTURE_LIBRARY.getTextureID("steel-albedo");
            const TextureID steelNormal = CB_TEXTURE_LIBRARY.getTextureID("steel-normal");
            const TextureID steelMrao = CB_TEXTURE_LIBRARY.getTextureID("steel-mrao");
            const gl::Texture2D& woodAlbedoTexture = CB_TEXTURE_LIBRARY.getTexture2D(woodAlbedo);
            const gl::Texture2D& woodNormalTexture = CB_TEXTURE_LIBRARY.getTexture2D(woodNormal);
            const gl::Texture2D& woodMraoTexture = CB_TEXTURE_LIBRARY.getTexture2D(woodMrao);
            const gl::Texture2D& steelAlbedoTexture = CB_TEXTURE_LIBRARY.getTexture2D(steelAlbedo);
            const gl::Texture2D& steelNormalTexture = CB_TEXTURE_LIBRARY.getTexture2D(steelNormal);
            const gl::Texture2D& steelMraoTexture = CB_TEXTURE_LIBRARY.getTexture2D(steelMrao);
            const gl::Texture2D& gridTexture = CB_TEXTURE_LIBRARY.getTexture2D(0, 0, 250, 3);

            gfx::Material& woodMaterial = CB_MATERIAL_LIBRARY.getMaterial(CB_MATERIAL_LIBRARY.makePBR("wood", woodAlbedo, woodNormal, woodMrao));
            gfx::Material& steelMaterial = CB_MATERIAL_LIBRARY.getMaterial(CB_MATERIAL_LIBRARY.makePBR("steel", steelAlbedo, steelNormal, steelMrao));
            gfx::Material& whiteRough = CB_MATERIAL_LIBRARY.getMaterial(CB_MATERIAL_LIBRARY.makePBR("white", COLOR_WHITE, 0.0f, 1.0f, 1.0f));
            gfx::Material& whiteSmooth = CB_MATERIAL_LIBRARY.getMaterial(CB_MATERIAL_LIBRARY.makePBR("white", COLOR_WHITE, 0.0f, 0.0f, 1.0f));
            gfx::Material& orangeMedium = CB_MATERIAL_LIBRARY.getMaterial(CB_MATERIAL_LIBRARY.makePBR("orange", COLOR_ORANGE, 0.0f, 0.5f, 1.0f));
            UMap<std::string, const core::gl::Texture2D&> gridTextures = {{"settings", gridTexture}};
            gfx::Material& gridMaterial = CB_MATERIAL_LIBRARY.getMaterial(CB_MATERIAL_LIBRARY.makeFromShader("grid", "grid", gridTextures));
            gfx::Mesh rotatingCube = gfx::MeshFactory::createCube(5, woodMaterial);
            gfx::Mesh ground = gfx::MeshFactory::createRectangle(100, 100, woodMaterial);
            gfx::Mesh sphere = gfx::MeshFactory::createSphere(5, woodMaterial);
            gfx::Mesh cube0 = gfx::MeshFactory::createCube(10, whiteRough);
            gfx::Mesh cube1 = gfx::MeshFactory::createCube(10, whiteSmooth);
            gfx::Mesh cube2 = gfx::MeshFactory::createCube(10, orangeMedium);
            ground.translate(glm::vec3(0.0f, 0.0f, 0.0f));
            ground.rotate(glm::vec3(90.0f, 0.0f, 0.0f));
            rotatingCube.translate(glm::vec3(-10.0f, 10.0f, 0.0f));
            cube0.translate(glm::vec3(0.0f, 5.0f, 25.0f));
            cube1.translate(glm::vec3(-25.0f, 10.0f, 0.0f));
            cube2.translate(glm::vec3(0.0f, 5.0f, -40.0f));
            sphere.translate(glm::vec3(10.0f, 5.0f, 0.0f));
            cube0.rotate(glm::vec3(0.0f, 30.0f, 0.0f));
            cube1.rotate(glm::vec3(0.0f, 15.0f, 0.0f));
            cube2.rotate(glm::vec3(0.0f, 45.0f, 0.0f));
            scene.addMesh(Move(rotatingCube));
            scene.addMesh(Move(ground));
            scene.addMesh(Move(sphere));
            scene.addMesh(Move(cube0));
            scene.addMesh(Move(cube1));
            scene.addMesh(Move(cube2));

            gfx::Mesh grid = gfx::MeshFactory::createGrid(1, gridMaterial);
            grid.translate(glm::vec3(-10.0f, 0.01f, -10.0f));
            grid.scale(glm::vec3(10000.0f, 1.0f, 10000.0f));
            scene.addMesh(Move(grid));
        }
    }  // namespace editor
}  // namespace cobalt

cobalt::engine::Application* cobalt::engine::createApplication() { return new cobalt::editor::Editor(); }