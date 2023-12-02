//
// Created by tomas on 29-11-2023.
//

#include "engine/cobalt.h"


using namespace cobalt;

class Game : public engine::Application {
public:
    Game() {
        core::Window window = core::WindowBuilder()
            .setTitle("cobalt example")
            .setWidth(1280)
            .setHeight(720)
            .setVsync(true)
            .setMode(core::WindowMode::Windowed)
            .setResizable(false)
            .setDecorated(true)
            .build();

        window.show();
    }

    ~Game() {
    }

    void fixedTimeStep() override {
    }

    void variableTimeStep(float delta) override {
    }
};

engine::Application *engine::createApplication() {
    return new Game();
}