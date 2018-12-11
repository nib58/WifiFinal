
#include <Wire.h>
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <string>     // std::string, std::to_string
#include <stdio.h>
#include <stdlib.h>
using namespace std;

const char* ssid     = "OnePiece";
const char* password  = "Gear4Luffy";
const char* host = "localhost";
const int port = 3000;
WiFiClient client;
byte counter = 0;
int value = 0;
int values[10];
int valuecounter;
std::string str = "";
String output = "";
String comma = ",";
int sendValue = 0;
char collect [5];
void setup()
{
  Serial.begin(115200);  // start serial for output
  WiFi.begin(ssid, password);
  WiFi.mode(WIFI_STA);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Wire.setClock(400000L);
  Serial.print("WiFi connected");
  Wire.begin(D1,D2);   //sda D1, scl D2     // join i2c bus (address optional for master)
  if (!client.connect(host, port)) {
   Serial.println("connection failed");
    return;
  }
}
void loop()
{ //4k not including client.connect
    long start = millis();//constant time
  for (int i = 0; i < 10000; i++) {
        Wire.requestFrom(2, 2);    // request 4 bytes from slave device #2
       while(Wire.available()){    // slave may send less than requested
          byte b = Wire.read(); // receive byte
          value += (int)b<<(8*counter++);//need to accumulate into int        
        }
        
        itoa(value,collect,10);
        output+=(collect + comma);
        sendValue++;
        if(sendValue == 2100){//send when buffer is 2100 (optimum size)
          Serial.println(output);
          sendValue = 0;   
        }      

        counter = 0;//reset values
        value = 0;//reset values
  }     
  long tot = float(10000 * 1000) / float(millis() - start);
  Serial.println(tot);
}
