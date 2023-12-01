//
// Created by tomas on 29-11-2023.
//

#pragma once


namespace cobalt {
    namespace engine {
        class Application {
            public:
            Application();
            virtual ~Application();

            virtual void run();
        };

        Application *createApplication();
    }
}