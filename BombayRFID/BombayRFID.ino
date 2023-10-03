#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>
#define RST_PIN         9        
#define SS_PIN          10 
Servo myServo;
Servo mySecondServo; // Segundo servo
MFRC522 mfrc522(SS_PIN, RST_PIN);  
byte LecturaUID[4];
byte Usuario1[4] = {0xD9, 0xD2, 0x0D, 0xE5}; // tarjeta blanca
byte Usuario2[4] = {0x2C, 0xD3, 0x64, 0x17}; // llavero azul

void setup() {
  pinMode(2,OUTPUT);
  pinMode(3,OUTPUT);
  myServo.attach(5);
  mySecondServo.attach(6); // Conectar el segundo servo al pin 6
  onOffLeds();
  Serial.begin(9600);  
  SPI.begin();
  mfrc522.PCD_Init(); 
  Serial.println("listo"); 
}

void loop() {
 if ( ! mfrc522.PICC_IsNewCardPresent())
   return;
  if ( ! mfrc522.PICC_ReadCardSerial()) 
    return;
 Serial.println("Respuesta: ");
 onOffLeds();
  for(byte i=0;i<mfrc522.uid.size ;i++){
    if(mfrc522.uid.uidByte[i]<0x10){
      Serial.print(" 0");
      }
    else{
      Serial.print(" ");
      }
    Serial.print(mfrc522.uid.uidByte[i],HEX);
    LecturaUID[i] = mfrc522.uid.uidByte[i];
 }
 
  Serial.print("\t");
  if(comparaUID(LecturaUID , Usuario1)){
    Serial.println("Acceso permitido, bienvenido");
    abrirPuerta();
    delay(2000);
    cerrarPuerta();
    }
  else if(comparaUID(LecturaUID , Usuario2)){
      Serial.println("Accedo denegado, lo siento no tiene permitido ingresar");
    }
  mfrc522.PICC_HaltA();
}
void onOffLeds(){
  digitalWrite(2,HIGH);
  digitalWrite(3,HIGH);
  delay(100);
  digitalWrite(2,LOW);
  digitalWrite(3,LOW);
  delay(100);
  digitalWrite(2,HIGH);
  digitalWrite(3,HIGH);
  delay(100);
  digitalWrite(2,LOW);
  digitalWrite(3,LOW);
  }
void cerrarPuerta(){
   int angulo=0;
   do{
     digitalWrite(3,HIGH);
     digitalWrite(2,LOW);
     angulo = angulo+1;
     myServo.write(angulo);
     mySecondServo.write(angulo); // Mover el segundo servo
     delay(50);
    }while(angulo<90);
  digitalWrite(3,LOW);
  digitalWrite(2,LOW);
}
void abrirPuerta(){
   int angulo=90;
   do{
     digitalWrite(2,HIGH);
     digitalWrite(3,LOW);
     angulo = angulo-1;
     myServo.write(angulo);
     mySecondServo.write(angulo); // Mover el segundo servo
     delay(50);
    }while(angulo>0);
}
boolean comparaUID(byte lectura[],byte usuario[]){
  for(byte i=0; i < mfrc522.uid.size; i++){
    if(lectura[i] != usuario[i])
    return(false);
  }
  return(true);
}
