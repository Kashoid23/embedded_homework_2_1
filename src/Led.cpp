#include "Led.h"
#include "Config.h"

void Led::init() {
    pinMode(Config::LED_PIN, OUTPUT);
    set(LedState::Off);
}

void Led::set(LedState state) {
    digitalWrite(Config::LED_PIN, state == LedState::On ? HIGH : LOW);
}

enum class Mode { Blinking, AlwaysOn, AlwaysOff };

static Mode mode = Mode::Blinking;

static LedState ledState = LedState::Off;
static uint32_t lastBlinkTime = 0;

static void setMode(Led& led, Mode newMode, uint32_t now) {
    mode = newMode;

    switch (mode) {
        case Mode::Blinking:
            ledState = LedState::On;
            lastBlinkTime = now;
            led.set(ledState);
            Serial.println("Mode: Blinking");
            break;

        case Mode::AlwaysOn:
            led.set(LedState::On);
            Serial.println("Mode: AlwaysOn");
            break;

        case Mode::AlwaysOff:
            led.set(LedState::Off);
            Serial.println("Mode: AlwaysOff");
            break;
    }
}

void initMode(Led& led, uint32_t now) {
    setMode(led, Mode::Blinking, now);
}

void updateMode(Led& led, bool pressed, uint32_t now) {
    switch (mode) {
        case Mode::Blinking:
            if (pressed) {
                setMode(led, Mode::AlwaysOn, now);
                break;
            }
            if (now - lastBlinkTime >= Config::BLINK_INTERVAL_MS) {
                lastBlinkTime = now;
                ledState = (ledState == LedState::On) ? LedState::Off : LedState::On;
                led.set(ledState);
            }
            break;

        case Mode::AlwaysOn:
            if (pressed) {
                setMode(led, Mode::AlwaysOff, now);
            }
            break;

        case Mode::AlwaysOff:
            if (pressed) {
                setMode(led, Mode::Blinking, now);
            }
            break;
    }
}
