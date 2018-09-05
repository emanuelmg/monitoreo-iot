#include <Wire.h>
#include <Adafruit_ADS1015.h>
 
Adafruit_ADS1115 ads;
const float multiplier = 0.000125F;
int16_t adc0, adc1, adc2, adc3;
#include <Wire.h>
#include "DHT.h"
//const float Sensibilidad = 0.1306;
#define DHTPIN 2  
#define DHTTYPE DHT21   

DHT dht(DHTPIN, DHTTYPE);

 
void setup(void) 
{
  Serial.begin(115200);
 
  // Descomentar el que interese
   //ads.setGain(GAIN_TWOTHIRDS);  //+/- 6.144V  1 bit = 0.1875mV (default)
   ads.setGain(GAIN_ONE);       // +/- 4.096V  1 bit = 0.125mV
   //ads2.setGain(GAIN_ONE);
  // ads.setGain(GAIN_TWO);        +/- 2.048V  1 bit = 0.0625mV
  // ads.setGain(GAIN_FOUR);         +/- 1.024V  1 bit = 0.03125mV
  // ads.setGain(GAIN_EIGHT);      +/- 0.512V  1 bit = 0.015625mV
  // ads.setGain(GAIN_SIXTEEN);    +/- 0.256V  1 bit = 0.0078125mV 
  ads.begin();
  pinMode(12, OUTPUT);
  digitalWrite(12, HIGH);
  
}
 
void loop(void) 
{
  //int16_t adc0, adc1, adc2, adc3;
  adc0 = ads.readADC_SingleEnded(0);
  //adc1 = ads.readADC_SingleEnded(1);
  //adc2 = ads.readADC_SingleEnded(2);
 // adc3 = ads.readADC_SingleEnded(3);

  float ipanel = 9.526 * (adc0 * multiplier) - 23.806;
  float humedad = dht.readHumidity();
   float temperatura = dht.readTemperature();
  //float ipanel = (adc0 * multiplier);
  //float ipanel=get_corriente(1000);
  
  Serial.print("ipanel: "); Serial.println(ipanel, 3);
   Serial.print("temp: "); Serial.println(temperatura);
    Serial.print("hum: "); Serial.println(humedad);
  //Serial.print("v: "); Serial.println((((analogRead(A0)*3.3)/1024) - 0.013), 3);
  //Serial.print("ipanel: "); Serial.println(adc2 * multiplier);
  //Serial.print("ipanel: "); Serial.println(adc3 * multiplier);
  delay(500);
}

float get_corriente(int n_muestras)
{
  
  adc0 = ads.readADC_SingleEnded(0);
  float voltajeSensor;
  float corriente=0;
  for(int i=0;i<n_muestras;i++)
  {
   //voltajeSensor = voltajeSensor + (adc0 * multiplier);
  
   voltajeSensor = (adc0 * multiplier);
   //corriente=corriente+(voltajeSensor-2.507)/Sensibilidad;
    corriente = corriente+(6.8648 * voltajeSensor - 17.189);  
  }
  //voltajeSensor = (voltajeSensor/n_muestras);
  //return(voltajeSensor);
  corriente=corriente/n_muestras;
  return(corriente);
} 

