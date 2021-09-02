#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

const int pins[] = {A0};
const int pinCount = sizeof(pins)/sizeof(pins[0]);
const int analogPinCount = 1;
/*create an array of pins you will use
keep in mind analog pins first then digital
also update the count of Analog Pins above*/

const String baseApi = "http://localhost/a.php?";
const int ping_frequency = 1000;
const int retry_connecting_frequency = 1000;
const char ssid[] = "www.skubotics.in";
const char password[] = "Tunir1497";
const int serial_port = 115200;
const String retry_connecting_message = "Connecting..";
 
void setup () {
  Serial.begin(serial_port);
  WiFi.begin(ssid, password);
  for(int i=0;i<pinCount;i++)
    pinMode(pins[i],INPUT);
}
 
void loop() {
 
  if (WiFi.status() == WL_CONNECTED) {
    String dataApi="";
    for(int i=0;i<pinCount;i++){
      int sensorValue = i<analogPinCount?analogRead(pins[i]):digitalRead(pins[i]);
      String urlPart = "data"+String((i+1),DEC)+'='+String(sensorValue,DEC);
      if(i<pinCount-1)
        urlPart+='&';
      dataApi+=urlPart;
    }
    
    HTTPClient http;
    WiFiClient client;
    
    http.begin(client, (baseApi+dataApi).c_str());
    Serial.println(baseApi+dataApi);
    int httpCode = http.GET();
    
    if(httpCode > 0){
    // start of fetching get process
      String response = "";
      response = http.getString();
      Serial.print("Server Response: ");
      Serial.println(response);
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
