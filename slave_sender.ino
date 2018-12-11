
#include <Wire.h>

int value = 0;
int counter = 1;
int i = 0;
int j = 0;
int gatherData = true;
short x = 0;
const int bufSize = 40000;
byte values[bufSize];
void setup()
{
 analogReadResolution(8);
 analogWriteResolution(8);
 Wire.begin(2);                // join i2c bus with address #2
 Wire.onRequest(requestEvent); // register event
 Serial.begin(115200);  // start serial for output                   // enable ADC on pin A0
}

void loop()
{
    //values[i++] = short(analogRead(A0));
  //analogWrite(DAC0, analogRead(A0));

  //num = 0;
  //collect values into a buffer.
  //find out max values it can hold then reset them?
  //then on request event send those values
  
}

void requestEvent()
{
  //x = values[j++];
  byte y = 100; 
  //analogWrite(DAC0, y);
  byte x = analogRead(A0);
  //Wire.write(x); 
  Wire.write(y); 
  //analogWrite(DAC0, x);
}
