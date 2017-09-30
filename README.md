# Arduino-MoreIO-I2C-library

<img src="http://i.imgur.com/ul15tVz.png" width="430"> <img src="http://i.imgur.com/jltriXt.png" width="430">

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
  delay(100);
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
   String data = "";
   int A0 = analogRead(A0);
   int A1 = analogRead(A1);
   int A2 = analogRead(A2);
   int A3 = analogRead(A3);

   if(A0 >= 1000){
    data = data + A0;
   }else if(A0 < 1000 && A0 >= 100){
    data = data + "0" + A0;
   }else if(A0 < 100 && A0 >= 10){
    data = data + "00" + A0;
   }else if(A0 < 10 && A0 >= 0){
    data = data + "000" + A0;
   }
   if(A1 >= 1000){
    data = data + A1;
   }else if(A1 < 1000 && A1 >= 100){
    data = data + "0" + A1;
   }else if(A1 < 100 && A1 >= 10){
    data = data + "00" + A1;
   }else if(A1 < 10 && A1 >= 0){
    data = data + "000" + A1;
   }
   if(A2 >= 1000){
    data = data + A2;
   }else if(A2 < 1000 && A2 >= 100){
    data = data + "0" + A2;
   }else if(A2 < 100 && A2 >= 10){
    data = data + "00" + A2;
   }else if(A2 < 10 && A2 >= 0){
    data = data + "000" + A2;
   }
   if(A3 >= 1000){
    data = data + A3;
   }else if(A3 < 1000 && A3 >= 100){
    data = data + "0" + A3;
   }else if(A3 < 100 && A3 >= 10){
    data = data + "00" + A3;
   }else if(A3 < 10 && A3 >= 0){
    data = data + "000" + A3;
   }

   data = data + digitalRead(io0) + digitalRead(io1) + digitalRead(io2) + digitalRead(io3) + digitalRead(io4) + digitalRead(io5) + digitalRead(io6) + digitalRead(io7) + digitalRead(io8) + digitalRead(io9) + digitalRead(io10) + digitalRead(io11);
   
   for (int i=0; i <= data.length() + 1; i++){
      Wire.write(data[i]);
   }
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
#include <Wire.h>
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
