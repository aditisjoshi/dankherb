// Inclusing necessary libraries
#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 

// Creating the pump as a "motor"
Adafruit_DCMotor *pump = AFMS.getMotor(3);

// setting up the variables needed to read the light sensor values
// c tells us which light sensor it is
char c;
// i tells us what the actual value is 
int i;

// initializing the soil sensor analog pin inputs as well as their values
int soilSensorVal1;
int soilSensorPin1 = A0;
int soilSensorVal2;
int soilSensorPin2 = A1;
int soilSensorVal3;
int soilSensorPin3 = A2;
int soilSensorVal4;
int soilSensorPin4 = A3;

// the treshold below which the pump will turn on
int treshold = 990;

// the speed necessary to get the pump running
int pumpOnSpeed = 200;

// initializing the light sensor values that will be read from the writer arduino
int lightSensorVal1;
int lightSensorVal2;
int lightSensorVal3;
int lightSensorVal4;


void setup() {
  // setting up the writer reciever relationship with the other arduino
  Wire.begin(8);
  Wire.onReceive(receiveEvent);
  Serial.begin(9600);
  AFMS.begin(); 
  pump->setSpeed(pumpOnSpeed);
  pump->run(FORWARD);
  // turn on motor
  pump->run(RELEASE);
}

void loop() {
  // first, the code reads the soil sensor values from the arduino
  readSoilSensorVals();

  // if average soil level is less than the treshold, turn the water on
  if ((soilSensorVal1 + soilSensorVal2 + soilSensorVal3 + soilSensorVal4)/4 < treshold) {
    pump->run(FORWARD);
  } else {
    pump->run(RELEASE);
  }
  // printing the soil and light values to be sent to the GUI
  printVals();
}

//RECEIVER FUNCTION
void receiveEvent(int howMany) {
  while(Wire.available()) {
    // if it is the second variable sent that means it is a sensor value
    if (Wire.available()%2 == 1) { 
      i = Wire.read();
      // depending on the value read right before, the new value read will be one of the sensor values
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
      // if it is not a number, that means it is not a sensor value, so it should read the value to tell us what sensor value it is for
      c = Wire.read();

    }
  }
}

// function to read all of the soil sensor values from the different pins
void readSoilSensorVals() {
  soilSensorVal1 = analogRead(soilSensorPin1);
  soilSensorVal2 = analogRead(soilSensorPin2);
  soilSensorVal3 = analogRead(soilSensorPin3);
  soilSensorVal4 = analogRead(soilSensorPin4);
}


// Serial printing all values to be sent to the GUI
void printVals() {
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


