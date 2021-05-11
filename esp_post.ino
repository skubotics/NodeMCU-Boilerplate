#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

const int pins[] = {D0,D1,D2};
const int pinCount = sizeof(pins)/sizeof(pins[0]);
//create an array of pins you will use

const String api = "your_link_here";
const char state_on = '1';
const char state_off = '0';
const int ping_frequency = 1000;
const int retry_connecting_frequency = 1000;
const char ssid[] = "hotspot_name";
const char password[] = "hotspot_pass";
const int serial_port = 115200;
const String retry_connecting_message = "Connecting..";
 
void setup () {
  Serial.begin(serial_port);
  WiFi.begin(ssid, password);
  for(int i=0;i<pinCount;i++)
    pinMode(pins[i],OUTPUT);
}
 
void loop() {
 
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(api);
    int httpCode = http.GET();
    
    if(httpCode > 0){
    // start of fetching get process
      String response = "";
      response = http.getString();
      Serial.print("Server Response: ");
      Serial.println(response);

      for(int i=0;i<pinCount;i++){
        if(response[i] == state_off)
          digitalWrite(pins[i],0);
        else if(response[i] == state_on)
          digitalWrite(pins[i],1);  
      }
    }
    else
      Serial.println(httpCode);
      
    http.end();
    // end of fetching get process
  }
  else{
    delay(retry_connecting_frequency);
    Serial.print(retry_connecting_message);
  }
  delay(ping_frequency);
}