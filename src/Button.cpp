#include "Button.h"
#include "Config.h"

static volatile bool buttonFlag = false;

static void IRAM_ATTR onButtonChange() {
    buttonFlag = true;
}

void Button::init() {
    pinMode(Config::BUTTON_PIN, INPUT);
    attachInterrupt(digitalPinToInterrupt(Config::BUTTON_PIN), onButtonChange, CHANGE);
}

bool Button::pressed(uint32_t now) {
    if (buttonFlag) {
        buttonFlag = false;
        lastChangeMs = now;
    }

    if (now - lastChangeMs < Config::DEBOUNCE_MS) {
        return false;
    }

    const bool isPressed = digitalRead(Config::BUTTON_PIN) == LOW;
    const bool newPress = isPressed && !wasPressed;
    wasPressed = isPressed;
    return newPress;
}
