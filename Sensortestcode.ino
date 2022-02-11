const int analogInPin = A0; //ESP8266 Analog Pin ADC0 = A0
int sensorValue = 0;  // value read from the pot
void setup() 
{
Serial.begin(115200); // activates Serial Communication
}

void loop() {
  // read the analog in value
  sensorValue = analogRead(analogInPin);
 
  // print the readings in the Serial Monitor
  Serial.print("sensor = ");
  Serial.print(sensorValue);
  
  delay(1000);
}
