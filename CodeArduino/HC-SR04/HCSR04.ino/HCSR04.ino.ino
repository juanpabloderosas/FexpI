unsigned long TOF = 0; // Tiempo de Vuelo (Time of Flight)en microsegundos

const uint8_t Trig = 4; // D4 Dispara
const uint8_t Echo = 5; // D5 Recibe


void setup() {
  Serial.begin(9600);
pinMode(Trig, OUTPUT);
pinMode(Echo, INPUT);
}

void loop() {


digitalWrite(Trig, HIGH);
delayMicroseconds(10);
digitalWrite(Trig, LOW); 

TOF = pulseIn(Echo, HIGH);

Serial.println(TOF);
delay(150);





}
