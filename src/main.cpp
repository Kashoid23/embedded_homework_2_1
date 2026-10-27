#include <Arduino.h>

#include "Button.h"
#include "Config.h"
#include "Led.h"
#include "Timer.h"

Led led;
Button button;

void setup() {
    Serial.begin(Config::BAUD_RATE);

    led.init();
    button.init();
    initMode(led, millis());
}

void loop() {
    const uint32_t startUs = micros();
    const uint32_t now = millis();

    updateMode(led, button.pressed(now), now);

    measureLoop(micros() - startUs);
}
