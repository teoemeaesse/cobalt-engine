//
// Created by tomas on 07-12-2023.
//

#include "editor/persistency/cobalt_configuration.h"
#include "editor/input/bindings.h"
#include "core/gfx/render_node.h"


static void printMat4(const glm::mat4& mat) {
    CB_INFO("0x0={0}, 0x1={1}, 0x2={2}, 0x3={3}", mat[0][0], mat[0][1], mat[0][2], mat[0][3]);
    CB_INFO("1x0={0}, 1x1={1}, 1x2={2}, 1x3={3}", mat[1][0], mat[1][1], mat[1][2], mat[1][3]);
    CB_INFO("2x0={0}, 2x1={1}, 2x2={2}, 2x3={3}", mat[2][0], mat[2][1], mat[2][2], mat[2][3]);
    CB_INFO("3x0={0}, 3x1={1}, 3x2={2}, 3x3={3}", mat[3][0], mat[3][1], mat[3][2], mat[3][3]);
}

namespace cobalt {
    namespace editor {
        class Editor : public engine::Application {
            public:
            Editor() : engine::Application(1),
                       configuration(CobaltConfiguration()),
                       outputCamera(glm::vec3(0.0, 0.0, 10.0),
                         glm::vec2(0.0, 0.0),
                         1.57079633f,
                         0.1f,
                         1.0f, 1000.0f,
                         16.0f/9.0f)
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
                core::Mesh mesh = core::Mesh::createRectangle(20, 10, material);
                scene.addMesh(std::move(mesh));

                defaultTarget = new core::RenderTarget(getWindow().getDefaultFBO(), outputCamera, "default");
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
                //outputCamera.resize(0, getWindow().getWidth(), 0, getWindow().getHeight());

                renderer.setTarget(defaultTarget);
                renderer.render(scene.getMeshes()[0]);

                outputCamera.rotateHorizontal(0.01f);

                getWindow().swapBuffers();

                //renderGraph.execute();
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
            
            core::Renderer renderer;
            core::RenderTarget* defaultTarget;
            core::PerspectiveCamera outputCamera;
        };
    }
}

cobalt::engine::Application *cobalt::engine::createApplication() {
    return new cobalt::editor::Editor();
}