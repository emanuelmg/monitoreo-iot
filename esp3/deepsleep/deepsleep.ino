/**
 * An example showing how to put ESP8266 into Deep-sleep mode
 */

#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

const char *ssid = "LIAPEP_PRO";
const char *pass = "powerlab";

 
void setup() {
  Serial.begin(115200);
  Serial.setTimeout(2000);

  // Wait for serial to initialize.
  while(!Serial) { }
  
  Serial.println("I'm awake.");

  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, pass);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  
  Serial.println("Going into deep sleep for 60 seconds");
  ESP.deepSleep(600e6); // 20e6 is 20 microseconds
}

void loop() {
}

