//
// Created by tomas on 29-11-2023.
//

#include "engine/cobalt.h"


class Game : public cobalt::engine::Application {
public:
    Game() {

    }

    ~Game() {

    }

    void run() override {
        while (true) {
            CB_INFO("Game is running!");
        }
    }
};

cobalt::engine::Application *cobalt::engine::createApplication() {
    return new Game();
}