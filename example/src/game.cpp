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
            .build()) {
        window.show();
        window.setClearColor(COLOR_BLUE);
        getInputManager().getKeyboard().bind(core::KeyboardInputID::ESCAPE, std::make_unique<Quit>(this));
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
};

engine::Application *engine::createApplication() {
    return new Game();
}