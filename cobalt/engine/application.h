//
// Created by tomas on 29-11-2023.
//

#pragma once


namespace cobalt {
    class Application {
    public:
        Application();
        virtual ~Application();

        virtual void run();
    };

    Application *createApplication();
}