#include <Wire.h>
#include <Adafruit_NeoPixel.h>

#define PIN     10
#define N_LEDS  20

Adafruit_NeoPixel strip = Adafruit_NeoPixel(N_LEDS, PIN, NEO_GRB + NEO_KHZ800);

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

static void chase(uint32_t c, int numstart, int numend) {
  for(uint16_t i=numstart; i<numend; i++) {
      strip.setPixelColor(i  , c); // Draw new pixel
      strip.show();
  }
} 

