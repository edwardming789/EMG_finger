#include <Servo.h>

//Threshold for servo motor control with muscle sensor. 
//You can set a threshold according to the maximum and minimum values of the muscle sensor.
#define THRESHOLD 200
#define baseline 100
//Pin number where the sensor is connected. (Analog 0)
#define EMG_PIN 0

//Pin number where the servo motor is connected. (Digital PWM 3)
#define SERVO_PIN 3

//Define Servo motor
Servo SERVO_1;

const int numReadings = 20;
const int numTrail = 1000;

int readings[numReadings];      // the readings from the analog input
int readIndex = 0;              // the index of the current reading
int total = 0;                  // the running total
int average = 0;
int maximum = 0;
int temp = 0;
int counter = 0;

int lthreshold;
int avg1;
float k;

bool stage1;
bool stage2 = false;
bool stage3 = false;
/*-------------------------------- void setup ------------------------------------------------*/

void setup(){
  
  //BAUDRATE set to 9600, remember it to set monitor serial properly. 
  Serial.begin(9600);
  for (int thisReading = 0; thisReading < numReadings; thisReading++) {
    readings[thisReading] = 0;
  }
  //Set servo motor to digital pin 3
  SERVO_1.attach(SERVO_PIN);
  stage1 = true;
}

/*--------------------------------  void loop  ------------------------------------------------*/

void loop(){
  total = total - readings[readIndex];
  // read from the sensor:
  readings[readIndex] = analogRead(EMG_PIN);
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

  maximum = max(maximum,average);
  
  //If the sensor value is GREATER than the THRESHOLD, the servo motor will turn to 180 degrees.
  if (stage1){
    if(average > THRESHOLD){
      if (counter < 10) {
        if (counter = 0){
          avg1 = average;
        }
        counter++;
      }
      else{
        k = (avg1 - average)/10;
        counter = 0;
        Serial.println(k);
      }
      
      if (average < maximum) {
        SERVO_1.write(179);
        lthreshold = maximum * 0.65;
        stage1 = false;
        stage2 = true;
        }
    }
    else{
      SERVO_1.write(0);
    }
  }

  if (stage2){
    if (average < lthreshold) {
      stage3 = true;
      stage2 = false;
    }
  }

  if (stage3){
    if (average > lthreshold) {
      SERVO_1.write(0);
    }
    if (average < baseline) {
        maximum = 0;
        stage3 = false;
        stage1 = true;
    }
  }
  
  //Serial.println(average);
  delay(1);
}
