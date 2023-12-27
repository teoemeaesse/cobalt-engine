//
// Created by tomas on 27-12-2023.
//

#pragma once

#include "core/pch.h"


namespace cobalt {
    namespace core {
        /** Interface between GLFW key codes and Cobalt key codes.
         */
        class KeyCodes {
            public:
            using PeripheralID = int;

            /** Initialize the key codes singleton.
             */
            static void init();
            /** Registers a new peripheral.
             * @param name: The name of the peripheral.
             * @return: The peripheral's handle.
             */
            static const PeripheralID registerPeripheral(const std::string& name);
            /** Get the name of a peripheral, given its registered handle.
             * @param peripheral: The peripheral id.
             * @return: The name of the peripheral.
             */
            static const std::string& peripheralToString(const PeripheralID peripheral);


            private:
            UMap<std::string, PeripheralID> peripheralIDs;

            static Scope<KeyCodes> instance;
        };
    }
}