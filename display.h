#include <Arduino.h>

#define SHIFT_DATA_PIN 0
#define SHIFT_LATCH_PIN 1
#define SHIFT_CLOCK_PIN 2

void display_init(void)
{
    pinMode(SHIFT_LATCH_PIN, OUTPUT);
    pinMode(SHIFT_DATA_PIN, OUTPUT);
    pinMode(SHIFT_CLOCK_PIN, OUTPUT);
}

/*
    A
  F   B
    G
  E   C
    D   DP

  A B C D E F G DP
*/
const byte digit_pattern[18] = {
        B11111100, // 0
        B01100000, // 1
        B11011010, // 2
        B11110010, // 3
        B01100110, // 4
        B10110110, // 5
        B10111110, // 6
        B11100000, // 7
        B11111110, // 8
        B11110110, // 9
        B11101110, // A
        B00111110, // b
        B10011100, // C
        B01111010, // d
        B10011110, // E
        B10001110, // F
        B00000001,  // .
        B00001010 // r
};

/*
 * This function update the number in the 7-segment displays
 */
void display_number(float count)
{
    uint8_t tens = 0;
    uint8_t ones = 0;
    uint8_t tenths = 0;

    tens = floor(count / 10);
    ones = floor(count) - (tens * 10);
    tenths = round((count - floor(count)) * 10);

    digitalWrite(SHIFT_LATCH_PIN, LOW);
    shiftOut(SHIFT_DATA_PIN, SHIFT_CLOCK_PIN, LSBFIRST, digit_pattern[abs(tens)]);
    shiftOut(SHIFT_DATA_PIN, SHIFT_CLOCK_PIN, LSBFIRST, digit_pattern[abs(ones)] | digit_pattern[16]); // Show number with decimal point
    shiftOut(SHIFT_DATA_PIN, SHIFT_CLOCK_PIN, LSBFIRST, digit_pattern[abs(tenths)]);
    digitalWrite(SHIFT_LATCH_PIN, HIGH);
}


void display_error(void)
{
    digitalWrite(SHIFT_LATCH_PIN, LOW);
    shiftOut(SHIFT_DATA_PIN, SHIFT_CLOCK_PIN, LSBFIRST, digit_pattern[14]);
    shiftOut(SHIFT_DATA_PIN, SHIFT_CLOCK_PIN, LSBFIRST, digit_pattern[17]);
    shiftOut(SHIFT_DATA_PIN, SHIFT_CLOCK_PIN, LSBFIRST, digit_pattern[17]);
    digitalWrite(SHIFT_LATCH_PIN, HIGH);
}