#include <SoftwareSerial.h>

SoftwareSerial bluetoothSerial(19, 18);  // RX, TX

void setup() {
  Serial.begin(9600);                 // Inicia la comunicación serial del Arduino Mega
  bluetoothSerial.begin(38400);       // Inicia la comunicación serial con el módulo Bluetooth a 38400 baudios

  configureBluetooth();               // Configura los parámetros del módulo Bluetooth
}

void loop() {
  // Tu código principal aquí
}

void configureBluetooth() {
  delay(1000);  // Espera inicial para asegurar que el módulo Bluetooth esté listo

  // Configura el módulo Bluetooth con los comandos AT
  bluetoothSerial.print("AT");                      // Comando AT para verificar la comunicación
  waitForResponse("OK");

  bluetoothSerial.print("AT+NAME=HC-05");             // Configura el nombre del dispositivo Bluetooth como "HC-05"
  waitForResponse("OK");

  bluetoothSerial.print("AT+PIN=12345678");           // Configura el PIN de acceso del dispositivo Bluetooth como "12345678"
  waitForResponse("OK");

  bluetoothSerial.print("AT+UART=9600,0,0");         // Configura la velocidad de transmisión a 9600 baudios
  waitForResponse("OK");

  bluetoothSerial.print("AT+ROLE=1");                // Configura el módulo Bluetooth en modo maestro
  waitForResponse("OK");

  bluetoothSerial.print("AT+CMODE=0");               // Configura el módulo Bluetooth en modo de conexión automática
  waitForResponse("OK");

  bluetoothSerial.print("AT+RESET");                 // Reinicia el módulo Bluetooth para aplicar los cambios
  waitForResponse("OK");

  Serial.println("Configuración del módulo Bluetooth completada.");
}

void waitForResponse(const char* response) {
  char buffer[100];
  memset(buffer, 0, sizeof(buffer));
  int bufferIndex = 0;

  unsigned long timeout = millis() + 3000;  // Espera 3 segundos para recibir la respuesta

  while (millis() < timeout) {
    if (bluetoothSerial.available()) {
      char c = bluetoothSerial.read();
      buffer[bufferIndex++] = c;

      if (strstr(buffer, response)) {
        Serial.println(buffer);
        return;
      }
    }
  }

  Serial.println("Timeout: No se recibió la respuesta esperada.");
}
