//Muhammad Azizi Mohd Ariffin
//mazizi@tmsk.uitm.edu.my
//ESP8266 with Cloud Server

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include "DHT.h"

#define DHTTYPE DHT11

uint8_t DHTPin = D4;
uint8_t relayPin = D0; 
               
DHT dht(DHTPin, DHTTYPE);                

float Temperature;
float Humidity;

//const char* ssid     = "AziSheNetwork2.4@unifi";
const char* ssid     = "Azizi";
const char* password = "0178822437";

const char* serverName = "http://165.22.98.67//post-esp-data.php";

String apiKeyValue = "tPmAT5Ab3j7F9";

String sensorName = "DHT11";
String sensorLocation = "IoTDemo";

void setup()
{
  Serial.begin(9600);
  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) { 
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
  
  dht.begin();
  
  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, HIGH);
}

void loop()
{
  if(WiFi.status()== WL_CONNECTED){
    HTTPClient http;
    
    http.begin(serverName);
    
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");
    
    String httpRequestData = "api_key=" + apiKeyValue + "&sensor=" + sensorName + "&location=" + sensorLocation + "&value1=" + String(dht.readTemperature()) + "&value2=" + String(dht.readHumidity()) + "&value3=" + String(0.00) + "";
    Serial.print("httpRequestData: ");
    Serial.println(httpRequestData);

    int httpResponseCode = http.POST(httpRequestData);
    if (httpResponseCode>0) {
      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);
    }
    else {
      Serial.print("Error code: ");
      Serial.println(httpResponseCode);
    }
    // Free resources
    http.end();
  }
  else {
    Serial.println("WiFi Disconnected");
  }
  

  if(dht.readHumidity()>= 62.00 ){
   digitalWrite(relayPin, LOW);
   delay(10000);
   digitalWrite(relayPin, HIGH); 
  }
  else{
    delay(10000);
  }
}
