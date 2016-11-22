 //#include <Adafruit_NeoPixel.h>

// Simple NeoPixel test.  Lights just a few pixels at a time so a
// 1m strip can safely be powered from Arduino 5V pin.  Arduino
// may nonetheless hiccup when LEDs are first connected and not
// accept code.  So upload code first, unplug USB, connect pixels
// to GND FIRST, then +5V and digital pin 6, then re-plug USB.
// A working strip will show a few pixels moving down the line,
// cycling between red, green and blue.  If you get no response,
// might be connected to wrong end of strip (the end wires, if
// any, are no indication -- look instead for the data direction
// arrows printed on the strip).

#include <Adafruit_NeoPixel.h>

#define PIN     10
#define N_LEDS  8

Adafruit_NeoPixel strip = Adafruit_NeoPixel(N_LEDS, PIN, NEO_GRB + NEO_KHZ800);

//sensor val to lux calibration values
float a = 3.60357776682*pow(10,-8);
float b = -5.35983142788*pow(10,-5);
float c = 0.0248690097221;
float d = -3.58641388043;
float e = 106.046836289;

//conversion constants for lux -> ppfd -> dli
int ppfdConversionConstant = 0.029; //Sunlight 0.0185, Fluorescent (Grolux) 0.029
int dliConversionConstant = 0.0864; //The 0.0864 factor is the total number of seconds in a day divided by 1,000,000 (to convert umol to mol)

//adding up lux to get daily light integral (DLI)
float dailyLuxVals[24];
int hour = 1;
int tStartHour;
int tCurrent;
int oneHour = 3.6 * pow(10, 6); //one hour in milliseconds
int currentLuxVal;
float currentDLI;

int lightSensorVal;
int luxVal;
int lightSensorPin = A1;

void setup() {
  strip.begin();
  Serial.begin(9600);
}

void loop() {
  lightSensorVal = getSensorVal();
  Serial.print(lightSensorVal);

  if (updateTime()) { //returns true if an hour has passed, false if not
    updateDailyLightValues();
  }

  currentDLI = getDLI();
  if (12 < currentDLI && currentDLI < 16) {
    //update the lights somehow!
  }
  
  if (lightSensorVal < 950) {
    chase(strip.Color(255, 255, 255)); // Red
  } else {
    chase(strip.Color(0, 0, 0));
  }
}

//CONTROL THE LIGHTS FUNCTIONS

static void chase(uint32_t c) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
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

void updateDailyLightValues() {
  currentLuxVal = sensorToLux(getSensorVal());
  addLuxtoAverage(currentLuxVal, hour);
}

float addLuxtoAverage(float luxVal, int hour) {
  dailyLuxVals[hour] = luxVal;
}

//GET KEY VALUES FUNCTIONS

int getSensorVal() {
  analogRead(lightSensorPin);
}

float getDLI() {
  return ppfdToDLI(avgLuxToPPFD(getLuxAverage())); //is this a cool thing to do with arduino? #notpython
}

int i;
float sum;

float getLuxAverage() {
  sum = 0;
  for (i = 0; i < 24; i = i + 1) {
    sum += dailyLuxVals[i];
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



