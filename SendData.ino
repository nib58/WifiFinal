#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>

const char* ssid     = "OnePiece";
const char* password = "Gear4Luffy";
const char* host = "http://10.0.0.171";
int buffer[1024];
int count = 0;
int value = 0;
void SendData(int *buff,int count)

{
  HTTPClient http;
  String uri = "http://10.0.0.171/php/add.php";
  String data = String("?value=") + *buff + "&amount=" + count;
  bool httpResult = http.begin(uri + data);
  if (!httpResult) {
    Serial.println("Invalid HTTP request:");
    Serial.println(uri + data);
  }
  int httpCode = http.GET();
  if (httpCode > 0) { // Request has been made
    //Serial.printf("HTTP status: %d\n", httpCode);
    //String payload = http.getString();
    //Serial.println(payload);
  } else { // Request could not be made
    Serial.printf("HTTP request failed. Error: %s\r\n", http.errorToString(httpCode).c_str());
  }
  http.end();
}

void setup() {
  pinMode(D0, INPUT); //Declare Pin mode for button
  Serial.begin(115200);
  delay(10);
  // We start by connecting to a WiFi network

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  /* Explicitly set the ESP8266 to be a WiFi-client, otherwise, it by default,
     would try to act as both a client and an access-point and could cause
     network-issues with your other WiFi-devices on your WiFi-network. */
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
 
 if(WiFi.status()== WL_CONNECTED){   //Check WiFi connection status
  
  //go to website below to view steps on verify functionality
  //https://randomnerdtutorials.com/esp8266-adc-reading-analog-values-with-nodemcu/
  
  //apply pull down resistor to GPIO16 input
  //while(digitalRead(button) == HIGH){
    //returns 10bit values 0-1024
    //analogRead(A0)
    
    for(int i = 0;i<1024;i++){
      buffer[i] = value;
    }
    SendData(buffer,count++);
 }
}