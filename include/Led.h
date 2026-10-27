#pragma once

#include <Arduino.h>

enum class LedState {
    On,
    Off
};

class Led {
    public:
        void init();
        void set(LedState state);
};

void initMode(Led& led, uint32_t now);

void updateMode(Led& led, bool pressed, uint32_t now);
