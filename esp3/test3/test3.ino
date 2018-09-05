void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  
  int val = analogRead(A0);
  val = map(val, 0, 1023, 0, 3300);
  Serial.print(val - 170);
  Serial.println(" mV");
  //float corriente = (voltaje - 2.5)/0.13103;
  
  //Serial.print("v:");Serial.println(voltaje);
  //Serial.print("I:");Serial.println(corriente);
  Serial.println(" ");
  delay(500);
}
