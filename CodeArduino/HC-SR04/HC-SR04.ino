unsigned long TOF = 0; // Tiempo de Vuelo (Time of Flight)en microsegundos


const uint8_t Trig = 4; // 4 Dispara
const uint8_t Echo = 5; // 5 Recibe





void setup() {
  Serial.begin(230400);
pinMode(Trig, OUTPUT);
pinMode(Echo, INPUT);
Serial.print("ingrese medidas de distancia d en mm\n");
Serial.println(F("#Nuevo Loggeo\ni,d_mm,TOF_us"));              
}

void loop() {
uint16_t d = readUint16();

        for(int i = 0; i < 5000; i++){
            digitalWrite(Trig, HIGH);
            delayMicroseconds(20);
            digitalWrite(Trig, LOW); 

            TOF = pulseIn(Echo, HIGH);
            Serial.print(i);
            Serial.print(",");
            Serial.print(d);
            Serial.print(",");      
            Serial.println(TOF);
            delay(80);
        }

}

uint16_t readUint16(void) {
                  String inputString;
                  char charBuffer[5];
                  uint16_t number = 0;

                  while (!Serial.available()) {}
                  if (Serial.available() > 0) {
                    inputString = Serial.readStringUntil('\n');
                    inputString.substring(0, 5).toCharArray(charBuffer, 6);
                    number = atoi(charBuffer);
                  }
                  return number;
}