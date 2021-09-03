#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>

const char* ssid = "your_wifi_name";
const char* password = "your_wifi_password";
String serverName = "your_server_ip";
const char state_on = '1';
const char state_off = '0';
const int serial_port = 115200;
const int pins[] = {D0,D4,D2};
const int pinCount = sizeof(pins)/sizeof(pins[0]);
const int ping_frequency = 1000;

void setup() {
  Serial.begin(serial_port); 
  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
  for(int i=0;i<pinCount;i++)
    pinMode(pins[i],OUTPUT);
}

void loop() {
    if(WiFi.status()== WL_CONNECTED){
      WiFiClient client;
      HTTPClient http;
      String serverPath = serverName + "";
      http.begin(client, serverPath.c_str());
      int httpResponseCode = http.GET();
      if (httpResponseCode>0) {
        String payload = http.getString();
        Serial.println(payload);
        processPayload(payload);
      }
      else {
        Serial.print("Error code: ");
        Serial.println(httpResponseCode);
      }
      http.end();
    }
    else {
      Serial.println("WiFi Disconnected");
    }
    delay(ping_frequency);
}

void processPayload(String payload){
  for(int i=0;i<pinCount;i++){
    if(payload[i] == state_off)
      digitalWrite(pins[i],0);
    else if(payload[i] == state_on)
      digitalWrite(pins[i],1);  
  }
}
