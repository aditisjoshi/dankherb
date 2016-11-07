int soilSensorVal1;
int soilSensorPin1 = A0;

int lightSensorVal1;
int lightSensorPin1 = A1;


int soilSensorVal2;
int soilSensorPin2 = A2;

int lightSensorVal2;
int lightSensorPin2 = A3;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  soilSensorVal1 = analogRead(soilSensorPin1);
  lightSensorVal1 = analogRead(lightSensorPin1);

  soilSensorVal2 = analogRead(soilSensorPin2);
  lightSensorVal2 = analogRead(lightSensorPin2);

  //Serial.print("light = ");
  Serial.print(lightSensorVal1);
  Serial.print("/");
  Serial.println(soilSensorVal1);
  Serial.print("/");
  Serial.print(lightSensorVal2);
  Serial.print("/");
  Serial.println(soilSensorVal2);
}
