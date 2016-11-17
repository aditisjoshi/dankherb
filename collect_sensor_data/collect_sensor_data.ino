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

int soilSensorVal3;
int soilSensorPin3 = A4;

int lightSensorVal3;
int lightSensorPin3 = A5;

// NEED TO FIX THESE PINS 
int soilSensorVal4;
int soilSensorPin4 = A2;

int lightSensorVal4;
int lightSensorPin4 = A3;

int pumpPin = 8;

//int numstart;
//int numend;

int num1 = N_LEDS / 4;
int num2 = (2 * N_LEDS) / 4;
int num3 = (3 * N_LEDS) / 4;
int num4 = (4 * N_LEDS) / 4;



void setup() {
  pinMode(pumpPin, OUTPUT);      // sets the digital pin as output
  strip.begin();
  // put your setup code here, to run once:
  Serial.begin(9600); 
}

void loop() {
  // put your main code here, to run repeatedly:
  // this code reads the different light and soil sensor values for all of the plants 
  soilSensorVal1 = analogRead(soilSensorPin1);
  lightSensorVal1 = analogRead(lightSensorPin1);

  soilSensorVal2 = analogRead(soilSensorPin2);
  lightSensorVal2 = analogRead(lightSensorPin2);

  soilSensorVal3 = analogRead(soilSensorPin3);
  lightSensorVal3 = analogRead(lightSensorPin3);

  soilSensorVal4 = analogRead(soilSensorPin4);
  lightSensorVal4 = analogRead(lightSensorPin4);

  
  // this is the control code for the lights
  if (lightSensorVal1 < 950) {
    chase(strip.Color(255, 255, 255), 0, num1); // Red
  } else {
    chase(strip.Color(0, 0, 0),0, num1);
  }

  if (lightSensorVal2 < 950) {
    chase(strip.Color(255, 255, 255), num1, num2); // Red
  } else {
    chase(strip.Color(0, 0, 0), num1, num2);
  }

  if (lightSensorVal3 < 950) {
    chase(strip.Color(255, 255, 255), num2, num3); // Red
  } else {
    chase(strip.Color(0, 0, 0), num2, num3);
  }

  if (lightSensorVal4 < 950) {
    chase(strip.Color(255, 255, 255), num4, N_LEDS); // Red
  } else {
    chase(strip.Color(0, 0, 0), num4, N_LEDS);
  }


  // this is the control code for the water NEEDS TO BE FIXED
  if (soilSensorVal1 < 800) {
    digitalWrite(pumpPin, HIGH);   // sets the LED on
  } else {
    digitalWrite(pumpPin, LOW);   // sets the LED on
  }


  // this is the printing of the sensor values (used by the GUI to be read from the serial monitor)
  Serial.print(lightSensorVal1);
  Serial.print("/");
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
}


static void chase(uint32_t c, int numstart, int numend) {
  for(uint16_t i=numstart; i<numend; i++) {
      strip.setPixelColor(i  , c); // Draw new pixel
      strip.show();
  }
} 
