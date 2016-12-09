
int pumpPin = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(pumpPin, OUTPUT); 
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(pumpPin, HIGH);
}
