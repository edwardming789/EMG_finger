int analogPin= 1;
int raw= 0;
int Vin= 5;
float Vout= 0;
int F = 0;
float R1= 100000;
float R2= 0;
float buffer= 0;

void setup()
{
Serial.begin(9600);
}

void loop()
{
raw= analogRead(analogPin);
  if(raw) 
  {
  buffer= raw * Vin;
  Vout= (buffer)/1024.0;
  buffer= (Vin/Vout) -1;
  R2= R1 * buffer/1000.0;
    if (R2>10000){
      R2 = 10000;
      //F = map(R2,120,80,100,400);
    }
  Serial.println(R2);
  }
}
