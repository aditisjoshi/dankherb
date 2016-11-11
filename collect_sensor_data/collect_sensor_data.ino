#include <Adafruit_NeoPixel.h>

#define PIN     10
#define N_LEDS  20

Adafruit_NeoPixel strip = Adafruit_NeoPixel(N_LEDS, PIN, NEO_GRB + NEO_KHZ800);


int soilSensorVal1;
int soilSensorPin1 = A0;

int lightSensorVal1;
int lightSensorPin1 = A1;


int soilSensorVal2;
int soilSensorPin2 = A2;

int lightSensorVal2;
int lightSensorPin2 = A3;

int pumpPin = 8;



void setup() {
  pinMode(pumpPin, OUTPUT);      // sets the digital pin as output
  strip.begin();
  // put your setup code here, to run once:
  Serial.begin(9600); 
}

void loop() {
  // put your main code here, to run repeatedly:
  soilSensorVal1 = analogRead(soilSensorPin1);
  lightSensorVal1 = analogRead(lightSensorPin1);

  soilSensorVal2 = analogRead(soilSensorPin2);
  lightSensorVal2 = analogRead(lightSensorPin2);
  
  if (lightSensorVal1 < 950) {
    chase(strip.Color(255, 255, 255)); // Red
  } else {
    chase(strip.Color(0, 0, 0));
  }

  digitalWrite(pumpPin, HIGH);
//  if (soilSensorVal1 < 800) {
//    digitalWrite(pumpPin, HIGH);   // sets the pump on
//  } else {
//    digitalWrite(pumpPin, LOW);   // sets the pump off
//  }

  //Serial.print("light = ");
  Serial.print(lightSensorVal1);
  Serial.print("/");
  Serial.println(soilSensorVal1);
}


static void chase(uint32_t c) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i  , c); // Draw new pixel
      strip.show();
  }
} 
