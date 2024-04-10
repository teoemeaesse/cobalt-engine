// Created by tomas on
// 07-12-2023

#include "editor/editor.h"

#include "editor/input/bindings.h"
#include "engine/bundle/base.h"
#include "engine/input/exception.h"
#include "engine/window/plugin.h"

namespace cobalt {
    namespace editor {
        using namespace core;
        using namespace engine;

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
            world.addHook<core::ecs::ReadRequest<Window>, core::ecs::WriteRequest<CameraManager>, core::ecs::WriteRequest<DefaultGraph>,
                          core::ecs::WriteRequest<engine::Scene>>(
                WindowPlugin::FRAMEBUFFER_RESIZE_EVENT, [](auto window, auto manager, auto graph, auto scene) {
                    const uint width = window.get().getDefaultFBO().getWidth();
                    const uint height = window.get().getDefaultFBO().getHeight();
                    graph.get().onResize(width, height);
                    manager.get().getController(scene.get().getCameraID()).resize((float)width / (float)height);
                });

            CB_TEXTURE_LIBRARY.loadTextures(io::Path("cobalt/editor/assets/textures", true));
            CB_SHADER_LIBRARY.loadShaders(io::Path("cobalt/editor/assets/shaders", true));

            CameraManager& cameraManager = world.getResource<engine::CameraManager>();

            world.addResource<engine::Scene>(cameraManager);
            createScene();

            world.addResource<DefaultGraph>(world.getResource<engine::Scene>(), cameraManager, getWindow().getDefaultFBO());
            world.getResource<DefaultGraph>().init(world.getResource<engine::CameraManager>());

            bindInput();
        }

        void Editor::addPlugins() { world.addBundle<engine::ecs::BaseBundle>(); }

        void Editor::fixedTimeStep() {
            CameraManager& manager = world.getResource<CameraManager>();
            manager.getController(world.getResource<engine::Scene>().getCameraID()).update();
            getWindow().setTitle("Cobalt Editor - " + std::to_string(getFramerate()) + " FPS");
        }

        void Editor::variableTimeStep(const float delta) {
            auto& scene = world.getResource<engine::Scene>();
            auto& cameraManager = world.getResource<engine::CameraManager>();
            scene.getMeshes()[0].rotate(glm::vec3(30.0f * delta, 5.0f * delta, 20.0f * delta));
            static float cubeXOffset = 0.0f;
            static float cubeYOffset = 0.0f;
            static float time = 0.0f;
            time += delta;
            cubeXOffset = sin(time) * 25.0f * delta;
            cubeYOffset = cos(time) * 25.0f * delta;
            scene.getMeshes()[4].translate(glm::vec3(cubeXOffset, 0.0f, cubeYOffset));
            world.getResource<DefaultGraph>().execute(cameraManager);
        }

        void Editor::bindInput() {
            /**
             * Two try-catch blocks are used to catch both the Keyboard and Mouse peripheral exceptions.
             * Likely to be useless since the Keyboard and Mouse peripherals are always present in the engine.
             */
            engine::Scene& scene = world.getResource<engine::Scene>();
            engine::Keyboard& keyboard = getInputManager().getPeripheral<engine::Keyboard>(engine::Keyboard::NAME);
            CameraID* camera = &scene.getCameraID();
            keyboard.bind(engine::KeyboardInputID::ESCAPE, CreateScope<Quit>(world, this));
            keyboard.bind(engine::KeyboardInputID::F9, CreateScope<Windowed>(world, this));
            keyboard.bind(engine::KeyboardInputID::F10, CreateScope<Borderless>(world, this));
            keyboard.bind(engine::KeyboardInputID::F11, CreateScope<Fullscreen>(world, this));
            keyboard.bind(engine::KeyboardInputID::W, CreateScope<PanIn>(world, camera));
            keyboard.bind(engine::KeyboardInputID::A, CreateScope<PanLeft>(world, camera));
            keyboard.bind(engine::KeyboardInputID::S, CreateScope<PanOut>(world, camera));
            keyboard.bind(engine::KeyboardInputID::D, CreateScope<PanRight>(world, camera));
            keyboard.bind(engine::KeyboardInputID::SPACE, CreateScope<PanUp>(world, camera));
            keyboard.bind(engine::KeyboardInputID::LCTRL, CreateScope<PanDown>(world, camera));
            keyboard.bind(engine::KeyboardInputID::UP, CreateScope<PanUp>(world, camera));
            keyboard.bind(engine::KeyboardInputID::LEFT, CreateScope<PanLeft>(world, camera));
            keyboard.bind(engine::KeyboardInputID::DOWN, CreateScope<PanDown>(world, camera));
            keyboard.bind(engine::KeyboardInputID::RIGHT, CreateScope<PanRight>(world, camera));
            keyboard.bind(engine::KeyboardInputID::P, CreateScope<Spawn>(world, &scene));

            Mouse& mouse = getInputManager().getPeripheral<Mouse>(Mouse::NAME);
            mouse.bind(MouseInputID::RIGHT_X, CreateScope<RotateX>(world, camera));
            mouse.bind(MouseInputID::RIGHT_Y, CreateScope<RotateY>(world, camera));
            mouse.bind(MouseInputID::SCROLL_Y, CreateScope<Zoom>(world, camera));
        }

        void Editor::createScene() {
            engine::Scene& scene = world.getResource<engine::Scene>();
            scene.clear();
            scene.setSkybox(Skybox::create(CB_TEXTURE_LIBRARY.getTexture<gl::Texture3D>("skybox"), CB_SHADER_LIBRARY.getShader("skybox")));
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
            Mesh rotatingCube = MeshFactory::createCube(5, woodMaterial);
            Mesh ground = MeshFactory::createRectangle(100, 100, woodMaterial);
            Mesh sphere = MeshFactory::createSphere(5, woodMaterial);
            Mesh cube0 = MeshFactory::createCube(10, whiteRough);
            Mesh cube1 = MeshFactory::createCube(10, whiteSmooth);
            Mesh cube2 = MeshFactory::createCube(10, orangeMedium);
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
            Mesh grid = MeshFactory::createGrid(10000, gridMaterial);
            scene.addMesh(Move(grid));
        }
    }  // namespace editor
}  // namespace cobalt

cobalt::engine::Application* cobalt::engine::createApplication() { return new cobalt::editor::Editor(); }