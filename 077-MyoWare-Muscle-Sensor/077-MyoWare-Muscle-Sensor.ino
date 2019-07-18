#include <Servo.h>

//Threshold for servo motor control with muscle sensor. 
//You can set a threshold according to the maximum and minimum values of the muscle sensor.
#define THRESHOLD 180
#define baseline 130
//Pin number where the sensor is connected. (Analog 0)
#define EMG_PIN 0
#define analogPin 1

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
int raw= 0;
int Vin= 5;
int F = 0;

int lthreshold;
int avg[9];

float k = 0.0;
float factor = 0.0;
float R1= 100000;
float R2= 0;
float R = 0;
float buffer= 0;
float Vout= 0;

bool stage1;
bool stage2 = false;
bool stage3 = false;
bool stage4 = false;
bool state = false;
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
        avg[counter] = average;
        counter ++;
      }
      else {
        k = ((float)(average - avg[0]))/10.0;
        counter = 0;
        //Serial.println(k);
      }

      if ((k > 10) && (average > 180) && (!state)) {
        for (int i = 0; i < 180; i++){
          SERVO_1.write(i);
          raw = analogRead(analogPin);
          R = OhmMeter(raw);
          /*if ((R > 12000) && (i > 40)){
            delay(3000);
            goto situation1;
          }*/
        }
        //situation1:
        factor = 0.47;
        state = true;
      }
      else if ((k > 0) && (!state)){
        for (int i = 0; i < 180; i++){
          SERVO_1.write(i);
          raw = analogRead(analogPin);
          R = OhmMeter(raw);
          /*if ((R > 12000) && (i >40)){
            delay(3000);
            goto situation2;
          }*/
          delay(8);
        }
        //situation2:
        factor = 0.7;
        state = true;
      }

      if (average < maximum) {
        lthreshold = maximum * factor;
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
      counter = 0;
      k = 0;
      state = false;
      stage3 = true;
      stage2 = false;
    }
  }

  if (stage3){
    if (average > lthreshold) {
      SERVO_1.write(0);
      stage3 = false;
      stage4 = true;
    }
  }

  if (stage4){
    if (average < baseline) {
        maximum = 0;
        R = 0;
        stage4 = false;
        stage1 = true;
    }
  }
  
  //Serial.println(k);
  Serial.println(average);
  delay(1);
}

float OhmMeter(int reading){
  if(reading) 
  {
  buffer= reading * Vin;
  Vout= (buffer)/1024.0;
  buffer= (Vin/Vout) -1;
  R2= R1 * buffer/1000.0;
  return R2;
  }
}
