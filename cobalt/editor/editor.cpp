// Created by tomas on
// 07-12-2023

#include "editor/editor.h"

#include "core/input/exception.h"
#include "editor/input/bindings.h"
#include "engine/ecs/plugin/bundle/base.h"
#include "engine/ecs/plugin/gfx/window.h"

namespace cobalt {
    namespace editor {
        using namespace cobalt::core;
        using namespace cobalt::engine;

        Editor::Editor() : Application(144), configuration(CobaltConfiguration()) {}

        Editor::~Editor() {
            configuration.set("width", getWindow().getWidth());
            configuration.set("height", getWindow().getHeight());
            configuration.set("vsync", getWindow().isVsync());
            configuration.set("mode", static_cast<size_t>(getWindow().getMode()));
            configuration.serialize(io::Path("cobalt-config.json", true));
        }

        void Editor::setup() {
            configuration.configureWindow(getWindow());
            getWindow().setClearColor(Color(0.2f, 0.2f, 0.2f));
            getWindow().show();
            world.addHook<core::ecs::ReadRequest<gfx::Window>, core::ecs::WriteRequest<DefaultGraph>, core::ecs::WriteRequest<scene::Scene>>(
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

        void Editor::addPlugins() { world.addBundle<engine::ecs::BaseBundle>(); }

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
            /**
             * Two try-catch blocks are used to catch both the Keyboard and Mouse peripheral exceptions.
             * Likely to be useless since the Keyboard and Mouse peripherals are always present in the engine.
             */
            scene::Scene& scene = world.getResource<scene::Scene>();

            engine::Keyboard& keyboard = getInputManager().getPeripheral<engine::Keyboard>(engine::Keyboard::NAME);
            keyboard.bind(engine::KeyboardInputID::ESCAPE, createScope<Quit>(world, this));
            keyboard.bind(engine::KeyboardInputID::F9, createScope<Windowed>(world, this));
            keyboard.bind(engine::KeyboardInputID::F10, createScope<Borderless>(world, this));
            keyboard.bind(engine::KeyboardInputID::F11, createScope<Fullscreen>(world, this));
            keyboard.bind(engine::KeyboardInputID::W, createScope<PanIn>(world, &scene.getCameraController()));
            keyboard.bind(engine::KeyboardInputID::A, createScope<PanLeft>(world, &scene.getCameraController()));
            keyboard.bind(engine::KeyboardInputID::S, createScope<PanOut>(world, &scene.getCameraController()));
            keyboard.bind(engine::KeyboardInputID::D, createScope<PanRight>(world, &scene.getCameraController()));
            keyboard.bind(engine::KeyboardInputID::SPACE, createScope<PanUp>(world, &scene.getCameraController()));
            keyboard.bind(engine::KeyboardInputID::LCTRL, createScope<PanDown>(world, &scene.getCameraController()));
            keyboard.bind(engine::KeyboardInputID::UP, createScope<PanUp>(world, &scene.getCameraController()));
            keyboard.bind(engine::KeyboardInputID::LEFT, createScope<PanLeft>(world, &scene.getCameraController()));
            keyboard.bind(engine::KeyboardInputID::DOWN, createScope<PanDown>(world, &scene.getCameraController()));
            keyboard.bind(engine::KeyboardInputID::RIGHT, createScope<PanRight>(world, &scene.getCameraController()));
            keyboard.bind(engine::KeyboardInputID::P, createScope<Spawn>(world, &scene));

            engine::Mouse& mouse = getInputManager().getPeripheral<engine::Mouse>(engine::Mouse::NAME);
            mouse.bind(engine::MouseInputID::RIGHT_X, createScope<RotateX>(world, &scene.getCameraController()));
            mouse.bind(engine::MouseInputID::RIGHT_Y, createScope<RotateY>(world, &scene.getCameraController()));
            mouse.bind(engine::MouseInputID::SCROLL_Y, createScope<Zoom>(world, &scene.getCameraController()));
        }

        void Editor::createScene() {
            scene::Scene& scene = world.getResource<scene::Scene>();
            scene.clear();
            scene.setSkybox(gfx::Skybox::create(CB_TEXTURE_LIBRARY.getTexture<gl::Texture3D>("skybox"), CB_SHADER_LIBRARY.getShader("skybox")));
            const TextureID woodAlbedo = CB_TEXTURE_LIBRARY.getTextureID("wood-albedo");
            const TextureID woodNormal = CB_TEXTURE_LIBRARY.getTextureID("wood-normal");
            const TextureID woodMrao = CB_TEXTURE_LIBRARY.getTextureID("wood-mrao");
            const TextureID steelAlbedo = CB_TEXTURE_LIBRARY.getTextureID("steel-albedo");
            const TextureID steelNormal = CB_TEXTURE_LIBRARY.getTextureID("steel-normal");
            const TextureID steelMrao = CB_TEXTURE_LIBRARY.getTextureID("steel-mrao");
            const gl::Texture2D& woodAlbedoTexture = CB_TEXTURE_LIBRARY.getTexture<gl::Texture2D>(woodAlbedo);
            const gl::Texture2D& woodNormalTexture = CB_TEXTURE_LIBRARY.getTexture<gl::Texture2D>(woodNormal);
            const gl::Texture2D& woodMraoTexture = CB_TEXTURE_LIBRARY.getTexture<gl::Texture2D>(woodMrao);
            const gl::Texture2D& steelAlbedoTexture = CB_TEXTURE_LIBRARY.getTexture<gl::Texture2D>(steelAlbedo);
            const gl::Texture2D& steelNormalTexture = CB_TEXTURE_LIBRARY.getTexture<gl::Texture2D>(steelNormal);
            const gl::Texture2D& steelMraoTexture = CB_TEXTURE_LIBRARY.getTexture<gl::Texture2D>(steelMrao);

            gfx::Material& woodMaterial = CB_MATERIAL_LIBRARY.getMaterial(CB_MATERIAL_LIBRARY.makePBR("wood", woodAlbedo, woodNormal, woodMrao));
            gfx::Material& steelMaterial = CB_MATERIAL_LIBRARY.getMaterial(CB_MATERIAL_LIBRARY.makePBR("steel", steelAlbedo, steelNormal, steelMrao));
            gfx::Material& whiteRough = CB_MATERIAL_LIBRARY.getMaterial(CB_MATERIAL_LIBRARY.makePBR("white", Colors::White, 0.0f, 1.0f, 1.0f));
            gfx::Material& whiteSmooth = CB_MATERIAL_LIBRARY.getMaterial(CB_MATERIAL_LIBRARY.makePBR("white", Colors::White, 0.0f, 0.0f, 1.0f));
            gfx::Material& orangeMedium = CB_MATERIAL_LIBRARY.getMaterial(CB_MATERIAL_LIBRARY.makePBR("orange", Colors::Orange, 0.0f, 0.5f, 1.0f));
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

            char color[4] = {(char)0, (char)0, (char)250, (char)3};
            const gl::Texture2D& gridTexture =
                CB_TEXTURE_LIBRARY.getTexture<gl::Texture2D>(CB_TEXTURE_LIBRARY.makeTexture("grid", color, gl::TextureEncodings::RGBA::Bits8));
            UMap<std::string, const core::gl::Texture2D&> gridTextures = {{"settings", gridTexture}};
            gfx::Material& gridMaterial = CB_MATERIAL_LIBRARY.getMaterial(CB_MATERIAL_LIBRARY.makeFromShader("grid", "grid", gridTextures));
            gfx::Mesh grid = gfx::MeshFactory::createGrid(10000, gridMaterial);
            scene.addMesh(Move(grid));
        }
    }  // namespace editor
}  // namespace cobalt

cobalt::engine::Application* cobalt::engine::createApplication() { return new cobalt::editor::Editor(); }