//
// Created by tomas on 29-11-2023.
//

#include "engine/cobalt.h"


using namespace cobalt;

class Game : public engine::Application {
    public:
    Game() : engine::Application(1), window(core::WindowBuilder()
            .setTitle("cobalt example")
            .setWidth(1280)
            .setHeight(720)
            .setVsync(true)
            .setMode(core::WindowMode::Windowed)
            .setResizable(false)
            .setDecorated(true)
            .build()) {
        window.show();
    }

    ~Game() override {
        
    }

    void fixedTimeStep() override {
        CB_INFO("Framerate: {0}", getFramerate());
        CB_INFO("Fixed time step");
    }

    void variableTimeStep(float delta) override {
        if (window.shouldClose()) {
            stop();
        }
        window.pollEvents();
        window.swapBuffers();
    }

    private:
    core::Window window;
};

engine::Application *engine::createApplication() {
    return new Game();
}