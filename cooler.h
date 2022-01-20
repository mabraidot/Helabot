int programmingMode = 0;
float programmingSetPoint = 0.0;

int buttonInterval = 300;
long buttonTimeout = 0;

void cooler_init(void)
{
}

void cooler_handle(void)
{
  // Save SETPOINT to memory
  if (buttons_pressed("a"))
  {
    if (programmingMode)
    {
      temperature_set_set_point(programmingSetPoint);
      programmingMode = 0;
    }
  }
  // Watch temperature SETPOINT / Increase SETPOINT
  else if (buttons_pressed("b"))
  {
    if (!programmingMode)
    {
      display_number(temperature_get_set_point());
    }
    else if (programmingSetPoint < 30)
    {
      if (abs((long)millis() - buttonTimeout) >= buttonInterval)
      {
        programmingSetPoint++;
        buttonTimeout = millis();
      }
    }
  }
  // Decrease SETPOINT
  else if (buttons_pressed("d"))
  {
    if (programmingMode && programmingSetPoint > 5)
    {
      if (abs((long)millis() - buttonTimeout) >= buttonInterval)
      {
        programmingSetPoint--;
        buttonTimeout = millis();
      }
    }
  }
  // Enter programming mode
  else if (buttons_pressed("c"))
  {
    if (abs((long)millis() - buttonTimeout) >= buttonInterval)
    {
      programmingMode = !programmingMode;
      if (programmingMode)
      {
        programmingSetPoint = temperature_get_set_point();
      }
      buttonTimeout = millis();
    }
  }
  // Handle normal functions of display
  else if (!programmingMode)
  {
    display_number(temperature_get());
  }
  else
  {
    display_number(programmingSetPoint, 1);
  }

  /*
  if pressed button c
    if not programmingmode and programmingTimeout == 0
      programmingTimeout = millis();
  else
    if programmingmode
      if programmingTimeout > 0 and millis - programmingTimeout > 2000
        programmingmode = 1
        programmingTimeout = 0
    else
      programmingmode = 0
  */
}