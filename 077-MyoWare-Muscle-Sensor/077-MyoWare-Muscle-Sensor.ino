#include <Servo.h>

//Threshold for servo motor control with muscle sensor. 
//You can set a threshold according to the maximum and minimum values of the muscle sensor.
#define THRESHOLD 500

//Pin number where the sensor is connected. (Analog 0)
#define EMG_PIN 0

//Pin number where the servo motor is connected. (Digital PWM 3)
#define SERVO_PIN 3

//Define Servo motor
Servo SERVO_1;
const int filterWeight = 64;  // higher numbers = heavier filtering
const int numReadings = 6;

int average = 60;                // the average
int mappingv;
/*-------------------------------- void setup ------------------------------------------------*/

void setup(){
  
  //BAUDRATE set to 9600, remember it to set monitor serial properly. 
  Serial.begin(9600);
  
  //Set servo motor to digital pin 3
  SERVO_1.attach(SERVO_PIN);
  average = analogRead(EMG_PIN);
}

/*--------------------------------  void loop  ------------------------------------------------*/

void loop(){
  //The "Value" variable reads the value from the analog pin to which the sensor is connected.
  for (int i = 0; i < numReadings; i++) {
    average = average + (analogRead(EMG_PIN) - average) / filterWeight;
    delay(3);
  }

  //If the sensor value is GREATER than the THRESHOLD, the servo motor will turn to 180 degrees.
  if(average > THRESHOLD){
    SERVO_1.write(179);
  }
  //If the sensor is LESS than the THRESHOLD, the servo motor will turn to 0 degrees.
  else if(average >= 150){
    mappingv = map(average,150,THRESHOLD,0,179);
    SERVO_1.write(mappingv);
  }
  else{
    SERVO_1.write(0);
  }

  //You can use serial monitor to set THRESHOLD properly, comparing the values shown when you open and close your hand.
  Serial.println(average);
  delay(1);
}
