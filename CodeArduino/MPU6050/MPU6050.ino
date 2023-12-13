/*
Este código sirve para:

1. Calibrar el acelerómetro.
2. Medir tiempos con la fotocompuerta y una señal con el acelerómetro

  ############################
 ####### P I N E S###########
############################ 

# Aceleŕometro MPU6500 -----> Arduino Nano
  Vcc ------> 5V
  GND ------> GND
  SDA ------> A4 (Resistencia pull up de 1 kOhm)
  SCL ------> A5 (Resistencia pull up de 1 kOhm)

#Fotocompuerta

Naranja  ------> Vcc
Blanco   ------> GND
Verde    ------> D2 (si se quiere probar la fotocompuerta, también conectar a A0)
############################ 


 */

#include <basicMPU6050.h> 
#include <Wire.h>

//-- Input parameters:

// Gyro settings:
#define         LP_FILTER    0           // Low pass filter.                    Value from 0 to 6
#define         GYRO_SENS    0           // Gyro sensitivity.                   Value from 0 to 3
#define         ACCEL_RANGE  0       // Accelerometer sensitivity.          Value from 0 to 3
#define         ADDRESS_A0  LOW         // I2C address from state of A0 pin.   A0 -> GND : ADDRESS_A0 = LOW
                                        //                                     A0 -> 5v  : ADDRESS_A0 = HIGH


// Accelerometer offset:

constexpr int   AX_OFFSET = 0 ;       // Use these values to calibrate the accelerometer. The sensor should output 1.0g if held level. 
constexpr int   AY_OFFSET = 0;       // These values are unlikely to be zero.
constexpr int   AZ_OFFSET = 0;

// Output scale: 
constexpr float AX_SCALE = 1.00457;     // Multiplier for accelerometer outputs. Use this to calibrate the sensor. If unknown set to 1.
constexpr float AY_SCALE = 0.99170;
constexpr float AZ_SCALE = 0.98317;

constexpr float GX_SCALE = 0.99764;     // Multiplier to gyro outputs. Use this to calibrate the sensor. If unknown set to 1.
constexpr float GY_SCALE = 1.0;
constexpr float GZ_SCALE = 1.01037;

// Bias estimate:
#define         GYRO_BAND   35          // Standard deviation of the gyro signal. Gyro signals within this band (relative to the mean) are suppresed.   
#define         BIAS_COUNT  5000        // Samples of the mean of the gyro signal. Larger values provide better calibration but delay suppression response. 

//-- Set the template parameters:

basicMPU6050<LP_FILTER,  GYRO_SENS,  ACCEL_RANGE, ADDRESS_A0,
             AX_OFFSET,  AY_OFFSET,  AZ_OFFSET, 
             &AX_SCALE,  &AY_SCALE,  &AZ_SCALE,
             &GX_SCALE,  &GY_SCALE,  &GZ_SCALE,
             GYRO_BAND,  BIAS_COUNT 
            >imu;


//baudios
const long baudios = 2000000; 

//constante de calibración
float c = 0.0; //variable global de calibración
float Tcal = 0; //variable global de temperatura de calibración

//número de medida
uint32_t n = 1;


//Interrupciones
volatile int  n_intF = 0;
volatile int  n_intR = 0;
volatile unsigned long t_intF = 0;
volatile unsigned long t_intR = 0;
volatile bool banderaR = 0;
volatile bool banderaF = 0;
/// S E T U P ///////////////////////////////////////////////////////////////////////////
void setup() {
  
  Serial.begin(baudios);
  Serial.println("Programa para calibrar y medir");
  
// Acelerómetro
  TWBR = 12;  //http://www.gammon.com.au/i2c (setea frecuencia de I2C a 1000kHz)

  imu.setup();
  TWBR = 12;  //http://www.gammon.com.au/i2c (setea frecuencia de I2C a 1000kHz)
  // Initial calibration of gyro
  //imu.setBias();



  // Start console
}
/////FIN    S E T U P////////////////////


void loop() { 
Serial.print(F("\nEscriba:\n\n\\
      a para imprimir constantes de calibratio (CTRL + ENTER)\n\n\\
      c para calibrar el acelerómetro (CTRL + ENTER)\n\n\\
      i para ver ángulos del acelerómetro\n\n\\
      s para imprimir medidas sin calibrar (CTRL + ENTER)\n\n\\
      p para probar la fotocompuerta\n\n\\
      m para medir  (CTRL + ENTER)\n\n\\
      r para cambiar el rango del acelerómetro (2g ó 4g)\n\n\\
      g para informar el rango del acelerómetro\n\n\\
      f para cambiar el Filtro Digital Pasa Bajos\n\n"));


      char bufferEntrada;

      while(!Serial.available());
            if(Serial.available()) {
            bufferEntrada = Serial.read();
            Serial.end(); //apaga para vaciar el serial (no conozco otra forma menos rústica)
            Serial.begin(baudios);
            while(Serial.available());
             
            }
  
      switch(bufferEntrada){
                            case 'a':
                            imprime_calibratio(); break;
                            
                            case 'c':
                            calibratio(10000); break;

                            case 'i':
                            angulo_hermanos();break;  

                            case 'm':
                            mide_imprime_acel(c); break;
                            
                            case 's':
                            mide_imprime_acel(1.00); break;

                            case 'p':
                            pruebafotocompuerta(); break;

                            case 'r':
                            rango_acel(); break;

                            case 'g':
                            en_que_rango();break;

                            case 'f':
                            LowPassFilter(); break;

                            default:  
                            Serial.println(F("Error: ingreso incorrecto."));
                            break;
                            }                

}
//// FIN loop ////////////////////////////////////////////////////////////////////

//función para ver los ángulos.
void angulo_hermanos(){
do{
const uint16_t n = 1000;
int32_t axm_ac = 0;
int32_t aym_ac = 0;
int32_t azm_ac = 0;

//acumula

  for(int i = 0; i < n; i++){
        axm_ac = axm_ac + imu.rawAx();
        aym_ac = aym_ac + imu.rawAy();
        azm_ac = azm_ac + imu.rawAz();
      }   

//medias
float axm = (float)axm_ac / n;
float aym = (float)aym_ac / n;
float azm = (float)azm_ac / n;

float angulo_xy = atan(aym/axm) *180 / M_PI;
float angulo_xz = atan(azm/axm) *180 / M_PI;

Serial.print(F("XY = ")); Serial.print(angulo_xy); Serial.print(F(" °   ,   XZ = ")); Serial.print(angulo_xz); Serial.print(F(" °\n"));
}while(!Serial.available());
Serial.end();Serial.begin(baudios);


}


//rango acelerómetro
//preguntar rango del acelerómetro
void en_que_rango(void){
                  Wire.beginTransmission(0x68); //dirección acelerómetro
                  Wire.write(0x1C);     // registro configuración acelerómetro
                  Wire.endTransmission();                    
                  Wire.requestFrom(0x68,1);    // pide registro de control
                  byte registerData = Wire.read();           // lee el byte de control 
 
 bool AFS_SELbit3 = ( registerData & 0b00001000 );
 bool AFS_SELbit4 = ( registerData & 0b00010000 );

int AFS_SEL = AFS_SELbit3 + 2 * AFS_SELbit4;

Serial.print(F("Rango Acelerómetro:\n  0 = +-  2g\n  1 = +-  4g\n  2 = +-  8g\n  3 = +- 16g\n"));
Serial.print(F("\nAcelerómetro Configurado en (ver tabla)  ")); Serial.println(AFS_SEL);
}

//cambiar rango del acelerómetro
void rango_acel(void){

////////////////////////////////////////////////////////////////////
int AFS_SEL = 0;

Serial.print(F("Rango Acelerómetro:\n  0 = +-  2g\n  1 = +-  4g\n  2 = +-  8g\n  3 = +- 16g\n"));
while(!Serial.available());
            if(Serial.available()) {
            AFS_SEL = Serial.parseInt();
            Serial.end(); //apaga para vaciar el serial (no conozco otra forma menos rústica)
            Serial.begin(baudios);
            while(Serial.available());
           }

bool AFS_SELbit3  = AFS_SEL & 0b00000001;
bool AFS_SELbit4  = AFS_SEL & 0b00000010;

///////////////////////////////////////////////////////////////////
    Wire.beginTransmission(0x68); //dirección acelerómetro
    Wire.write(0x1C);     // registro configuración acelerómetro
    Wire.endTransmission();                    
    Wire.requestFrom(0x68,1);    // pide registro de control
    byte registerData = Wire.read();           // lee el byte de control 
    bitWrite(registerData, 3, AFS_SELbit3);
    bitWrite(registerData, 4, AFS_SELbit4);
    Wire.beginTransmission(0x68);  // Dirección chip
    Wire.write(0x1C);            // registro de control
    Wire.write(registerData);    // ponemos el byte con los bits 3 y 4 en 
    Wire.endTransmission();
    Serial.print(F("\nAcelerómetro Configurado en (ver tabla)  ")); Serial.println(AFS_SEL);

}

//Filtro low pass
//cambiar rango del acelerómetro
void LowPassFilter(void){
int DLPF = 0;

Serial.print(F("Filtro pasa bajos:\n  0 = 260 Hz\n  1 = 184 Hz\n  2 = 94Hz\n  3 = 44 Hz\n  4 = 21 Hz\n  5 = 10 Hz\n  6 = 5 Hz\n"));
while(!Serial.available());
            if(Serial.available()) {
            DLPF = Serial.parseInt();
            Serial.end(); //apaga para vaciar el serial (no conozco otra forma menos rústica)
            Serial.begin(baudios);
            while(Serial.available());
           }

bool DLPFbit0  = DLPF & 0b00000001;
bool DLPFbit1  = DLPF & 0b00000010;
bool DLPFbit2  = DLPF & 0b00000100;


Wire.beginTransmission(0x68); //dirección acelerómetro
Wire.write(0x1A);     // registro configuración DLPF
  Wire.endTransmission();                    
  Wire.requestFrom(0x68,1);    // pide registro de control
  byte registerData = Wire.read();           // lee el byte de control 
  bitWrite(registerData, 0, DLPFbit0);
  bitWrite(registerData, 1, DLPFbit1);
  bitWrite(registerData, 2, DLPFbit2);
  Wire.beginTransmission(0x68);  // Dirección chip
  Wire.write(0x1A);            // registro de control
  Wire.write(registerData);    // ponemos el byte con los bits 4 y 5 en 1
  Wire.endTransmission();
  Serial.print(F("\nDigital Low Pass Filter (ver tabla) configurado en "));Serial.println(DLPF);
  
}



// Fotocompuerta
//interrupción RISING
void fc_negra_R(void){
t_intR = micros(); 
detachInterrupt(0);
n_intR++;
banderaR = 1;
EIFR = bit(INTF0); attachInterrupt(0, fc_negra_F, FALLING);
}

//interrupción FALLING
void fc_negra_F(void){
t_intF = micros(); 
detachInterrupt(0);
n_intF++;
banderaF = 1;
EIFR = bit(INTF0); attachInterrupt(0, fc_negra_R, RISING);
}


//fotocompuerta muestra valores analógicos
void pruebafotocompuerta(void){
                        pinMode(A0, INPUT);

          Serial.println(F("Valores de referencia: \n\n < 100 para la fotocompuerta sin obstruir \n\n > 100 para fotocompuerta tapada \n\n \\
          Para interrumpir, presionar cualquier tecla."));


          Serial.println(F("Comenzando en 6...")); delay(2000);
          Serial.println(F("4...")); delay(2000); Serial.println(F("2..."));delay(2000); 

      do{Serial.println(analogRead(A0));}while(!Serial.available());
      delay(1000);
 
  Serial.print(F("#\n#\n#\n#\n#\n#\nMedida interrumpida por usuario\n"));
 
}




//medida con todos
void mide_imprime_acel(float c_cal){

//hacemos cero las variables
  n_intF = 0;
  n_intR = 0;

//fototompuerta
pinMode(2, INPUT);
attachInterrupt(0, fc_negra_R, RISING);

Serial.print(F("################################# M e d i d a ###########################################################\n"));
Serial.print(F("t,ax,ay,az,n_intR,t_intR,n_intF,t_intF\n"));
unsigned long tf1 = micros();


do{
  
    
    float t = (float)(micros() - tf1) / 1000000.0000;

  
    //imu.updateBias();
    float ax =  (float)imu.rawAx() * c_cal;
    float ay =  (float)imu.rawAy() * c_cal; 
    float az =  (float)imu.rawAz() * c_cal;
   
    Serial.print(t,4);
    Serial.print(",");
    Serial.print(ax);
    Serial.print( "," );
    Serial.print(ay);
    Serial.print( "," );
    Serial.print(az);

    Serial.print(",");
    
        if(banderaR == 1){    
          Serial.print(n_intR);
          Serial.print(",");
          Serial.print(t_intR - tf1);
          Serial.print(",");
          banderaR = 0;
        }else{Serial.print(F(",,"));}
        
        if(banderaF == 1){    
          Serial.print(n_intF);
          Serial.print(",");
          Serial.print(t_intF - tf1);
          banderaF = 0;
        }else{Serial.print(F(","));}


Serial.print("\n");
n++;
}while(!Serial.available());


  delay(1000);

  
  unsigned long tf2 = micros();

  Serial.print("###################################################################\n#  F_muestreo = ");
  Serial.print (n * 1000000.00 / (tf2 - tf1));
  Serial.print(" Hz\n#\n#  Tiempo total de la medida: "); Serial.print( (tf2 - tf1)/1000000.00 ); Serial.print(" s");
  Serial.print("\n#\n#  Cantidad de medidas N = "); Serial.print(n);
  Serial.print("\n#\n#  c_calibración = "); Serial.print(c_cal,16);
  Serial.print(F("\n#\n#  ")); en_que_rango();
  Serial.print("\n###################################################################");
  delay(2000);
  Serial.end(); Serial.begin(baudios);
  n = 1;


}




//función de calibración: calcula una c y da la temperatura de calibración.
void calibratio(int n){ 

int32_t axm_ac = 0;
int32_t aym_ac = 0;
int32_t azm_ac = 0;

//acumula
uint32_t tant = 0;
Serial.print(F("Calibrando.\n"));

       for(int i = 0; i < n; i++){
                                  axm_ac = axm_ac + imu.rawAx();
                                  aym_ac = aym_ac + imu.rawAy();
                                  azm_ac = azm_ac + imu.rawAz();
                                  if(millis() > (tant + 1000)){ Serial.print(F("          .\n")); tant = millis();}
                                 }   

//medias
float axm = (float)axm_ac / n;
float aym = (float)aym_ac / n;
float azm = (float)azm_ac / n;

c = 9.7931 / sqrt(axm * axm + aym * aym + azm * azm);

Serial.print("c_cal = "); Serial.println(c,16);
Serial.print("T_cal = "); Serial.println(Tcal);

}


void imprime_calibratio(void){
Serial.print("c = "); Serial.println(c,16);
Serial.print("Tcalc = "); Serial.println(Tcal);
delay(2000);
}