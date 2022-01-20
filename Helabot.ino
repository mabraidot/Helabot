#include <Arduino.h>
#include "EEPROM.h"
#include "display.h"
#include "buttons.h"
#include "relays.h"
#include "temperature.h"
#include "cooler.h"

// Feature for software reset
void (*resetFunc)(void) = 0;

void setup()
{
  display_init();
  display_number(00.0);
  buttons_init();
  relays_init();
  temperature_init();
  cooler_init();
}

void loop()
{
  buttons_handle();
  temperature_handle();
  cooler_handle();
}
