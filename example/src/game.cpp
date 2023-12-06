//
// Created by tomas on 29-11-2023.
//

#include "engine/cobalt.h"
#include "engine/application.h"


using namespace cobalt;

class Quit : public core::ConcreteInputCommand<engine::Application> {
    public:
    Quit(engine::Application* target) : core::ConcreteInputCommand<engine::Application>(target) {
    }
    void execute() const override {
        getTarget()->stop();
    }
};

class Fullscreen : public core::ConcreteInputCommand<core::Window> {
    public:
    Fullscreen(core::Window* target) : core::ConcreteInputCommand<core::Window>(target) {
    }
    void execute() const override {
        if (!getInput().active) {
            getTarget()->switchMode(core::WindowMode::Fullscreen);
        }
    }
};

class Borderless : public core::ConcreteInputCommand<core::Window> {
    public:
    Borderless(core::Window* target) : core::ConcreteInputCommand<core::Window>(target) {
    }
    void execute() const override {
        if (!getInput().active) {
            getTarget()->switchMode(core::WindowMode::Borderless);
        }
    }
};

class Windowed : public core::ConcreteInputCommand<core::Window> {
    public:
    Windowed(core::Window* target) : core::ConcreteInputCommand<core::Window>(target) {
    }
    void execute() const override {
        if (!getInput().active) {
            getTarget()->switchMode(core::WindowMode::Windowed);
        }
    }
};

class Game : public engine::Application {
    public:
    Game() : engine::Application(1), window(core::WindowBuilder()
            .setTitle("cobalt example")
            .setWidth(1280)
            .setHeight(720)
            .setVsync(false)
            .setMode(core::WindowMode::Windowed)
            .setResizable(true)
            .setDecorated(true)
            .build()),
            shaderLibrary() {
        window.show();
        window.setClearColor(COLOR(0.2f, 0.2f, 0.2f, 1.0f));
        getInputManager().getKeyboard().bind(core::KeyboardInputID::ESCAPE, std::make_unique<Quit>(this));
        getInputManager().getKeyboard().bind(core::KeyboardInputID::F9, std::make_unique<Windowed>(&window));
        getInputManager().getKeyboard().bind(core::KeyboardInputID::F10, std::make_unique<Borderless>(&window));
        getInputManager().getKeyboard().bind(core::KeyboardInputID::F11, std::make_unique<Fullscreen>(&window));

        shaderLibrary.loadShaders(cobalt::core::Path("example/assets/shaders/", true));
    }

    ~Game() override {
        
    }

    void fixedTimeStep() override {
        CB_INFO("Fps: {0}", getFramerate());
    }

    void variableTimeStep(float delta) override {
        if (window.shouldClose()) {
            stop();
        }
        window.clear();

        getInputManager().pollEvents();
        getInputManager().clearEvents();

        window.swapBuffers();
    }

    private:
    core::Window window;
    engine::ShaderLibrary shaderLibrary;
};

engine::Application *engine::createApplication() {
    return new Game();
}