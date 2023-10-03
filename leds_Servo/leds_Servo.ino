#include <Servo.h>

#define NUMBER_OF_LEDS 6
#define NUMBER_OF_SERVOS 2

struct LED{
  int pin;
  char onCommand;
  char offCommand;
};

struct ServoMotor{
  Servo servo;
  int pin;
  int angle;
  int redLedPin;
  int greenLedPin;
  char openCommand;
  char closeCommand;
};

struct LED leds[NUMBER_OF_LEDS] = {
  {2, 'A', 'B'},
  {3, 'C', 'D'},
  {4, 'E', 'F'},
  {5, 'G', 'H'},
  {6, 'I', 'J'},
  {7, 'K', 'L'}
};

struct ServoMotor servos[NUMBER_OF_SERVOS] = {
  {Servo(), 9, 0, 10, 11, '1', '2'},
  {Servo(), 23, 0, 25, 27, '3', '4'}
};

void controlLED(int ledPin, bool state);
void moverServo(struct ServoMotor *servoMotor, int targetAngle);

void setup() {
  Serial.begin(38400);
  
  for(int i = 0; i < NUMBER_OF_LEDS; i++){
    pinMode(leds[i].pin, OUTPUT);
  }

  for(int i = 0; i < NUMBER_OF_SERVOS; i++){
    servos[i].servo.attach(servos[i].pin);
    pinMode(servos[i].redLedPin, OUTPUT);
    pinMode(servos[i].greenLedPin, OUTPUT);
  }
}

void loop() {
  if (Serial.available()) {
    char valor = Serial.read();  // Lee el dato entrante vía Bluetooth

    // Control de los LEDs
    for(int i = 0; i < NUMBER_OF_LEDS; i++){
      if(valor == leds[i].onCommand){
        controlLED(leds[i].pin, HIGH);
      } else if(valor == leds[i].offCommand){
        controlLED(leds[i].pin, LOW);
      }
    }

    // Control de los servomotores
    for(int i = 0; i < NUMBER_OF_SERVOS; i++){
      if(valor == servos[i].openCommand){
        moverServo(&servos[i], 180);  // Mover el servo a 180 grados
      } else if(valor == servos[i].closeCommand){
        moverServo(&servos[i], 0);    // Mover el servo a 0 grados
      }
    }
  }
}

void controlLED(int ledPin, bool state) {
  digitalWrite(ledPin, state);
}

void moverServo(struct ServoMotor *servoMotor, int targetAngle) {
  int increment = targetAngle < servoMotor->angle ? -1 : 1;
  
  while (servoMotor->angle != targetAngle) {
    servoMotor->angle += increment;       
    servoMotor->servo.write(servoMotor->angle);
    
    controlLED(servoMotor->redLedPin, servoMotor->angle == 0);
    controlLED(servoMotor->greenLedPin, servoMotor->angle == 180);
    
    delay(15); 
  }
}
