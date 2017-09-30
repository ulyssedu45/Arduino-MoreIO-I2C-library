#ifndef FDB_MOREIO_I2C_H
#define FDB_MOREIO_I2C_H

#include <Arduino.h>

class Moreio_I2C {
public:

  Moreio_I2C(uint8_t lcd_addr);

  void begin();

  void digitalWrite(int pin, bool value);

  void analogWrite(int pin, int value);

  void pinMode(int pin, int value);

  int analogRead(int pin);

  int digitalRead(int pin);
  
private:
  uint8_t _addr;
};

#endif // FDB_MOREIO_I2C_H
