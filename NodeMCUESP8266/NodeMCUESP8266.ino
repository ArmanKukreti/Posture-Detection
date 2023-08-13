#include <SoftwareSerial.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ArduinoJson.h>

WiFiClient client;
const char* ssid = "moto g62 5G";
const char* password = "sumit2606";

const char* serverName = "http://thetechiesposturedetection.000webhostapp.com//post-data.php";;
 
String apiKeyValue = "54321";


void setup(){
	Serial.begin(9600);
while (!Serial) {
; // wait for serial port to connect. Needed for native USB port only
}

  WiFi.begin(ssid, password);
  Serial.println("Connecting to the Wifi Network");
  while(WiFi.status() != WL_CONNECTED) { 
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("WiFi is Connected at this IP Address : ");
  Serial.println(WiFi.localIP());
}


void loop(){

  if(Serial.available()) {
      // Read the incoming JSON string from Serial
      String jsonString = Serial.readStringUntil('\n');

      // Parse the JSON string
      DynamicJsonDocument jsonDoc(128);
      DeserializationError error = deserializeJson(jsonDoc, jsonString);

      if (error) {
        Serial.print("Parsing failed: ");
        Serial.println(error.c_str());
      } else {
        // Extract data from the JSON object
        float TopDistance = jsonDoc["TopDistance"];
        float BottomDistance = jsonDoc["BottomDistance"];
        float SetDistance = jsonDoc["SetDistance"];
        float Delay = jsonDoc["Delay"];

        // Process the received data
        Serial.print("TopDistance : ");
        Serial.println(TopDistance);
        Serial.print("BottomDistance : ");
        Serial.println(BottomDistance);
        Serial.print("SetDistance : ");
        Serial.println(SetDistance);
        Serial.print("Delay : ");
        Serial.println(Delay);




        if(WiFi.status()== WL_CONNECTED){
          HTTPClient http;
          
          http.begin(client,serverName);
          
          http.addHeader("Content-Type", "application/x-www-form-urlencoded");
          // Prepare your HTTP POST request data
          String httpRequestData = "api_key=" + apiKeyValue + "&TopDistance=" + TopDistance
                                + "&BottomDistance=" + BottomDistance + "&SetDistance=" + SetDistance
                                + "&Delay=" + Delay;
          //String httpRequestData ="api_key=54321&SensorData=distance sensor&LocationData=Aicpecf-office&value1=NULL&value2=NULL&value3=NULL";
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
      
          http.end();
        }
      }
  }

  else {
    Serial.println("WiFi Disconnected");
  }


}








