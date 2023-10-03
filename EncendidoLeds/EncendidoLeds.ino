// Variables asociadas a los seis LEDs que se van a controlar
int led_1 = 2;
int led_2 = 3;
int led_3 = 4;
int led_4 = 5;
int led_5 = 6;
int led_6 = 7;

char valor;  // Variable para indicar que llega una orden

void setup() {
  pinMode(led_1, OUTPUT);
  pinMode(led_2, OUTPUT);
  pinMode(led_3, OUTPUT);
  pinMode(led_4, OUTPUT);
  pinMode(led_5, OUTPUT);
  pinMode(led_6, OUTPUT);
  Serial.begin(38400);
}

void controlarLED(char comando) {
  switch (comando) {
    case 'A':
      digitalWrite(led_1, HIGH);  // Enciende el LED 1
      break;
    case 'B':
      digitalWrite(led_1, LOW);   // Apaga el LED 1
      break;
    case 'C':
      digitalWrite(led_2, HIGH);  // Enciende el LED 2
      break;
    case 'D':
      digitalWrite(led_2, LOW);   // Apaga el LED 2
      break;
    case 'E':
      digitalWrite(led_3, HIGH);  // Enciende el LED 3
      break;
    case 'F':
      digitalWrite(led_3, LOW);   // Apaga el LED 3
      break;
    case 'G':
      digitalWrite(led_4, HIGH);  // Enciende el LED 4
      break;
    case 'H':
      digitalWrite(led_4, LOW);   // Apaga el LED 4
      break;
    case 'N':
      digitalWrite(led_5, HIGH);  // Enciende el LED 5
      break;
    case 'J':
      digitalWrite(led_5, LOW);   // Apaga el LED 5
      break;
    case 'K':
      digitalWrite(led_6, HIGH);  // Enciende el LED 6
      break;
    case 'L':
      digitalWrite(led_6, LOW);   // Apaga el LED 6
      break;
    default:
      break;
  }
}

void loop() {
  if (Serial.available()) {  // Si el puerto serie (Bluetooth) está disponible
    valor = Serial.read();  // Lee el dato entrante vía Bluetooth

    // Control de los LEDs usando la función controlarLED()
    controlarLED(valor);
  }
}
