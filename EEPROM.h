#include <EEPROM.h>

void eeprom_clear(void)
{
  for (int i = 0; i < EEPROM.length(); i++)
  {
    EEPROM.write(i, 0);
  }
}

/*
Rotate function to wear out the eeprom records evenly
*/
void eeprom_write(float value)
{
  static long readingTimeout = 0;
  
  byte tens = abs(floor(value / 10));
  byte ones = abs(floor(value) - (tens * 10));
  byte tenths = abs(round((value - floor(value)) * 10));
  /*
  values    |0|1|x|?|?|?|?|
  cells     |0|1|2|3|4|5|6|
  */
  int addr = 0;
  for (int i = 0; i < EEPROM.length(); i++)
  {
    if (EEPROM.read(i) > 0)
    {
      addr = i;
      break;
    }
  }
  if (addr + 4 >= EEPROM.length())
  { // End of EEPROM, move to the begining
    EEPROM.write(0x00, 1);
    EEPROM.write(0x01, tens);
    EEPROM.write(0x02, ones);
    EEPROM.write(0x03, tenths);
  }
  else
  { // Not end of EEPROM, so move to the next  set of addresses
    EEPROM.write(addr, 0);
    EEPROM.write(addr + 1, 1);
    EEPROM.write(addr + 2, tens);
    EEPROM.write(addr + 3, ones);
    EEPROM.write(addr + 4, tenths);
  }
}

float eeprom_read()
{
  /*
  values    |0|0|1|x|?|?|?|
  cells     |0|1|2|3|4|5|6|
  */
  int addr = 0;
  for (int i = 0; i < EEPROM.length(); i++)
  {
    if (EEPROM.read(i) > 0)
    {
      addr = i;
      break;
    }
  }

  float number = 0.0;
  number += EEPROM.read(addr + 1) * 10;
  number += EEPROM.read(addr + 2);
  number += EEPROM.read(addr + 3) / 10;

  return number;
}