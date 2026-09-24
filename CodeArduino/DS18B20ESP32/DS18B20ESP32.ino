/* 

DS18B20 VCC → 3.3V del ESP32
**Conexiones**

DS18B20 GND → GND del ESP32

DS18B20 DATA → GPIO 4 (puedes usar otro, pero el código usa este)

Resistencia de 4.7kΩ: Conéctala entre DATA y VCC (3.3V). Es obligatoria para que la comunicación funcione
*/

#include <OneWire.h>
#include <DallasTemperature.h>
#include "BluetoothSerial.h"   // <-- Nuevo

// Pin donde conectaste el cable DATA del DS18B20
#define ONE_WIRE_BUS 4

// Configuración de las instancias OneWire
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

BluetoothSerial SerialBT;      

void setup() {
  Serial.begin(115200);
  SerialBT.begin("ESP32_TEMP"); // <-- Poner un nombre acá!

  Serial.println("\n\n***\nIniciando lectura de temperatura...");
  
  // Inicia la comunicación con el sensor
  sensors.begin();
  Serial.print("t(s), T(C)\n");
  SerialBT.println("t(s), T(C)");
  
}

void loop() {
  // Envía el comando para leer la temperatura
  sensors.requestTemperatures();
  
  // Obtiene la temperatura en grados Celsius del primer sensor
  
  float TEMP = sensors.getTempCByIndex(0);
  float t = (float) millis()/1000.0;
  // Muestra en el monitor serie
  Serial.print(t);
  Serial.print(",");
  Serial.println(TEMP);
  SerialBT.print(t);
  SerialBT.print(",");
  SerialBT.println(TEMP);

  
  // Espera 1 segundo antes de la próxima lectura
  delay(1000);
}