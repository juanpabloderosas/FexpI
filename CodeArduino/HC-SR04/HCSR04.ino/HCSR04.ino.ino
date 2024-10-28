unsigned long TOF = 0; // Tiempo de Vuelo (Time of Flight)en microsegundos
unsigned long ti = 0; // Tiempo inicio de medida, en microsegundos
unsigned long tf = 0; // Tiempo fin de medida, en microsegundos



const uint8_t Trig = 4; // 4 Dispara
const uint8_t Echo = 5; // 5 Recibe


void setup() {
  Serial.begin(9600);
pinMode(Trig, OUTPUT);
pinMode(Echo, INPUT);
}

void loop() {

digitalWrite(Trig, HIGH);
delayMicroseconds(10);
ti = micros();
digitalWrite(Trig, LOW); 


TOF = pulseIn(Echo, HIGH);
tf = micros();
Serial.print((tf + ti)/2);
Serial.print(",");
Serial.println(TOF);

delay(60);

}
