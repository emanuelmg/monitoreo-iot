#include <Wire.h>
#include <Adafruit_ADS1015.h>
 
Adafruit_ADS1115 ads1(0x48);
Adafruit_ADS1115 ads2(0x49);
const float multiplier = 0.000125F;
 
void setup(void) 
{
  Serial.begin(115200);
 
  // Descomentar el que interese
   //ads.setGain(GAIN_TWOTHIRDS);  //+/- 6.144V  1 bit = 0.1875mV (default)
   ads1.setGain(GAIN_ONE);       // +/- 4.096V  1 bit = 0.125mV
   ads2.setGain(GAIN_ONE);
  // ads.setGain(GAIN_TWO);        +/- 2.048V  1 bit = 0.0625mV
  // ads.setGain(GAIN_FOUR);         +/- 1.024V  1 bit = 0.03125mV
  // ads.setGain(GAIN_EIGHT);      +/- 0.512V  1 bit = 0.015625mV
  // ads.setGain(GAIN_SIXTEEN);    +/- 0.256V  1 bit = 0.0078125mV 
  ads1.begin();
  ads2.begin();

}
 
void loop(void) 
{
  int16_t adc0, adc1, adc2, adc3, adc4, adc5, adc6, adc7;
  adc0 = ads1.readADC_SingleEnded(0);
  adc1 = ads1.readADC_SingleEnded(1);
  adc2 = ads1.readADC_SingleEnded(2);
  adc3 = ads1.readADC_SingleEnded(3);
  adc4 = ads2.readADC_SingleEnded(0);
  adc5 = ads2.readADC_SingleEnded(1);
  adc6 = ads2.readADC_SingleEnded(2);
  adc7 = ads2.readADC_SingleEnded(3);

  //float v_panel = ( 5.6632 * (adc2 * multiplier)) - 0.0674; 
  //float i_panel = 7.717*(adc4 * multiplier) - 19.748;
  //float i_panel = ((adc4 * multiplier) - 2.5) / 0.13103;
  //float v_aero = (5.674 * (adc3 * multiplier)); 
  //float i_aero = (15.108 * (adc7 * multiplier)) - 38.541;
  //float i_aero = ((adc7 * multiplier) - 2.5) / 0.065; 
  //float vbat = (5.587 * (adc5 * multiplier));
  //float vac = (78.071 * (adc0 * multiplier)) + 0.2602;
  //float iac = (1.8066 * (adc1 * multiplier)) - 0.0176;
  //float tbat = ((adc6 * multiplier) * 100) - 273.15;
  
 

 float v_panel = 9.2716*(adc7 * multiplier) + 0.0003;
 float i_panel =23.532*(adc4 * multiplier)  - 58.768;
 float  v_aero = 9.2716*(adc3 * multiplier) + 0.0003;
 float i_aero =23.532*(adc2 * multiplier)  - 58.768;
 float vbat = (adc5 * multiplier);
 float tbat = (adc6 * multiplier) * 100;
 
 // float vac = ((adc0 * multiplier)-2.48) * (120/1.05);
  
  //float iac = 4.4828 * (adc1 *multiplier) + 0.0853;

  //float v_panel = 5.7249 * (adc2 * multiplier) - 0.161;
 //float i_panel = 15.874 * (adc4 * multiplier) - 39.579;

 // float v_aero = 5.6931 * (adc3 * multiplier) - 0.2044;
//  float i_aero = 15.291 * (adc7 * multiplier) - 38.115;
  
  //Serial.print("vac: "); Serial.println(vac);
  //Serial.print("vac: "); Serial.println(adc0 * multiplier);
  //Serial.print("iac: "); Serial.println(adc1 *multiplier);
  //Serial.print("vac: "); Serial.println(vac);
  //Serial.print("iac: "); Serial.println(iac);
  
 // Serial.print("v_panel: "); Serial.println(v_panel);
 // Serial.print("i_panel: "); Serial.println(i_panel);
  //Serial.print("v_panel: "); Serial.println(adc2 * multiplier);
  //Serial.print("i_panel: "); Serial.println(adc4 * multiplier);
  
  
 // Serial.print("v_aero: "); Serial.println(v_aero);
 // Serial.print("i_aero: "); Serial.println(i_aero);
  //Serial.print("v_aero_ "); Serial.println(adc3 * multiplier);
  //Serial.print("i_aero: "); Serial.println(adc7 * multiplier);
  
 // Serial.print("tbat: "); Serial.println(tbat);
 Serial.print("vbat: "); Serial.println(vbat);
  //Serial.print("i_aero: "); Serial.println(i_aero);
  Serial.println(" ");
  
  delay(500);
}
