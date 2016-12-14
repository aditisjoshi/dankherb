// adding in the necessary libraries
#include <Wire.h>
#include <Adafruit_NeoPixel.h>

// chosing the pins that the lights are attached too
#define PIN     8
#define N_LEDS  20


//set up for Neopixels
Adafruit_NeoPixel strip = Adafruit_NeoPixel(N_LEDS, PIN, NEO_GRB + NEO_KHZ800);

int lightSensorVal1;
int lightSensorPin1 = A3;
int lightSensorVal2;
int lightSensorPin2 = A2;
int lightSensorVal3;
int lightSensorPin3 = A1;
int lightSensorVal4;
int lightSensorPin4 = A0;

// these are the indices of the individually addressable LEDs that should be turned on for each light
int numLights[] = {0 , N_LEDS / 4, (2 * N_LEDS) / 4, (3 * N_LEDS) / 4,  (4 * N_LEDS) / 4};


//sensor val to lux calibration values
const float a = -6.04174634356 * pow(10, -14);
const float b = 1.73210693561 * pow(10, -10);
const float c = -1.80136355915 * pow(10, -7);
const float d = 8.6163611226 * pow(10, -5);
const float e = -0.0191817214905;
const float f = 1.80117265067;
const float g = -42.2194133246;

//conversion constants for lux -> ppfd -> dli
const float ppfdConversionConstant = 0.029; //Sunlight 0.0185, Fluorescent (Grolux) 0.029
const float dliConversionConstant = 0.0864; //The 0.0864 factor is the total number of seconds in a day divided by 1,000,000 (to convert umol to mol)

//adding up lux to get daily light integral (DLI)
float dailyLuxVals[4][24];

int hour = 0;
int tStartHour;
int tCurrent;
const int oneHour = 3.6 * pow(10, 6); //one hour in milliseconds
int currentLuxVal;

float currentDLI;
float currentDLI[4];

const float minDLI = 0.5;
const float maxDLI = 0.9;

void setup() {
  // put your setup code here, to run once:
  Wire.begin();
  Serial.begin(9600);
  strip.begin();
}

void loop() {
  updateLights();
  controlLights();
  sendDatatoReceiver();
}


//setup functions

//writer functions

void sendDatatoReceiver() {
  //sends the DLI data to the receiver, from which it is printed to the serial, where the python GUI can grab it
  Wire.beginTransmission(8);
  Wire.write("a");
  Wire.write((int)currentDLI[0]);
  Wire.write("b");
  Wire.write((int)currentDLI[1]);
  Wire.write("c");
  Wire.write((int)currentDLI[2]);
  Wire.write("d");
  Wire.write((int)currentDLI[3]);
  Wire.endTransmission();

  delay(100);
}

//CONTROL THE LIGHTS FUNCTIONS

void controlLights() {
  //for each light, get the current DLI, and if it is not bright enough, turn the lights on

  for (int lightNum = 0; lightNum < 4; lightNum++) {
    currentDLI = getDLI(lightNum);
    currentDLI[lightNum] = currentDLI; //save this so that we can send it to the python GUI
    Serial.println(currentDLI);
    if (minDLI < currentDLI && currentDLI < maxDLI) {
      Serial.println("YAY");
      chase(strip.Color(0, 0, 0), numLights[lightNum], numLights[lightNum + 1]);
    } else {
      chase(strip.Color(255, 255, 255), numLights[lightNum], numLights[lightNum+1]); // Red
    }
  }
}

static void chase(uint32_t c, int numstart, int numend) {
  for (uint16_t i = numstart; i < numend; i++) {
    strip.setPixelColor(i  , c); // Draw new pixel
    strip.show();
  }
}

//UPDATE FUNCTIONS

void updateLights() {
  //updateTime() returns true if an hour has passed, false if not
  //this saves the sensor light values every hour so that the average can be calculated

  if (updateTime()) {
    updateDailyLightValues(0, lightSensorPin1);
    updateDailyLightValues(1, lightSensorPin2);
    updateDailyLightValues(2, lightSensorPin3);
    updateDailyLightValues(3, lightSensorPin4);
  }
}

boolean updateTime() {
  //returns true if an hour has passed, false if not

  tCurrent = millis();
  //if an hour has passed
  if ((tCurrent - tStartHour) >= 500) {
    //update the start of the hour
    tStartHour = tCurrent;
    // update the hour number we are on
    if (hour == 24) {
      hour = 0;
    }
    else {
      hour++;
    }
    //update the daily light values
    return true;
  }

  return false;
}

void updateDailyLightValues(int sensorNum, int sensorPin) {
  //gets the current light value in Lux from the value given by the sensor and adds it to the average of the day's values
  currentLuxVal = sensorToLux(getSensorVal(sensorPin));
  addLuxtoAverage(sensorNum, currentLuxVal);
}

float addLuxtoAverage(int sensorNum, float luxVal) {
  dailyLuxVals[sensorNum][hour] = luxVal;
}

//GET KEY VALUES FUNCTIONS

int getSensorVal(int pin) {
  int sensorVal = analogRead(pin);
  return sensorVal;
}

float getDLI(int sensorNum) {
  //for a certain sensor (i.e. a certain plant), get the average lux from the last 12 hours and convert that to PPFD and then DLI
  //(see our website resources for more info on PPFD and DLI)
  return ppfdToDLI(avgLuxToPPFD(getLuxAverage(sensorNum))); //is this a cool thing to do with arduino? #notpython
}

float sum;
float getLuxAverage(int sensorNum) {
  //takes average of all saved lux values from the last 12 hours
  sum = 0;
  float numVals = 24.0;
  for (int i = 0; i < 24; i++) {
    int dailyLightVal = dailyLuxVals[sensorNum][i];
    sum += dailyLightVal;
  }

  return ((float)sum) / numVals;
}

//CONVERSION FUNCTIONS

float sensorToLux(int sensorVal) {
  //this polynomial comes from our own calibration of the sensor
  return a * pow(sensorVal, 6) + b * pow(sensorVal, 5) + c * pow(sensorVal, 4) + d * pow(sensorVal, 3) + e * pow(sensorVal, 2) + f * pow(sensorVal, 1) + g;
}

float avgLuxToPPFD(float luxVal) {
  return luxVal * ppfdConversionConstant; //PPFD in µmol m-2 s-1
}

float ppfdToDLI(float ppfdVal) {
  return ppfdVal * dliConversionConstant;
}



