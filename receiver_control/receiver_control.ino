#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 

// Creating the two motors
Adafruit_DCMotor *pump = AFMS.getMotor(4);

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

int pumpOffSpeed = 0;
int pumpOnSpeed = 100;

void setup() {
  Wire.begin(8);
  Wire.onReceive(receiveEvent);
  Serial.begin(9600);
  AFMS.begin(); 
  offPump();
}

void loop() {
  // put your main code here, to run repeatedly:
  readSoilSensorVals();
  
  if ((soilSensorVal1 + soilSensorVal2 + soilSensorVal3 + soilSensorVal4)/4 < 800) {
    runPump();
  } else {
    offPump();
  }

  printSoilVals();
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

void readSoilSensorVals() {
  soilSensorVal1 = analogRead(soilSensorPin1);
  soilSensorVal2 = analogRead(soilSensorPin2);
  soilSensorVal3 = analogRead(soilSensorPin3);
  soilSensorVal4 = analogRead(soilSensorPin4);

}

void runPump() {
  // Set the speed to start, from 0 (off) to 255 (max speed)
  pump->setSpeed(pumpOnSpeed);
  pump->run(FORWARD);
  // turn on motor
  pump->run(RELEASE);
}

void offPump() {
  // Set the speed to start, from 0 (off) to 255 (max speed)
  pump->setSpeed(pumpOffSpeed);
  pump->run(FORWARD);
  // turn on motor
  pump->run(RELEASE);
}

void printSoilVals() {
  Serial.print(lightSensorVal1);
  Serial.print("/");
  Serial.print(soilSensorVal1);
  Serial.print("/");
  Serial.print(lightSensorVal2);
  Serial.print("/");
  Serial.print(soilSensorVal2);
  Serial.print("/");
  Serial.print(lightSensorVal3);
  Serial.print("/");
  Serial.print(soilSensorVal3);
  Serial.print("/");
  Serial.print(lightSensorVal4);
  Serial.print("/");
  Serial.println(soilSensorVal4);
}


