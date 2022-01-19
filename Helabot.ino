#include <Arduino.h>
#include "display.h"
#include "buttons.h"
#include "relays.h"
#include "temperature.h"

// float counter = 0.0;

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
  if (temperature_error())
  {
    display_error();
  }
  else
  {
    display_number(temperature_get());
  }

  if (buttons_pressed("a") && buttons_pressed("b"))
  {
    resetFunc();
    delay(500);
  }

  if (buttons_pressed("a"))
  {
    // counter += 10.0;
    // display_number(counter);
    // delay(500);
    relays_enable(1);
  }
  else
  {
    relays_disable(1);
  }
  if (buttons_pressed("c"))
  {
    // counter -= 10.0;
    // display_number(counter);
    // delay(500);
    relays_enable(2);
  }
  else
  {
    relays_disable(2);
  }

  // if (buttons_pressed("b")) {
  //   counter += 00.1;
  //   display_number(counter);
  //   delay(500);
  // }

  // if (buttons_pressed("d")) {
  //   counter -= 00.1;
  //   display_number(counter);
  //   delay(500);
  // }
}
