#define EMG_PIN 0

const int filterWeight = 64;  // higher numbers = heavier filtering
const int numReadings = 6;
int average = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  average = analogRead(EMG_PIN);
}

void loop() {
  // put your main code here, to run repeatedly:
  for (int i = 0; i < numReadings; i++) {
    average = average + (analogRead(EMG_PIN) - average) / filterWeight;
    delay(3);
  }
  Serial.println(average);
}
