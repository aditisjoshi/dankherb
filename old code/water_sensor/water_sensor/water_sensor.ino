int sensorPin = A5;
int ledPin = 11;
int val = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  val = analogRead(sensorPin);
  Serial.println(val);
  if (val < 500) {
    digitalWrite(ledPin, HIGH);
    delay(500);
    digitalWrite(ledPin, LOW);
    delay(500);
  }
  else {
     digitalWrite(ledPin, LOW);
     delay(500);
  }
}
