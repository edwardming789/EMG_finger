int analogPin= 0;
int raw= 0;
int Vin= 5;
float Vout= 0;
float F = 0;
float R1= 1000;
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
if (R2 < 25) {
  F = 100000000.0 * (pow(R2,-5.08));
}else{
  F = 0;
}

//Serial.print("Vout: ");
//Serial.println(Vout);
//Serial.print("R2: ");
Serial.println(R2);
}
}
