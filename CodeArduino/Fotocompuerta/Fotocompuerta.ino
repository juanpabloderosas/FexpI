/*
* Conectando:
* - Conectar el diodo y el fototransistor a GND y 5V (poner las resistencias para no quemar nada!
* - Conectar la salida del comparador (fototransistor) al pin D2. Puede estar puenteada a A0 para
*   el testeo. 	
*
*/



//pines interrupción
const byte Pino = 2; 
byte flag = 0;

//variables para las medidas de tiempo.
volatile unsigned long t = 0;
volatile unsigned long t_ant = 0;
unsigned long t1 = 0;
int n =1;
int tirada = 0;

void setup() {
  Serial.begin(9600);           //  setup serial
  pinMode(Pino, INPUT_PULLUP);

  //Configuramos interrupción en el pin Pino (D2 según la línea 12)
  //La configuramos como CHANGE = de abajo a arriba y de arriba a abajo,
  //lo que quiere decir que va a marcar un tiempo cuando pase de 
  //oscuridad a luz y de luz a oscuridad. Puede ser configurada como RISING o FALLING, 
  //(lo que va a detectar un flanco en lugar de dos)
  attachInterrupt(digitalPinToInterrupt(Pino),inputISR1, CHANGE); 
  Serial.print("Tirada");
  Serial.print(";");
  Serial.print("Cinta");
  Serial.print(";");
  Serial.println("t");
}

void loop() {
  //int rawTemp;
  if(flag == 1){
    if((t - t_ant) >= (1000000) ){tirada = tirada +1; n = 1;};
    if(n == 1){t1 = t;};
    Serial.print(tirada);
    Serial.print(";");
    Serial.print(n);
    Serial.print(";");
    Serial.println(t-t1);
    t_ant = t;
    flag = 0;
    n = n+1;
    
    }
    
    
}
/*INTERRUPCIonN*/
void inputISR1() {
  t_ant = t;
  t = micros();
  flag = 1;
 }
