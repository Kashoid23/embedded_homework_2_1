#pragma once

#include <Arduino.h>

class Button {
    public:
        void init();
        bool pressed(uint32_t now);

    private:
        uint32_t lastChangeMs = 0;
        bool wasPressed = true;
};
