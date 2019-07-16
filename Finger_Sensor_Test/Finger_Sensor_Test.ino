#include <Servo.h>

const int sensorPin = A0;
int sensorReading;

int position;

Servo myservo;

void setup(){
  Serial.begin(9600);
  //myservo.write(30);  // Closed claw.
  //myservo.attach(servoPin );
}

void loop(){
  sensorReading = analogRead(sensorPin);
    //Serial.print("Analog reading = ");
    Serial.println(sensorReading); // the raw analog reading
}
