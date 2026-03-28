#ifndef LEDBAR_H
#define LEDBAR_H

#include <Arduino.h>

template<size_t ledPinSize>

class LedBar {
    private:
        const uint8_t ledPin[ledPinSize];
        uint8_t potentiometerPin;

        uint16_t pot_result;
        uint8_t scale;

        uint8_t i;
    public:
        template<typename... Args>
        LedBar(Args... pins) : ledPin{static_cast<uint8_t>(pins)...} {
            static_assert(sizeof...(Args) == ledPinSize, "Wrong quantity of pins");
        }

        void begin(const uint8_t potentiometerPin) {
            this->potentiometerPin = potentiometerPin;
            for (i = 0; i < ledPinSize; ++i)
                pinMode(ledPin[i], OUTPUT);
        }

        void drawChart() {
            pot_result = analogRead(potentiometerPin);

            scale = (pot_result * ledPinSize) >> 10;

            for (i = 0; i < scale; ++i)
                digitalWrite(ledPin[i], HIGH);

            for (i = scale; i < ledPinSize; ++i)
                digitalWrite(ledPin[i], LOW);
        }
};

template<typename... Args>
LedBar(Args...) -> LedBar<sizeof...(Args)>;

#endif