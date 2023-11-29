//
// Created by tomas on 29-11-2023.
//

#include "engine/cobalt.h"


class Game : public cobalt::Application {
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

cobalt::Application *cobalt::createApplication() {
    return new Game();
}