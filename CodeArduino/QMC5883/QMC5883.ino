#include <avr/pgmspace.h>
#include <QMC5883LCompass.h>
#include <Wire.h>



QMC5883LCompass compass;

 float gaincorx = 1.017745303*0.0333;
 float gaincory = 1.005154639*0.0317;
 float gaincorz = 1.024159664*0.0336;

// the memory buffer for the LCD

void setup() {
  Serial.begin(230400);
  compass.init();
   
}

void loop() {
  
 int x, y, z, n;

uint32_t t0 = micros();
   compass.read();
uint32_t t1 = micros();

  x = compass.getX();
  y = compass.getY();
  z = compass.getZ();

Serial.print((t1+t0)/2000000.00, 10);
Serial.print(",");
Serial.print(x);
Serial.print(",");
Serial.print(y);
Serial.print(",");
Serial.println(z);
delay(100);
}
