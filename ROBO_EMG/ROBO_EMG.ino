// using a power of 2 for the filterWeight will allow the compiler to optimise the calculation
#define inputPin 0
const int filterWeight = 32;  // higher numbers = heavier filtering
const int numReadings = 10;

int average = 0;                // the average

void setup() {
  // initialize serial communication with computer:
  Serial.begin(9600);
  // seed the filter
  average = analogRead(inputPin);
}
void loop() {
  for (int i = 0; i < numReadings; i++) {
    average = average + (analogRead(inputPin) - average) / filterWeight;
  }
  Serial.println(average);
  delay(1);
}
