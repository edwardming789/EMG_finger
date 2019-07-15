#include <Servo.h>

const int sensorPin = A1;
float sensorReading;

int position;

Servo myservo;

void setup(){
  Serial.begin(9600);
  //myservo.write(30);  // Closed claw.
  myservo.attach(servoPin );
}

void loop(){
  sensorReading = analogRead(sensorPin);
    Serial.print("Analog reading = ");
    Serial.print(sensorReading); // the raw analog reading
}
