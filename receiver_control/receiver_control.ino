#include <Wire.h>

bool is_int = false; //stands for int

char c;
int i;

int soilSensorVal1;
int soilSensorPin1 = A0;

int soilSensorVal2;
int soilSensorPin2 = A1;

int soilSensorVal3;
int soilSensorPin3 = A2;

int soilSensorVal4;
int soilSensorPin4 = A3;

int lightSensorVal1;
int lightSensorVal2;
int lightSensorVal3;
int lightSensorVal4;

int pumpPin = 8;

void setup() {
  // put your setup code here, to run once:
  Wire.begin(8);
  Wire.onReceive(receiveEvent);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  soilSensorVal1 = analogRead(soilSensorPin1);
  soilSensorVal2 = analogRead(soilSensorPin1);
  soilSensorVal3 = analogRead(soilSensorPin1);
  soilSensorVal4 = analogRead(soilSensorPin1);

  if ((soilSensorVal1 + soilSensorVal2 + soilSensorVal3 + soilSensorVal4)/4 < 800) {
    digitalWrite(pumpPin, HIGH);   // sets the LED on
  } else {
    digitalWrite(pumpPin, LOW);   // sets the LED on
  }

  
  Serial.println("START");
  Serial.print("LIGHT");
  Serial.print(lightSensorVal1);
  Serial.print("SOIL");
  Serial.println(soilSensorVal1);
  Serial.print("/");
  Serial.print(lightSensorVal2);
  Serial.print("/");
  Serial.println(soilSensorVal2);
  Serial.print("/");
  Serial.print(lightSensorVal3);
  Serial.print("/");
  Serial.println(soilSensorVal3);
  Serial.print("/");
  Serial.print(lightSensorVal4);
  Serial.print("/");
  Serial.println(soilSensorVal4);
  Serial.println("END");
}

void receiveEvent(int howMany) {
  while(Wire.available()) {
    if (Wire.available()%2 == 1) { 
      i = Wire.read();
      if (c == 'a') {
        lightSensorVal1 = i;
      }
      else if (c == 'b') {
        lightSensorVal2 = i;
      }
      else if (c == 'c') {
        lightSensorVal3 = i;
      }
      else if (c == 'd') {
        lightSensorVal4 = i;
      }
    } else {
      c = Wire.read();

    }
  }
}



