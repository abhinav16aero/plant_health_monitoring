
#include "pol.h"
#include "lm393.h"
#include "mpu6050.h"
#include <SoftwareSerial.h>

PollutantSensors pol = PollutantSensors();
LM393 lm393(A1); 
MPUSensor mpuSensor;

SoftwareSerial mySerial(10, 11);

void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);

  lm393.begin();
  mpuSensor.begin();
}

void loop() {
  pol.Sample(mySerial, Serial);
  Serial.print("Pollutant Sensor Data: ");
  Serial.println(pol.reading);

  lm393.WriteToBuff();
  Serial.print("LM393 Sensor Data: ");
  Serial.println(lm393.getReading());

  mpuSensor.WriteToBuff();
  Serial.print("MPU Sensor Data: ");
  Serial.println(mpuSensor.getReading());

  Serial.println("--------------------------------------------------");
  delay(1000);
}
