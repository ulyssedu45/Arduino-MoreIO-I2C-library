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
#ifndef FDB_MOREIO_I2C_H
#define FDB_MOREIO_I2C_H

#include <Arduino.h>
#include <Wire.h>

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
typedef struct RecvData_t{
  int A0;
  int A1;
  int A2;
  int A3;
  int io0;  //PWM
  int io1;
  int io2;
  int io3;  //PWM
  int io4; //PWM
  int io5; //PWM
  int io6;
  int io7;
  int io8; //Digital / Analog
  int io9; //Digital / Analog
  int io10; //Digital / Analog
  int io11; //Digital / Analog
};

typedef union I2C_Packet_t{
 RecvData_t data;
 byte I2CPacket[sizeof(RecvData_t)];
};  

#define PACKET_SIZE sizeof(RecvData_t)
I2C_Packet_t Packet;

  uint8_t _addr;
};

#endif // FDB_MOREIO_I2C_H
