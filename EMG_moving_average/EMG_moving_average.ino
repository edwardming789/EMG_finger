const int numReadings = 20;
const int numTrail = 1000;

int readings[numReadings];      // the readings from the analog input
int readIndex = 0;              // the index of the current reading
int total = 0;                  // the running total
int average = 0;                // the average
int minimum = 40;
int maximum = 40;
int value;
int counter = 0;
int tempvalue[49];
int inputPin = A0;

void setup() {
  // initialize serial communication with computer:
  Serial.begin(9600);
  // initialize all the readings to 0:
  for (int thisReading = 0; thisReading < numReadings; thisReading++) {
    readings[thisReading] = 0;
  }
  for (int thisReading = 0; thisReading < numTrail; thisReading++) {
    value = analogRead(inputPin);
    maximum = max(value, maximum);
    minimum = min(value, minimum);
    delay(1);
  }
}

void loop() {
  // subtract the last reading:
  total = total - readings[readIndex];
  // read from the sensor:
  readings[readIndex] = analogRead(inputPin);
  // add the reading to the total:
  total = total + readings[readIndex];
  // advance to the next position in the array:
  readIndex = readIndex + 1;
  // if we're at the end of the array...
  if (readIndex >= numReadings) {
    // ...wrap around to the beginning:
    readIndex = 0;
  }

  // calculate the average:
  average = total / numReadings;
  // send it to the computer as ASCII digits
  Serial.println(average);

  if (counter < 50){
    tempvalue[counter]=average
    counter ++;
  }
  else{
  
  }

  
  delay(1);        // delay in between reads for stability
}
