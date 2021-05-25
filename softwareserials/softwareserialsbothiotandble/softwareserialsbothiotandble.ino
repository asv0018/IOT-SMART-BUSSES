#include<SoftwareSerial.h>
SoftwareSerial iot(A10,A11);
SoftwareSerial ble(A9,A8);
void setup() {
Serial.begin(9600);
iot.begin(9600);
ble.begin(9600);
}

void loop() {
connectble();
}
void connectble()
{
  if (ble.available())
    Serial.write(ble.read());
  if (Serial.available())
    ble.write(Serial.read()); 
}
void connectiot()
{
  if (iot.available())
    Serial.write(iot.read());
  if (Serial.available())
    iot.write(Serial.read()); 
}
