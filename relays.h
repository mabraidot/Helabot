#include <Arduino.h>

#define RELAY_1_PIN 5
#define RELAY_2_PIN 6


void relays_init(void)
{
    pinMode(RELAY_1_PIN, OUTPUT);
    pinMode(RELAY_2_PIN, OUTPUT);
    digitalWrite(RELAY_1_PIN, HIGH);
    digitalWrite(RELAY_2_PIN, HIGH);
}

void relays_enable(int index = 1) {
    if (index == 1) {
        digitalWrite(RELAY_1_PIN, LOW);
    }
    if (index == 2) {
        digitalWrite(RELAY_2_PIN, LOW);
    }
}

void relays_disable(int index = 1) {
    if (index == 1) {
        digitalWrite(RELAY_1_PIN, HIGH);
    }
    if (index == 2) {
        digitalWrite(RELAY_2_PIN, HIGH);
    }
}