# Arduino-MoreIO-I2C-library

<img src="https://i.imgur.com/n3VSYwB.png" width="430"> <img src="https://i.imgur.com/zVXCQZA.png" width="430">

#### I2C card code

```c
#include <Wire.h>
int adressebit0 = 2;
int adressebit1 = 3;
int adressebit2 = 4;
int adressebit3 = 5;

int io0 = 6;  //PWM
int io1 = 7;
int io2 = 8;
int io3 = 9;  //PWM
int io4 = 10; //PWM
int io5 = 11; //PWM
int io6 = 12;
int io7 = 13;
int io8 = 14; //Digital / Analog
int io9 = 15; //Digital / Analog
int io10 = 16; //Digital / Analog
int io11 = 17; //Digital / Analog

int Pins[] = {6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17};

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

int adresse = 112;

void setup() {
  
  pinMode(adressebit0, INPUT);
  digitalWrite(adressebit0, LOW);
  pinMode(adressebit1, INPUT);
  digitalWrite(adressebit1, LOW);
  pinMode(adressebit2, INPUT);
  digitalWrite(adressebit2, LOW);
  pinMode(adressebit3, INPUT);
  digitalWrite(adressebit3, LOW);
  
  if(digitalRead(adressebit0) == HIGH){
    adresse = adresse + 1;
  }
  if(digitalRead(adressebit1) == HIGH){
    adresse = adresse + 2;
  }
  if(digitalRead(adressebit2) == HIGH){
    adresse = adresse + 4;
  }
  if(digitalRead(adressebit3) == HIGH){
    adresse = adresse + 8;
  }
  
  Wire.begin(adresse);
  Wire.onReceive(receiveEvent);
  Wire.onRequest(requestEvent);
}

void loop() {
  Packet.data.A0 = analogRead(A0);
  Packet.data.A1 = analogRead(A1);
  Packet.data.A2 = analogRead(A2);
  Packet.data.A3 = analogRead(A3);

  Packet.data.io0 = digitalRead(io0);
  Packet.data.io1 = digitalRead(io1);
  Packet.data.io2 = digitalRead(io2);
  Packet.data.io3 = digitalRead(io3);
  Packet.data.io4 = digitalRead(io4);
  Packet.data.io5 = digitalRead(io5);
  Packet.data.io6 = digitalRead(io6);
  Packet.data.io7 = digitalRead(io7);
  Packet.data.io8 = digitalRead(io8);
  Packet.data.io9 = digitalRead(io9);
  Packet.data.io10 = digitalRead(io10);
  Packet.data.io11 = digitalRead(io11);
}

void receiveEvent(int howMany) {

  String data = "";
  while (Wire.available()) {
    char c = Wire.read();
    data = data + c;
  }
  
  if(String(data[0]).toInt() == 0){
    if(String(data[1]).toInt() == 0){
      digitalWrite(Pins[hexToDec(String(data[2]))], String(data[3]).toInt());
    }else if(String(data[1]).toInt() == 1){
      analogWrite(Pins[hexToDec(String(data[2]))], data.substring(3).toInt());
    }
  }else if(String(data[0]).toInt() == 1){
      pinMode(Pins[hexToDec(String(data[1]))], String(data[2]).toInt());
  }
}

void requestEvent() {
  Wire.write(Packet.I2CPacket, PACKET_SIZE); 
}

unsigned int hexToDec(String hexString) {
  
  unsigned int decValue = 0;
  int nextInt;
  
  for (int i = 0; i < hexString.length(); i++) {
    
    nextInt = int(hexString.charAt(i));
    if (nextInt >= 48 && nextInt <= 57) nextInt = map(nextInt, 48, 57, 0, 9);
    if (nextInt >= 65 && nextInt <= 70) nextInt = map(nextInt, 65, 70, 10, 15);
    if (nextInt >= 97 && nextInt <= 102) nextInt = map(nextInt, 97, 102, 10, 15);
    nextInt = constrain(nextInt, 0, 15);
    
    decValue = (decValue * 16) + nextInt;
  }
  
  return decValue;
}
```


#### Example

```c
#include <Moreio_I2C.h>

Moreio_I2C mio1(127);

void setup() {
  mio1.begin();
  mio1.pinMode(7, OUTPUT);
}

void loop() {
  mio1.digitalWrite(7,LOW);
  delay(1000);
  mio1.digitalWrite(7,HIGH);
  delay(1000);
}
```
