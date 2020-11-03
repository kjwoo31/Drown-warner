int Electromagnet = 10;
 
// the setup routine runs once when you press reset:
void setup() {                
  // initialize the digital pin as an output.
  pinMode(Electromagnet, OUTPUT); 
}
 
// the loop routine runs over and over again forever:
void loop() {
  digitalWrite(Electromagnet, HIGH); // turn the Electromagnet on (HIGH is the voltage level)
  Serial.println("on");
  delay(9000);               // wait for a second
}
