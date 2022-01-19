#include <OneWire.h>
#include <DallasTemperature.h>

#define ONE_WIRE_BUS 10
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

float temperature = 0.0;
int error = 0;

void temperature_init(void)
{
    sensors.begin();
    if (sensors.getDS18Count() == 0)
    {
        temperature = 30.3;
    }
    else
    {
        sensors.setResolution(11);
    }
}

float temperature_get(void)
{
    return temperature;
}

int temperature_error(void)
{
    return error;
}

void temperature_handle(void)
{
    static int interval = 500;
    static long timeout = 0;
    if (abs((long)millis() - timeout) >= interval)
    {
        if (sensors.getDS18Count() != 0)
        {
            error = 0;
            sensors.requestTemperatures();
            temperature = sensors.getTempCByIndex(0);
            timeout = millis();
        }
        else
        {
            error = 1;
        }
    }
}