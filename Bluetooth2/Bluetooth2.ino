#include <SoftwareSerial.h>

#define LED_PIN 13

SoftwareSerial SerialBT(18, 19);  // RX, TX
void setup() {
  pinMode(LED_PIN, OUTPUT);
  SerialBT.begin(38400);
  
  // Enviar nombre del dispositivo
  SerialBT.print("AT+NAME=ArduinoMega\r\n");
  
  // Asignar rol en esclavo
  SerialBT.print("AT+ROLE=0\r\n");
  
  // Configurar contraseña
  SerialBT.print("AT+PSWD=12345678\r\n");
  
  // Reiniciar el módulo
  SerialBT.print("AT+RESET\r\n");
  
  // Esperar un segundo antes de reiniciar
  delay(1000);
  
  // Reiniciar el Arduino
  resetFunc();
}

void loop() {
  digitalWrite(LED_PIN, HIGH);  // Encender el LED
  delay(5000);                 // Esperar 5 seguW);   // Apagar el LED
  delay(5000);                 // Esperar 5 segundos
}

// Función para reiniciar el Arduino
void resetFunc() {
  asm volatile ("  jmp 0");
}
ndos
  digitalWrite(LED_PIN, LO