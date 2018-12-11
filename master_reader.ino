
#include <Wire.h>
#include <Arduino.h>
#include <ESP8266WiFi.h>

const char* ssid     = "iPhone";
//const char* ssid     = "OnePiece";

const char* password  = "warriors#30";
//const char* password  = "Gear4Luffy";

const char* host = "172.20.10.3";
//const char* host = "10.0.0.171";

const int port = 3000;
WiFiClient client;
String output = "";
String comma = ",";

byte counter = 0;
byte sendValue = 0;
short value = 0;
char collect [5];
const int bufSize = 42000; 
byte clientBuf[bufSize];
int clientCount = 0;
void setup()
{
  pinMode(D8, OUTPUT);
  client.setNoDelay(true);
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
{
      while(client.connected()){
      long start = millis();//constant time 
        for(int i = 0;i<bufSize;i++){
          Wire.requestFrom(2, 1);    // request 2 bytes from slave device #2
          while(Wire.available()){    // slave may send less than requested
           clientBuf[i] = Wire.read(); // receive byte
           analogWrite(D8,clientBuf[i]);
            //value = (int)b<<(8*counter++);//need to accumulate into int
          //Serial.write((byte)clientBuf[i]);
            //itoa(value,collect,10)
            //output+=(collect + comma);
          }
        }
        counter = 0;//reset values
        value = 0;//reset values
          client.write(clientBuf,bufSize);
          //output = ""; 
          
        float tot =bufSize/(float(millis() - start)/1000.0);
        Serial.println(tot);
        }
        //Serial.write(clientBuf,bufSize);
       // client.write(clientBuf,bufSize);
        //client.print(value);
        //client.write not working?
        //collect a byte buffer
        //set a byteand ++ to collect values
        //value = 0;
        //counter = 0;
      
}
