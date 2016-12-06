#include <Wire.h>
#include <Adafruit_NeoPixel.h>

#define PIN     10
#define N_LEDS  10

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

int numLights[5];
numLights[0] = 0
numLights[1] = N_LEDS / 4;
numLights[2] = (2 * N_LEDS) / 4;
numLights[3] = (3 * N_LEDS) / 4;
numLights[4] = (4 * N_LEDS) / 4;

//sensor val to lux calibration values
const float a = -6.04174634356*pow(10,-14);
const float b = 1.73210693561*pow(10,-10);
const float c = -1.80136355915*pow(10, -7);
const float d = 8.6163611226*pow(10,-5);
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

float currentDLI1;
float currentDLI2;
float currentDLI3;
float currentDLI4;

const int minDLI = 12;
const int maxDLI = 16;

void setup() {
  // put your setup code here, to run once:
  Wire.begin();
  Serial.begin(9600);
  strip.begin();
//for (int j=0;j<24;j++) {
//  dailyLuxVals[0][j] = 0;
//  dailyLuxVals[1][j] = 0;
//  dailyLuxVals[2][j] = 0;
//  dailyLuxVals[3][j] = 0;
//}
}

void loop() {
  updateLights();
  controlLights();
  sendDatatoReceiver();
}

//writer functions

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

//CONTROL THE LIGHTS FUNCTIONS

void controlLights() {
  for (int lightNum=0; i<4; i++) {
    currentDLI = getDLI(lightNum);
    if (minDLI < currentDLI && currentDLI < maxDLI) {
      chase(strip.Color(255, 255, 255), numLights[lightNum], numLights[LightNum+1]); // Red
    } else {
      chase(strip.Color(0, 0, 0), numLights[lightNum], numLights[lightNum+1]);
    }
  }
}

static void chase(uint32_t c, int numstart, int numend) {
  for(uint16_t i=numstart; i<numend; i++) {
      strip.setPixelColor(i  , c); // Draw new pixel
      strip.show();
  }
} 

//UPDATE FUNCTIONS

void updateLights() {
  if (updateTime()) { //returns true if an hour has passed, false if not
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
    if (hour == 24) { hour = 0; } 
    else { hour++; }
    //update the daily light values
    return true; 
  }

  return false;
}

void updateDailyLightValues(int sensorNum, int sensorPin) {
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
  return ppfdToDLI(avgLuxToPPFD(getLuxAverage(sensorNum))); //is this a cool thing to do with arduino? #notpython
}

float sum;
float getLuxAverage(int sensorNum) {
  sum = 0;
  float numVals = 24.0;
  for (int i = 0; i < 24; i++) {
    int dailyLightVal = dailyLuxVals[sensorNum][i];
    sum += dailyLightVal;
  }
  
  return ((float)sum)/numVals;
}

//CONVERSION FUNCTIONS

float sensorToLux(int sensorVal) {
  return a*pow(sensorVal,6) + b*pow(sensorVal,5) + c*pow(sensorVal,4) + d*pow(sensorVal, 3) + e*pow(sensorVal, 2) + f*pow(sensorVal, 1) + g;
}

float avgLuxToPPFD(float luxVal) {
  return luxVal * ppfdConversionConstant; //PPFD in µmol m-2 s-1
}

float ppfdToDLI(float ppfdVal) {
  return ppfdVal * dliConversionConstant;
}


