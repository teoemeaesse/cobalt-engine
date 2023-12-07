//
// Created by tomas on 07-12-2023.
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

class Editor : public engine::Application {
    public:
    Editor() : engine::Application(1), window(core::WindowBuilder()
            .setTitle("Cobalt")
            .setWidth(600)
            .setHeight(600)
            .setVsync(false)
            .setMode(core::WindowMode::Windowed)
            .setResizable(true)
            .build()) {
        window.show();
        window.setClearColor(COLOR(0.2f, 0.2f, 0.2f, 1.0f));
        getInputManager().getKeyboard().bind(core::KeyboardInputID::ESCAPE, std::make_unique<Quit>(this));
        getInputManager().getKeyboard().bind(core::KeyboardInputID::F9, std::make_unique<Windowed>(&window));
        getInputManager().getKeyboard().bind(core::KeyboardInputID::F10, std::make_unique<Borderless>(&window));
        getInputManager().getKeyboard().bind(core::KeyboardInputID::F11, std::make_unique<Fullscreen>(&window));
    }

    ~Editor() override {
        
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
};

engine::Application *engine::createApplication() {
    return new Editor();
}