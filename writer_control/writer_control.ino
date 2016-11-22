#include <Wire.h>
#include <Adafruit_NeoPixel.h>

#define PIN     10
#define N_LEDS  20

Adafruit_NeoPixel strip = Adafruit_NeoPixel(N_LEDS, PIN, NEO_GRB + NEO_KHZ800);

//lights control 
int lightSensorVal1;
int lightSensorPin1 = A0;

int lightSensorVal2;
int lightSensorPin2 = A1;

int lightSensorVal3;
int lightSensorPin3 = A2;
//
int lightSensorVal4;
int lightSensorPin4 = A3;

int num1 = N_LEDS / 4;
int num2 = (2 * N_LEDS) / 4;
int num3 = (3 * N_LEDS) / 4;
int num4 = (4 * N_LEDS) / 4;

//sensor val to lux calibration values
const float a = 3.60357776682*pow(10,-8);
const float b = -5.35983142788*pow(10,-5);
const float c = 0.0248690097221;
const float d = -3.58641388043;
const float e = 106.046836289;

//conversion constants for lux -> ppfd -> dli
const int ppfdConversionConstant = 0.029; //Sunlight 0.0185, Fluorescent (Grolux) 0.029
const int dliConversionConstant = 0.0864; //The 0.0864 factor is the total number of seconds in a day divided by 1,000,000 (to convert umol to mol)

//adding up lux to get daily light integral (DLI)
float dailyLuxVals[4][24];
int hour = 1;
int tStartHour;
int tCurrent;
const int oneHour = 3.6 * pow(10, 6); //one hour in milliseconds
int currentLuxVal;
float currentDLI1;
float currentDLI2;
float currentDLI3;
float currentDLI4;

const int minDLI = 12;
const int maxDLI = 16;

void setup() {
  // put your setup code here, to run once:
  Wire.begin();
  strip.begin();
}

void loop() {
  readLights();
//  controlLights();
  sendDatatoReceiver();
}

void sendDatatoReceiver() {
  Wire.beginTransmission(8);
  Wire.write("a");
  Wire.write(lightSensorVal1);
  Wire.write("b");
  Wire.write(lightSensorVal1);
  Wire.write("c");
  Wire.write(lightSensorVal1);
  Wire.write("d");
  Wire.write(lightSensorVal1);
  Wire.endTransmission();

  delay(100);
}

void readLights() {
  lightSensorVal1 = analogRead(lightSensorPin1);
//  lightSensorVal2 = analogRead(lightSensorPin2);
//  lightSensorVal3 = analogRead(lightSensorPin3);
//  lightSensorVal4 = analogRead(lightSensorPin4);
}

void controlLights() {

  if (updateTime()) { //returns true if an hour has passed, false if not
    updateDailyLightValues(lightSensorPin1);
    updateDailyLightValues(lightSensorPin2);
    updateDailyLightValues(lightSensorPin3);
    updateDailyLightValues(lightSensorPin4);
  }

  currentDLI1 = getDLI(lightSensorPin1);
  currentDLI2 = getDLI(lightSensorPin2);
  currentDLI3 = getDLI(lightSensorPin3);
  currentDLI4 = getDLI(lightSensorPin4);
  
  if (minDLI < currentDLI1 && currentDLI1 < maxDLI) {
    //update the lights somehow!
  }
  
  if (lightSensorVal1 < 950) {
    chase(strip.Color(255, 255, 255), 0, num1); // Red
  } else {
    chase(strip.Color(0, 0, 0),0, num1);
  }

//  if (lightSensorVal2 < 950) {
//    chase(strip.Color(255, 255, 255), num1, num2); // Red
//  } else {
//    chase(strip.Color(0, 0, 0), num1, num2);
//  }

//  if (lightSensorVal3 < 950) {
//    chase(strip.Color(255, 255, 255), num2, num3); // Red
//  } else {
//    chase(strip.Color(0, 0, 0), num2, num3);
//  }
//
//  if (lightSensorVal4 < 950) {
//    chase(strip.Color(255, 255, 255), num4, N_LEDS); // Red
//  } else {
//    chase(strip.Color(0, 0, 0), num4, N_LEDS);
//  }
}

//CONTROL THE LIGHTS FUNCTIONS

static void chase(uint32_t c, int numstart, int numend) {
  for(uint16_t i=numstart; i<numend; i++) {
      strip.setPixelColor(i  , c); // Draw new pixel
      strip.show();
  }
} 

//UPDATE FUNCTIONS
boolean updateTime() {
  //returns true if an hour has passed, false if not
  
  tCurrent = millis();
 
  //if an hour has passed
  if ((tCurrent - tStartHour) >= oneHour) { 
    //update the start of the hour
    tStartHour = tCurrent;
    // update the hour number we are on
    if (hour == 24) { hour = 0; } 
    else { hour++; }
    //update the daily light values
    return true; 
  }

  return false;
}

void updateDailyLightValues(int pin) {
  currentLuxVal = sensorToLux(getSensorVal(pin));
  addLuxtoAverage(pin,currentLuxVal, hour);
}

float addLuxtoAverage(int pin, float luxVal, int hour) {
  dailyLuxVals[pin][hour] = luxVal;
}

//GET KEY VALUES FUNCTIONS

int getSensorVal(int pin) {
  analogRead(pin);
}

float getDLI(int pin) {
  return ppfdToDLI(avgLuxToPPFD(getLuxAverage(pin))); //is this a cool thing to do with arduino? #notpython
}

int i;
float sum;

float getLuxAverage(int pin) {
  sum = 0;
  for (i = 0; i < 24; i = i + 1) {
    sum += dailyLuxVals[pin][i];
  }
  return sum/24;
}

//CONVERSION FUNCTIONS

float sensorToLux(int sensorVal) {
  return a*pow(sensorVal,4) + b*pow(sensorVal,3) + c*pow(sensorVal,2) + d*sensorVal + e;
}

float avgLuxToPPFD(float luxVal) {
  return luxVal * ppfdConversionConstant; //PPFD in µmol m-2 s-1
}

float ppfdToDLI(float ppfdVal) {
  return ppfdVal * dliConversionConstant;
}

