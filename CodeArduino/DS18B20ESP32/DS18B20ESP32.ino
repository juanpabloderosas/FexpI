#include <OneWire.h>
#include <DallasTemperature.h>
#include "BluetoothSerial.h" // Librería nativa del ESP32

// Creamos el objeto para controlar el Bluetooth
BluetoothSerial SerialBT; 



// Pin del ESP32 donde se conecta la línea de datos (DQ)
#define ONE_WIRE_BUS 4

// Configura una instancia de oneWire para comunicarse con los dispositivos
OneWire oneWire(ONE_WIRE_BUS);

// Pasa la referencia de oneWire a la librería DallasTemperature
DallasTemperature sensors(&oneWire);

// Variable para almacenar el número de sensores encontrados
int numeroDeSensores;

void setup() {
  // Inicializa el monitor serie a 115200 baudios
  Serial.begin(115200);
  SerialBT.begin("ESP32_Transmision"); 
  
  
  
  Serial.println("--- Buscando sensores DS18B20 ---");
  SerialBT.println("--- Buscando sensores DS18B20 ---");
  //Inicializa la librería de los sensores
  sensors.begin();

  
  // Cuenta y muestra cuántos sensores hay en el bus
  numeroDeSensores = sensors.getDeviceCount();
  Serial.print("Sensores encontrados: ");
  Serial.println(numeroDeSensores);
  SerialBT.print("Sensores encontrados: ");
  SerialBT.println(numeroDeSensores);
  


  Serial.print("t,T_Santi,T_Nico,T_Agus\n");
  SerialBT.print("t,T_Santi,T_Nico,T_Agus\n");

}

void loop() {
  // Envía la orden a todos los sensores para que midan la temperatura
  sensors.requestTemperatures(); 
  

  float t = (float) millis()/1000.0000;
  Serial.print(t);
  Serial.print(",");

  SerialBT.print(t);
  SerialBT.print(",");


  for (int i = 0; i < numeroDeSensores; i++) {
    float T = sensors.getTempCByIndex(i);
    Serial.print(T);
    SerialBT.print(T);
    if(i < numeroDeSensores - 1){Serial.print(","); SerialBT.print(",");}
    }
  

  Serial.print("\n");
  SerialBT.print("\n");


  delay(4000); // Espera 2 segundos antes de la próxima lectura
}
