#include <OneWire.h>
#include <DallasTemperature.h>

/********************************************************************/
// Data wire is plugged into pin 2 on the Arduino 
#define ONE_WIRE_BUS 2

/********************************************************************/
// Setup a oneWire instance to communicate with any OneWire devices  
// (not just Maxim/Dallas temperature ICs) 
OneWire oneWire(ONE_WIRE_BUS); 
/********************************************************************/
// Pass our oneWire reference to Dallas Temperature. 
DallasTemperature sensors(&oneWire);
/********************************************************************/ 




void setup(void) 
          { 
            Serial.begin(9600); // Comienza el puerto Serie (comunicación con la computadora)
            sensors.begin(); //Inicialize
            sensors.setResolution(12); 
          } 



void loop(void) 
              { 

              sensors.requestTemperatures(); // Send the command to get temperature readings 
              float T0 = sensors.getTempCByIndex(0); // obtenemos la única temperatura (si hay más termómetros, entonces 1,2,3,...,127)
              uint32_t t = millis();
              
              Serial.print(t/1000.0);
              Serial.print(",");
              Serial.println(T0,4);  

              delay(1000); 
              } 
