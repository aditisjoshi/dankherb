int soilSensorVal;
int soilSensorPin = A0;

int lightSensorVal;
int lightSensorPin = A1;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  soilSensorVal = analogRead(soilSensorPin);
  lightSensorVal = analogRead(lightSensorPin);

  //Serial.print("light = ");
  Serial.print(lightSensorVal);
  Serial.print("/");
  Serial.println(soilSensorVal);
}
