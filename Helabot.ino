#include <Arduino.h>
#include "EEPROM.h"
#include "display.h"
#include "buttons.h"
#include "relays.h"
#include "temperature.h"

// Needed for software reset
void (*resetFunc)(void) = 0;

void setup()
{
  display_init();
  display_number(00.0);
  buttons_init();
  relays_init();
  temperature_init();
}

void loop()
{
  buttons_handle();
  temperature_handle();


  /// TESTING
  if (buttons_pressed("a") && buttons_pressed("b"))
  {
    resetFunc();
    delay(500);
  }
  else if (buttons_pressed("a"))
  {
    temperature_set_set_point(temperature_get());
  }
  else if (buttons_pressed("c"))
  {
    relays_enable(1);
    relays_enable(2);
  }
  else if (buttons_pressed("b"))
  {
    display_number(temperature_get_set_point());
  }
  else if (buttons_pressed("d"))
  {
    // temperature_set_set_point(temperature_get());
  }
  else
  {
    relays_disable(1);
    relays_disable(2);
    display_number(temperature_get());
  }
}
