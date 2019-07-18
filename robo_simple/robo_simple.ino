#include <Servo.h>

Servo servoindex;          // Define index servo
int analogPin= 0;
int raw= 0;
int Vin= 5;
float Vout= 0;
int F = 0;
float R1= 100000;
float R2= 0;
float buffer= 0;
int A = 0;

void setup() { 
  Serial.begin(9600);
  servoindex.attach(3);
} 

void loop() {
  //alltorest();
  servoindex.write(0);
  delay(1000);// Loop through motion tests
  for (int i = 0; i<180; i++) {
    servoindex.write(i);
    raw = analogRead(analogPin);
    R2 = OhmMeter(raw);
    Serial.println(R2);
    if ((R2 > 12000) && (i >40)){
      delay(3000);
      goto situation1;
    }
  }
  situation1:
    delay(1000);
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
// Motion to set the servo into "virtual" 0 position: alltovirtual
void alltomiddle() {         
  servoindex.write(90);
}
// Motion to set the servo into "rest" position: alltorest
void alltorest() {         
  servoindex.write(0);
}

// Motion to set the servo into "max" position: alltomax
void alltomax() {
  servoindex.write(180);

 
}
