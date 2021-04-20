#include <WiFi.h>
#include <HTTPClient.h>

// Replace with your network credentials
const char* ssid     = "YOUR WIFI SSID";
const char* password = "YOUR WIFI PASS";

// REPLACE with your Domain name and URL path or IP address with path
const char* serverName = "../read_water_pump.php";

#define WATER_PUMP 27
boolean state = false;

void setup() {
  
  pinMode(WATER_PUMP, OUTPUT);
  Serial.begin(115200);
  delay(4000);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }

  Serial.println("Connected to the WiFi network");

}

void loop() {
 
  if ((WiFi.status() == WL_CONNECTED)) {
 
    HTTPClient http;
 
    http.begin(serverName);
    int httpCode = http.GET();
 
    if (httpCode > 0) { 

        String payload = http.getString();
        Serial.println(payload);
      
        if(payload == "1"){
            // Trigger the water pump
            digitalWrite(WATER_PUMP,HIGH);
            delay(0);
        }
        else{
          digitalWrite(WATER_PUMP,LOW);
        }
      
      }
    else {
      Serial.println("Error on HTTP request");
    }
 
    http.end();
  }
 
  delay(0);
 
}
