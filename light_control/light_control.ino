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

int lightSensorVal;
int lightSensorPin = A1;

void setup() {
  strip.begin();
  Serial.begin(9600);
}

void loop() {
  lightSensorVal = analogRead(lightSensorPin);
  Serial.print(lightSensorVal);
  
  if (lightSensorVal < 950) {
    chase(strip.Color(255, 255, 255)); // Red
  } else {
    chase(strip.Color(0, 0, 0));
  }
}

static void chase(uint32_t c) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i  , c); // Draw new pixel
      strip.show();
  }
} 
