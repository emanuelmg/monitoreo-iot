#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <PubSubClient.h>
#include <Adafruit_ADS1015.h>
#include <Wire.h>
#include "DHT.h"

#define DHTPIN 2  
#define DHTTYPE DHT21   

DHT dht(DHTPIN, DHTTYPE);

//Conexion a router
const char *ssid = "LIAPEP_PRO";
const char *pass = "powerlab";

const float multiplier = 0.000125F;
int16_t adc0, adc1, adc2, adc3;
const float Sensibilidad = 0.131;
 
//Conexion mqtt server
const char* mqtt_server = "monitoreoiot.ddns.net";
String USERNAME = "esp3";
WiFiClient espClient;
PubSubClient client(espClient);
char ESP3[50];
String strtemp ="";
String strtempp ="";
String strhum ="";
String strtp ="";
String strrad ="";
String stripanel ="";
char str_temp[15];
char str_tempp[15];
char str_hum[15];
char str_tp[15];
char str_rad[15];
char str_ipanel[15];
   

// Variables y constantes para el RTC
char HH = -7;
char MM = 00;
int conteo = 0;
const int muestra_min = 10;
unsigned int localPort = 2390;       // local port to listen for UDP packets
IPAddress timeServerIP;              // time.nist.gov NTP server address
const char* ntpServerName = "1.north-america.pool.ntp.org"; // Servidor pool
const int NTP_PACKET_SIZE = 48;       // NTP time stamp is in the first 48 bytes of the message
byte packetBuffer[ NTP_PACKET_SIZE]; 
WiFiUDP udp;

//ADC
Adafruit_ADS1115 ads;
//const float multiplier = 0.000125F;

//=======================================================================
//                     SETUP
//=======================================================================
void setup()
{
  pinMode(12, OUTPUT);
  dht.begin();
  Serial.begin(115200);
  Serial.println();
  Serial.println();
  Serial.setTimeout(2000);

  // Wait for serial to initialize.
  while(!Serial) { }
  Serial.println("I'm awake.");
  
  // We start by connecting to a WiFi network
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, pass);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    conteo = conteo + 1;
    if(conteo == 15){
       ESP.deepSleep(540e6);
      }
  }
  Serial.println("");
  
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  
  Serial.println(WiFi.localIP());
  client.setServer(mqtt_server, 1883);

  ads.setGain(GAIN_ONE);       // +/- 4.096V  1 bit = 0.125mV
  ads.begin();
  
  //Serial.println("Starting UDP");
  udp.begin(localPort);
  //Serial.print("Local port: ");
  //Serial.println(udp.localPort());
  digitalWrite(12, HIGH);
}

//=======================================================================
//  send an NTP request to the time server at the given address
//=======================================================================
unsigned long sendNTPpacket(IPAddress& address)
{
  //Serial.println("sending NTP packet...");
  // set all bytes in the buffer to 0
  memset(packetBuffer, 0, NTP_PACKET_SIZE);
  
  // Initialize values needed to form NTP request
  // (see URL above for details on the packets)
  packetBuffer[0] = 0b11100011;   // LI, Version, Mode
  packetBuffer[1] = 0;     // Stratum, or type of clock
  packetBuffer[2] = 6;     // Polling Interval
  packetBuffer[3] = 0xEC;  // Peer Clock Precision
  // 8 bytes of zero for Root Delay & Root Dispersion
  packetBuffer[12]  = 49;
  packetBuffer[13]  = 0x4E;
  packetBuffer[14]  = 49;
  packetBuffer[15]  = 52;
  
  udp.beginPacket(address, 123); //NTP requests are to port 123
  udp.write(packetBuffer, NTP_PACKET_SIZE);
  udp.endPacket();
}

void reconnect() {
 // Loop until we're reconnected
 while (!client.connected()) {
    Serial.print("Intentando conexion MQTT...");
    // Crea un ID de cliente al azar
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    USERNAME.toCharArray(ESP3, 50);
    if (client.connect(ESP3)) {
      Serial.println("conectado");
     } else {
      Serial.print("fallo, rc=");
      Serial.print(client.state());
      Serial.println(" intenta nuevamente en 5 segundos");
      // espera 5 segundos antes de reintentar
      delay(5000);
    }
  }
}  


//=======================================================================
//                        LOOP
//=======================================================================
void loop()
{
 

  // int16_t adc0, adc1, adc2, adc3;
 //  adc0 = ads.readADC_SingleEnded(0); 
 //  adc1 = ads.readADC_SingleEnded(1); 
 //  adc3 = ads.readADC_SingleEnded(3); 
   float humedad = 50;
   float temperatura = 25;
   float rad = (analogRead(A0)* (3.3/1024));
   
  
    Serial.println(rad);
    delay(1000);  
  }

  
  


//=======================================================================
