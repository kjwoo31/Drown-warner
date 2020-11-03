void setup()
{
 Serial.begin(9600);
}
void loop()
{
 int rubberVal = analogRead(A0);
 Serial.println(rubberVal);
 delay(1000);
}

