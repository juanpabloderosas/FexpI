unsigned long TOF = 0; // Tiempo de Vuelo (Time of Flight)en microsegundos
unsigned long t_i = 0;
unsigned long t_f = 0;

const uint8_t Trig = 4; // 4 Dispara
const uint8_t Echo = 5; // 5 Recibe





void setup() {
  Serial.begin(230400);
pinMode(Trig, OUTPUT);
pinMode(Echo, INPUT);
Serial.println(F("#Nuevo Loggeo\nt_s,TOF_us"));              
}

void loop() {

            digitalWrite(Trig, HIGH);
            delayMicroseconds(20);
            t_i = micros();
            digitalWrite(Trig, LOW); 

            TOF = pulseIn(Echo, HIGH);
            t_f = micros();

            Serial.print((t_i + t_f) / 2000000.000);
            Serial.print(",");      
            Serial.println(TOF);
            delay(50);
 
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