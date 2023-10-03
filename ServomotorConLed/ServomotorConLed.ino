#include <Servo.h>

const int servoPin = 9;     // Pin del servomotor
const int redLedPin = 10;   // Pin del LED rojo
const int greenLedPin = 11; // Pin del LED verde

Servo servo;
int angle = 0;              // Ángulo inicial del servomotor
int delayTime = 3000;       // Tiempo de espera en milisegundos

void setup() {
  servo.attach(servoPin);
  pinMode(redLedPin, OUTPUT);
  pinMode(greenLedPin, OUTPUT);
}

void loop() {
  servo.write(angle);  // Mover el servomotor al ángulo actual
  
  // Encender el LED rojo cuando el servomotor esté en la posición 0
  if (angle == 0) {
    digitalWrite(redLedPin, HIGH);
    digitalWrite(greenLedPin, LOW);
  }
  // Encender el LED verde cuando el servomotor esté en la posición de 180 grados
  else if (angle == 180) {
    digitalWrite(redLedPin, LOW);
    digitalWrite(greenLedPin, HIGH);
  }
  // Apagar ambos LEDs en cualquier otro ángulo
  else {
    digitalWrite(redLedPin, LOW);
    digitalWrite(greenLedPin, LOW);
  }
  
  // Incrementar o decrementar el ángulo en 1 grado
  if (angle == 0) {
    angle = 180;
  } else {
    angle = 0;
  }
  
  delay(delayTime);  // Esperar el tiempo especificado
  
  // Cambiar el tiempo de espera para la siguiente transición
  if (delayTime == 3000) {
    delayTime = 3000; // Mantener el tiempo de espera en 3 segundos
  } else {
    delayTime = 3000; // Cambiar el tiempo de espera a 3 segundos si se desea una pausa adicional entre transiciones
  }
}
