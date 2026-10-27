#pragma once

#include <Arduino.h>

struct Config {
    static constexpr uint8_t LED_PIN = 2;
    static constexpr uint8_t BUTTON_PIN = 4;

    static constexpr uint32_t BLINK_INTERVAL_MS = 500;
    static constexpr uint32_t DEBOUNCE_MS = 30;

    static constexpr uint32_t REPORT_EVERY_ITERATIONS = 1000;
    static constexpr uint32_t BAUD_RATE = 115200;
};
