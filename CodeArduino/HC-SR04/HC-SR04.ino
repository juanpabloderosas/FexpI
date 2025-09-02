unsigned long TOF = 0; // Tiempo de Vuelo (Time of Flight)en microsegundos
unsigned long t_inicio = 0; //tiempo de inicio de cada serie de medidas
unsigned long ti = 0; // Tiempo inicio de medida, en microsegundos
unsigned long tf = 0; // Tiempo fin de medida, en microsegundos



const uint8_t Trig = 4; // 4 Dispara
const uint8_t Echo = 5; // 5 Recibe





void setup() {
  Serial.begin(230400);
pinMode(Trig, OUTPUT);
pinMode(Echo, INPUT);
}

void loop() {
Serial.begin(230400);
Serial.print(F("#Presione una tecla para comenzar una medida\n#(y una tecla para pararla)\n"));
while(!Serial.available()){
                          if(Serial.available()) {
                          break;
                          }
              }

Serial.end(); //apaga para vaciar el serial (no conozco otra forma menos rústica)

Serial.begin(230400);
Serial.println(F("#Nuevo Loggeo\nt_us,TOF_us"));              
t_inicio = micros();

do{
digitalWrite(Trig, HIGH);
delayMicroseconds(15);
ti = micros() - t_inicio;


digitalWrite(Trig, LOW); 
TOF = pulseIn(Echo, HIGH);

tf = micros() - t_inicio;
Serial.print((tf + ti)/2);
Serial.print(",");
Serial.println(TOF);

delay(60);
}while(!Serial.available());
Serial.println(F("#Medida interrumpida por el usuario\n#\n#"));
delay(2000);
Serial.end();
}
