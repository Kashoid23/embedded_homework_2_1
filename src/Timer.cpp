#include "Timer.h"
#include "Config.h"

void measureLoop(uint32_t durationUs) {
    static uint32_t iterations = 0;
    static uint64_t totalUs = 0;
    static uint32_t maxUs = 0;

    iterations++;
    totalUs += durationUs;
    if (durationUs > maxUs) {
        maxUs = durationUs;
    }

    if (iterations < Config::REPORT_EVERY_ITERATIONS) {
        return;
    }

    Serial.printf("Loop: avg %lu us, max %lu us\n",
                  static_cast<unsigned long>(totalUs / iterations),
                  static_cast<unsigned long>(maxUs));

    iterations = 0;
    totalUs = 0;
    maxUs = 0;
}
