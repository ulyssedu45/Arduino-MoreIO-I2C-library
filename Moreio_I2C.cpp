#include "Moreio_I2C.h"
#include <Arduino.h>
#include <Wire.h>

Moreio_I2C::Moreio_I2C(uint8_t mio_addr)
{
  _addr = mio_addr;
}

void Moreio_I2C::begin() {
  Wire.begin();
}

void Moreio_I2C::digitalWrite(int pin, bool value){
  String data = "00";
  data = data + String(pin, HEX) + value;
  Wire.beginTransmission(_addr);
  for (int i=0; i <= data.length(); i++){
    Wire.write(data[i]);
  }
  Wire.endTransmission();
}

void Moreio_I2C::analogWrite(int pin, int value){
  if(value > 255){
    value = 255;
  }else if(value < 0){
    value = 0;
  }
  String data = "01";
  data = data + String(pin, HEX);
  if(value < 10){
    data = data + "00" + value;
  }else if(value >= 10 && value < 100){
    data = data + "0" + value;
  }else if(value >= 100){
    data = data + value;
  }
  Wire.beginTransmission(_addr);
  for (int i=0; i <= data.length(); i++){
    Wire.write(data[i]);
  }
  Wire.endTransmission();
}

void Moreio_I2C::pinMode(int pin, int value){
  if(pin > 11){
    pin = 11;
  }else if(pin < 0){#include "Moreio_I2C.h"
#include <Arduino.h>
#include <Wire.h>

Moreio_I2C::Moreio_I2C(uint8_t mio_addr)
{
  _addr = mio_addr;
}

void Moreio_I2C::begin() {
  Wire.begin();
}

void Moreio_I2C::digitalWrite(int pin, bool value){
  String data = "00";
  data = data + String(pin, HEX) + value;
  Wire.beginTransmission(_addr);
  for (int i=0; i <= data.length(); i++){
    Wire.write(data[i]);
  }
  Wire.endTransmission();
}

void Moreio_I2C::analogWrite(int pin, int value){
  if(value > 255){
    value = 255;
  }else if(value < 0){
    value = 0;
  }
  String data = "01";
  data = data + String(pin, HEX);
  if(value < 10){
    data = data + "00" + value;
  }else if(value >= 10 && value < 100){
    data = data + "0" + value;
  }else if(value >= 100){
    data = data + value;
  }
  Wire.beginTransmission(_addr);
  for (int i=0; i <= data.length(); i++){
    Wire.write(data[i]);
  }
  Wire.endTransmission();
}

void Moreio_I2C::pinMode(int pin, int value){
  if(pin > 11){
    pin = 11;
  }else if(pin < 0){
    pin = 0;
  }
  String data = "1";
  data = data + String(pin, HEX) + value;
  Wire.beginTransmission(_addr);
  for (int i=0; i <= data.length(); i++){
    Wire.write(data[i]);
  }
  Wire.endTransmission();
}

int Moreio_I2C::analogRead(int pin){

  byte byteArray[PACKET_SIZE];
  
  Wire.requestFrom(_addr, PACKET_SIZE);
  Wire.readBytes( byteArray, PACKET_SIZE);

  for (int k=0; k < PACKET_SIZE; k++)
  { 
    Packet.I2CPacket[k] = byteArray[k];
  }
  
  if(pin == 0){
    return Packet.data.A0;
  }else if(pin == 1){
    return Packet.data.A1;
  }else if(pin == 2){
    return Packet.data.A2;
  }else if(pin == 3){
    return Packet.data.A3;
  }else{
    return 0;
  }
}

int Moreio_I2C::digitalRead(int pin){
	
  byte byteArray[PACKET_SIZE];
  
  Wire.requestFrom(_addr, PACKET_SIZE);
  Wire.readBytes( byteArray, PACKET_SIZE);

  for (int k=0; k < PACKET_SIZE; k++)
  { 
    Packet.I2CPacket[k] = byteArray[k];
  }
  
  if(pin == 0){
    return Packet.data.io0;
  }else if(pin == 1){
    return Packet.data.io1;
  }else if(pin == 2){
    return Packet.data.io2;
  }else if(pin == 3){
    return Packet.data.io3;
  }else if(pin == 4){
    return Packet.data.io4;
  }else if(pin == 5){
    return Packet.data.io5;
  }else if(pin == 6){
    return Packet.data.io6;
  }else if(pin == 7){
    return Packet.data.io7;
  }else if(pin == 8){
    return Packet.data.io8;
  }else if(pin == 9){
    return Packet.data.io9;
  }else if(pin == 10){
    return Packet.data.io10;
  }else if(pin == 11){
    return Packet.data.io11;
  }else{
    return 0;
  }
}


    pin = 0;
  }
  String data = "1";
  data = data + String(pin, HEX) + value;
  Wire.beginTransmission(_addr);
  for (int i=0; i <= data.length(); i++){
    Wire.write(data[i]);
  }
  Wire.endTransmission();
}

int Moreio_I2C::analogRead(int pin){
  Wire.requestFrom(_addr, 29);

  String data = "";
  while (Wire.available()) {
    char c = Wire.read();
    data = data + c;
  }

  if(pin == 0){
    return data.substring(0,4).toInt();
  }else if(pin == 1){
    return data.substring(4,8).toInt();
  }else if(pin == 2){
    return data.substring(8,12).toInt();
  }else if(pin == 3){
    return data.substring(12,16).toInt();
  }else{
    return 0;
  }
}

int Moreio_I2C::digitalRead(int pin){
  Wire.requestFrom(_addr, 29);

  String data = "";
  while (Wire.available()) {
    char c = Wire.read();
    data = data + c;
  }
  if(pin == 0){
    return data.substring(16,17).toInt();
  }else if(pin == 1){
    return data.substring(17,18).toInt();
  }else if(pin == 2){
    return data.substring(18,19).toInt();
  }else if(pin == 3){
    return data.substring(19,20).toInt();
  }else if(pin == 4){
    return data.substring(20,21).toInt();
  }else if(pin == 5){
    return data.substring(21,22).toInt();
  }else if(pin == 6){
    return data.substring(22,23).toInt();
  }else if(pin == 7){
    return data.substring(23,24).toInt();
  }else if(pin == 8){
    return data.substring(24,25).toInt();
  }else if(pin == 9){
    return data.substring(25,26).toInt();
  }else if(pin == 10){
    return data.substring(26,27).toInt();
  }else if(pin == 11){
    return data.substring(27,28).toInt();
  }else{
    return 0;
  }
}

