#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <Adafruit_ADS1015.h>
#include <Wire.h>


unsigned long previousMillis = 0;


Adafruit_ADS1115 ads1(0x48);
Adafruit_ADS1115 ads2(0x49);
//const float multiplier = 0.0001875F;
const float multiplier = 0.000125F;

//const char *ssid = "ARRIS-CA02";
//const char *password = "A434F4CA8BC88C56";
const char *ssid = "LIAPEP_PRO";
const char *password = "powerlab";
const char* mqtt_server = "monitoreoiot.ddns.net";
const String USERNAME = "esp1";   


WiFiClient espClient;
PubSubClient client(espClient);

char ESP1[50];


char REQUEST[50];
char STAT[50];
int flag_request;

char strvpanel[15];
char stripanel[15];
char strwpanel[15];
char strvaero[15];
char striaero[15];
char strwaero[15];
char strvac[15];
char striac[15];
char strwac[15];
char strvbat[15];
char strtbat[15];

String strvp ="";
String strip ="";
String strwp ="";
String strva ="";
String stria ="";
String strwa ="";
String strvc ="";
String stric ="";
String strwc ="";
String strvb ="";
String strtb ="";


int flag_r = 0;
int flag_p = 0;
int flag_a = 0;
int flag_c = 0;
int flag_b = 0;

int carga_flag = 0;
int control_flag = 0;
int foco_flag = 0;
int db_flag = 0;
int cambio_flag = 0;

  

//------------------------CALLBACK-----------------------------
void callback(char* topic, byte* payload, unsigned int length) {

  char PAYLOAD[5] = "    ";
  
  //Serial.print("Mensaje Recibido: [");
  //Serial.print(topic);
  //Serial.println("] ");
  for (int i = 0; i < length; i++) {
    PAYLOAD[i] = (char)payload[i];
  }
  Serial.println(PAYLOAD);
  if (String(topic) ==  String(REQUEST)){
    if(payload[0] == 'P'){
      flag_p = 1;
    }
    else if(payload[0] == 'A'){
      flag_a = 1;
    }
    else if(payload[0] == 'C'){
      flag_c = 1;
    }
    else if(payload[0] == 'B'){
      flag_b = 1;
    }
    else  if (payload[0] == 'R'){
      flag_r = 1;
    }
  }
  
  else if(String(topic) ==  "control") {
    if (payload[1] == 'A'){
     control_flag = 1;
    }
    else if (payload[1] == 'M'){
      control_flag = 0;
    }
  } 
  
  else if(String(topic) ==  "foco") {
    cambio_flag = 1;
    if (payload[1] == 'N'){
    foco_flag = 1;
    }
    else if(payload[1] == 'F'){
    foco_flag = 0;   
    }
  }
    
  else if(String(topic) ==  "ava") {
    if (payload[1] == 'N'){
     digitalWrite(13, LOW);//D7
    }
    else if (payload[1] == 'F'){
      digitalWrite(13, HIGH);
    }
  } 

   else if(String(topic) == String(STAT)){
    if(payload[0] == 'S'){
      client.publish("/esp1/status", "ACK");
      carga_flag = 1;
    }
   }
  else if(String(topic) == "database"){
    if(payload[0] == 'Z'){
      db_flag = 1;
    }
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
    USERNAME.toCharArray(ESP1, 50);
    if (client.connect(ESP1)) {
      Serial.println("conectado");
       // ... and subscribe to topic
      client.subscribe(REQUEST);
      client.subscribe(STAT);
      client.subscribe("foco");
      client.subscribe("ava");
      client.subscribe("control");
      client.subscribe("database");
      client.subscribe("/esp1/request");
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

client.setCallback(callback);
//ads1.setGain(GAIN_TWOTHIRDS);  //+/- 6.144V  1 bit = 0.1875mV (default)
//ads2.setGain(GAIN_TWOTHIRDS);

ads1.setGain(GAIN_ONE);       // +/- 4.096V  1 bit = 0.125mV
ads2.setGain(GAIN_ONE);

ads1.begin();
ads2.begin();
pinMode(13, OUTPUT);
pinMode(12, OUTPUT);
   
String request = "/" + USERNAME + "/" + "request"; 
request.toCharArray(REQUEST, 50);
String estado = "/" + USERNAME + "/" + "status"; 
estado.toCharArray(STAT, 50);

}

void loop()
{
 
 if (!client.connected()) {
 reconnect();
 }
 client.loop();

      
 unsigned long currentMillis = millis();
if ((currentMillis - previousMillis >= 5000)) { //muestrea cada 5 segundos
    previousMillis = currentMillis;
  //Serial.println(flag_r);
  //Serial.println(cambio_flag);
 if(flag_r == 1 || db_flag == 1 || cambio_flag == 1 || flag_b == 1 || flag_p == 1 || flag_a == 1 || flag_c == 1){
  Serial.println(digitalRead(12));
      int16_t adc0, adc1, adc2, adc3,adc4, adc5, adc6, adc7;
      adc0 = ads1.readADC_SingleEnded(0);
      adc1 = ads1.readADC_SingleEnded(1);
      adc2 = ads1.readADC_SingleEnded(2);
      adc3 = ads1.readADC_SingleEnded(3);
      adc4 = ads2.readADC_SingleEnded(0);
      adc5 = ads2.readADC_SingleEnded(1);
      adc6 = ads2.readADC_SingleEnded(2);
      adc7 = ads2.readADC_SingleEnded(3);
         
     float i_ac = adc1 *multiplier;
     Serial.println(i_ac);
     if(flag_c == 1 || db_flag == 1 || flag_r == 1 || cambio_flag == 1){ 
      if(i_ac > 0.09 && i_ac < 0.17){ //Foco OFF - abanico ON
        i_ac = 0.4;
        client.publish("cstat", "1");
        Serial.println("cstat 1");
        if(cambio_flag == 1){
         if(digitalRead(12) == 1){
          if(foco_flag == 1){  
            digitalWrite(12, LOW);
           }
          }else if(digitalRead(12) == 0){
            if(foco_flag == 1){  
            digitalWrite(12, HIGH);
           }
          }cambio_flag = 0;
         }
      }else if(i_ac > 0.17 && i_ac < 0.22){ //Foco ON - abanico OFF
        i_ac = 0.9;
        client.publish("cstat", "2");
        Serial.println("cstat 2");
         if(cambio_flag == 1){
         if(digitalRead(12) == 1){
          if(foco_flag == 0){  
            digitalWrite(12, LOW);
           }
          }else if(digitalRead(12) == 0){
            if(foco_flag == 0){  
            digitalWrite(12, HIGH);
           }
          }cambio_flag = 0;
         }
      }else if(i_ac > 0.22 && i_ac < 0.40){//Foco ON - abanico ON
        i_ac = 1.3;
        client.publish("cstat", "3");
        Serial.println("cstat 3");
       if(cambio_flag == 1){
         if(digitalRead(12) == 1){
          if(foco_flag == 0){  
            digitalWrite(12, LOW);
           }
          }else if(digitalRead(12) == 0){
            if(foco_flag == 0){  
            digitalWrite(12, HIGH);
           }
          }cambio_flag = 0;
         }
      }else if(i_ac < 0.07){ //Foco OFF - abanico OFF
        i_ac = 0;
        client.publish("cstat", "4");
        Serial.println("cstat 4");
        if(cambio_flag == 1){
         if(digitalRead(12) == 1){
          if(foco_flag == 1){  
            digitalWrite(12, LOW);
           }
          }else if(digitalRead(12) == 0){
            if(foco_flag == 1){  
            digitalWrite(12, HIGH);
           }
          }cambio_flag = 0;
         }
       } 
     }

      float v_ac = (adc0 * multiplier);
      if(v_ac > 2.5){
         v_ac = v_ac * (120.7/3.55); 
        }
       else{
         v_ac = 0; //*multiplier) + 0.0853;
        }
          
       float v_panel = 9.2716*(adc7 * multiplier) + 0.0003;
       float i_panel =23.532*(adc4 * multiplier)  - 58.768;
       if(i_panel < 0.001){
        i_panel = 0;
       }
       float  v_aero = 9.2716*(adc3 * multiplier) + 0.0003;
       float i_aero =23.532*(adc2 * multiplier)  - 58.768;
       if(i_aero < 0.001){
        i_aero = 0;
       }
       float v_bat = -55.108 * (adc5 * multiplier) + 139.66;
       float t_bat = (adc6 * multiplier) * 100;
        
       float w_panel = v_panel * i_panel;
       float w_aero = v_aero * i_aero;
       float w_ac = i_ac * v_ac;
       //float w_ac = v_ac;
       
       
        if(flag_p == 1 || db_flag == 1){
           Serial.println(adc4 * multiplier);
           strvp = String(v_panel, 2); 
           strvp.toCharArray(strvpanel, 15);
           client.publish("vpanel", strvpanel);
           Serial.print("vpanel: "); Serial.println(v_panel);

           strip = String(i_panel, 2); 
           strip.toCharArray(stripanel, 15);
           client.publish("ipanel", stripanel);
           Serial.print("ipanel: "); Serial.println(i_panel);

           strwp = String(w_panel, 2);
           strwp.toCharArray(strwpanel, 15);
           client.publish("wpanel", strwpanel);
           Serial.print("wpanel: "); Serial.println(w_panel);
           flag_p = 0;
        }
        if(flag_c == 1 || db_flag == 1){
           strvc = String(v_ac, 2); 
           strvc.toCharArray(strvac, 15);
           Serial.print("vac: "); Serial.println(v_ac);
           client.publish("vac", strvac);
           

           stric = String(i_ac, 2); 
           stric.toCharArray(striac, 15);
           Serial.print("iac: "); Serial.println(i_ac);
           client.publish("iac", striac);

           strwc = String(w_ac, 2); 
           strwc.toCharArray(strwac, 15);
           Serial.print("wac: "); Serial.println(w_ac);
           client.publish("wac", strwac);
          flag_c = 0;
        }
        if(flag_a == 1 || db_flag == 1){
           strva = String(v_aero, 2); 
           strva.toCharArray(strvaero, 15);
           client.publish("vaero", strvaero);
           Serial.print("vaero: "); Serial.println(v_aero);

           stria = String(i_aero, 2); 
           stria.toCharArray(striaero, 15);
           client.publish("iaero", striaero);
           Serial.print("iaero: "); Serial.println(i_aero);

           strwa = String(w_aero, 2); 
           strwa.toCharArray(strwaero, 15);
           client.publish("waero", strwaero);
           Serial.print("waero: "); Serial.println(w_aero);
           flag_a=0;
        } 
        if(flag_b == 1 || db_flag == 1){
             strvb = String(v_bat, 2); 
             strvb.toCharArray(strvbat, 15);
             client.publish("vbat", strvbat);

             strtb = String(t_bat, 2); 
             strtb.toCharArray(strtbat, 15);
             client.publish("tbat", strtbat);
            flag_b=0;
        }  
        db_flag = 0; 
        flag_r = 0;   
  }
 }
}


