void setup() {
   Serial.begin(115200);
   delay(1000);

}

void loop() {
  // put your main code here, to run repeatedly:

  Serial.println((analogRead(A0)*3.3)/1024);
  delay(1000);
}
