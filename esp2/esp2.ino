#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include "TSL2561.h"
#include <Wire.h>


#include "DHT.h"

#define DHTPIN 2  
#define DHTTYPE DHT21   

TSL2561 tsl(TSL2561_ADDR_FLOAT); 

int contconexion = 0;
unsigned long previousMillis = 0;
unsigned long previousMillis2 = 0;

const char *ssid = "LIAPEP_PRO";
const char *password = "powerlab";
const char* mqtt_server = "monitoreoiot.ddns.net";
String USERNAME = "esp2";   

WiFiClient espClient;
PubSubClient client(espClient);
DHT dht(DHTPIN, DHTTYPE);

char ESP2[50];

char REQUEST[50];
char STAT[50];
char CONTROL[50];
int flag_request_temp = 0;
int control_flag = 0;
int db_flag = 0;

String strtemp ="";
String strhum ="";
String strlux ="";
String strdew ="";


char str_temp[15];
char str_hum[15];
char str_lux[15];
char str_dew[15];





//------------------------CALLBACK-----------------------------
void callback(char* topic, byte* payload, unsigned int length) {

  char PAYLOAD[5] = "    ";
  
  Serial.print("Mensaje Recibido: [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    PAYLOAD[i] = (char)payload[i];
  }
  
  if (String(topic) ==  String(REQUEST)){
    if (payload[0] == 'T'){
     flag_request_temp = 1;
    }
  } 
  else if(String(topic) ==  String("control")) {
    if (payload[0] == 'A'){
     control_flag = 1;
    }
    else if (payload[0] == 'M'){
      control_flag = 0;
    }
  }
  else if(String(topic) ==  String(STAT))
  {
     if (payload[0] == 'S'){
    client.publish(STAT, "ACK");
    }
 
  } else if(String(topic) ==  "database")  
    if(payload[0] == 'Z'){
      db_flag = 1;
    }
     
}

void reconnect() {
 // Loop until we're reconnected
 while (!client.connected()) {
    Serial.print("Intentando conexion MQTT...");
    // Crea un ID de cliente al azar
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    USERNAME.toCharArray(ESP2, 50);
    if (client.connect(ESP2)) {
      Serial.println("conectado");
       // ... and subscribe to topic
      client.subscribe(REQUEST);
      client.subscribe(STAT);
      client.subscribe("control");
      client.subscribe("database");
     } else {
      Serial.print("fallo, rc=");
      Serial.print(client.state());
      Serial.println(" intenta nuevamente en 5 segundos");
      // espera 5 segundos antes de reintentar
      delay(5000);
    }
  }
}  

void setup() {

  Wire.begin();
  Serial.begin(115200);
  dht.begin();
  //ads.setGain(GAIN_ONE);      //  +/- 4.096V  1 bit = 0.125mV
  //ads.begin();
  
    // Conexión WIFI
 Serial.print("Connecting to ");
 Serial.println(ssid);
 WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);



String request = "/" + USERNAME + "/" + "request"; 
request.toCharArray(REQUEST, 50);
String estado = "/" + USERNAME + "/" + "status"; 
estado.toCharArray(STAT, 50);

 if (tsl.begin()) {
    Serial.println("Found sensor");
  } else {
    Serial.println("No sensor?");
    while (1);
  }
   
  tsl.setGain(TSL2561_GAIN_16X);   
  tsl.setTiming(TSL2561_INTEGRATIONTIME_13MS);  
  // Now we're ready to get readings!


}

void loop()
{
  //int16_t adc0, adc1, adc2, adc3;
   uint16_t x = tsl.getLuminosity(TSL2561_VISIBLE);
   if (!client.connected()) {
    reconnect();
   }
   client.loop();
  
    uint32_t lum = tsl.getFullLuminosity();
    uint16_t ir, full;
    ir = lum >> 16;
    full = lum & 0xFFFF;
    int lux = tsl.calculateLux(full, ir);

  float humedad = dht.readHumidity();
  float temperatura = dht.readTemperature();
  float dewp = (pow((humedad/100), 0.125)) * (112 + 0.9 * temperatura)+ 0.1 * temperatura - 112;
  
  
  //Serial.print("h: "); Serial.println(humedad); 
  //Serial.print("T: "); Serial.println(temperatura);
  //Serial.print("pow: "); Serial.println(pow((humedad/100), 0.125)); 
    
  unsigned long currentMillis = millis();
 
  if (currentMillis - previousMillis >= 5000){ 
      previousMillis = currentMillis;   
     
        if(flag_request_temp == 1 || db_flag == 1){ 
            if(control_flag == 1){
              client.publish("contstat","N");
            }else{
              client.publish("contstat","F");
            }
            
            strtemp = String(temperatura, 2);
            strtemp.toCharArray(str_temp, 15);
            Serial.print("Send Temperatura: ");
            Serial.println(str_temp);
            client.publish("/esp2/temp", str_temp);
   
            strhum = String(humedad, 2);
            strhum.toCharArray(str_hum, 15);
            Serial.print("Send Humedad: ");
            Serial.println(str_hum);
            client.publish("/esp2/hum", str_hum);
 
            //Serial.print("Lux: "); Serial.println(lux);
            strlux = String(lux);
            strlux.toCharArray(str_lux, 15);
            Serial.print("Send Lux: ");
            Serial.println(str_lux);
            client.publish("lux", str_lux);

            strdew = String(dewp);
            strdew.toCharArray(str_dew, 15);
            Serial.print("Send Dew_point: ");
            Serial.println(str_dew);
            client.publish("dew", str_dew);
        
            flag_request_temp = 0;
            db_flag = 0;
      
      }
      
     }
     if (currentMillis - previousMillis2 >= 60000){ 
      previousMillis2 = currentMillis; 
      if(control_flag == 1){
        if(dewp >= 19){
            client.publish("aba", "ON");        
          }
         else if(dewp < 19){
            client.publish("aba", "OFF");
          }

         if(lux < 60){
             client.publish("foco", "ON");  
         }
         else if (lux >= 60){
             client.publish("foco", "OFF");
         }
       }
     }
  }
 
