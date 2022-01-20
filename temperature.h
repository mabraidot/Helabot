#include <OneWire.h>

OneWire ds(10);

float offset = 3.0;
float temperature = 0.0;
float temperatureSetPoint = 0.0;


void temperature_init()
{
  temperatureSetPoint = eeprom_read();
}

float temperature_get(void)
{
  return temperature;
}

float temperature_get_set_point(void)
{
  return temperatureSetPoint;
}

void temperature_set_set_point(float setPoint)
{
  temperatureSetPoint = setPoint;
  eeprom_write(setPoint);
}

void temperature_handle()
{
  static int reading = 0;
  static long readingTimeout = 0;

  if (!reading)
  {
    reading = 1;
    readingTimeout = millis();
    ds.reset();
    ds.write(0xCC);
    ds.write(0x44);
  }

  if (abs((long)millis() - readingTimeout) >= 750 && reading)
  {
    readingTimeout = millis();
    reading = 0;
  
    byte data[2];
    ds.reset();
    ds.write(0xCC);
    ds.write(0xBE);

    data[0] = ds.read();
    data[1] = ds.read();
    temperature = data[1] * 16.0 + data[0] / 16.0;
  }
}