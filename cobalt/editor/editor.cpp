//
// Created by tomas on 07-12-2023.
//

#include "editor/persistency/cobalt_configuration.h"
#include "editor/input/bindings.h"
#include "core/gfx/render_node.h"


namespace cobalt {
    namespace editor {
        class Editor : public engine::Application {
            public:
            Editor() : engine::Application(1),
                       configuration(CobaltConfiguration()),
                       outputCamera(glm::vec3(1.0, 1.0, 10.0),
                         glm::vec2(0.0, 0.0),
                         90.0f,
                         0.1f,
                         0.0f, 1000.0f,
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
                //std::unique_ptr<core::Mesh> testMesh = std::make_unique<core::Mesh>(core::Mesh::createRectangle(1000, 1000, core::Material(testShader, testTexture, testTexture, testTexture)));
                //scene.addMesh(std::move(testMesh));
                
                core::Material* material = new core::Material(testShader, testTexture, testTexture, testTexture);
                scene.addMesh(core::Mesh::createRectangle(1000, 1000, material));

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

                //renderer.setTarget(defaultTarget);
                //renderer.render(*scene.getMeshes()[0]);
/*
                defaultTarget->bind();

                core::Mesh mesh = core::Mesh::createRectangle(1000, 1000, core::Material(CB_SHADER_LIBRARY.getShader(CB_SHADER_LIBRARY.getShaderID("test_shader")), CB_TEXTURE_LIBRARY.getTexture(CB_TEXTURE_LIBRARY.getTextureID("test_texture")), CB_TEXTURE_LIBRARY.getTexture(CB_TEXTURE_LIBRARY.getTextureID("test_texture")), CB_TEXTURE_LIBRARY.getTexture(CB_TEXTURE_LIBRARY.getTextureID("test_texture"))));

                const float w = 2.0f;
                const float h = 2.0f;

                const float vertices[] = {
                    -w, -h, 0.0f, 0.0f, 0.0f,
                    w, -h, 0.0f, 1.0f, 0.0f,
                    w,  h, 0.0f, 1.0f, 1.0f,
                    -w,  h, 0.0f, 0.0f, 1.0f
                };

                core::VBO vbo(core::GLUsage::StaticDraw);
                vbo.bind();
                vbo.load(vertices, sizeof(float) * 20);

                core::VAOLayout layout;
                layout.push(core::GLType::Float, 3, false);   // Position.
                layout.push(core::GLType::Float, 2, false);   // Texture coordinates.
                core::VAO vao(vbo, layout);
                vao.bind();

                core::IBO ibo = core::IBO::fromQuads(core::GLUsage::StaticDraw, 1);
                ibo.bind();

                core::Shader& shader = CB_SHADER_LIBRARY.getShader(CB_SHADER_LIBRARY.getShaderID("test_shader"));
                shader.use();
                glBindFramebuffer(GL_FRAMEBUFFER, 0);
                glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
*/
                //outputCamera.rotateHorizontal(0.01f);

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