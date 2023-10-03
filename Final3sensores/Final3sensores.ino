#include <Servo.h>
#include <DHT.h>
// Definición de los pines para sensor ultrasonico y DHT
const int triggerPin1 = 29;
const int echoPin1 = 31;
const int buzzerPin = 33;
const int triggerPin2 = 35;
const int echoPin2 = 37;
#define DHTPIN 39
#define DHTTYPE DHT11
#define NUMBER_OF_LEDS 6
#define NUMBER_OF_SERVOS 2

DHT dht(DHTPIN, DHTTYPE);

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
// Declaración de funciones
long readUltrasonicDistance(int triggerPin1, int echoPin1);
long readUltrasonicDistance(int triggerPin2, int echoPin2);
void checkDistanceAndTemperature(int distance, float humidity, float temperatureCelsius);
void controlLED(int ledPin, bool state);
void moverServo(struct ServoMotor *servoMotor, int targetAngle);

void setup() {
  Serial.begin(38400);
  pinMode(buzzerPin, OUTPUT);
  dht.begin();

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

  // Medición de la distancia con el sensor ultrasónico
  long distance1 = 0.01723 * readUltrasonicDistance(triggerPin1, echoPin1);
  long distance2 = 0.01723 * readUltrasonicDistance(triggerPin2, echoPin2);
  delay(1000);

  // Lectura de la humedad y temperatura con el sensor DHT
  float humidity = dht.readHumidity();
  float temperatureCelsius = dht.readTemperature();

  // Verificación de errores en la lectura del sensor DHT
  if (isnan(humidity) || isnan(temperatureCelsius)) {
    Serial.println("Error en la lectura del sensor DHTxx");
    return;
  }

  Serial.print("Distancia Sensor 1: ");
  Serial.println(distance1);
  Serial.print("Distancia Sensor 2: ");
  Serial.println(distance2);
  Serial.print("Humedad: ");
  Serial.print(humidity);
  Serial.print(" %");
  Serial.print(" Temperatura: ");
  Serial.print(temperatureCelsius);
  Serial.println(" °C");

  // Comprobación de la distancia y temperatura para activar el buzzer
  checkDistanceAndTemperature(distance1, distance2, humidity, temperatureCelsius);

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

// Función para medir la distancia con el sensor ultrasónico
long readUltrasonicDistance(int triggerPin, int echoPin) {
  pinMode(triggerPin, OUTPUT);
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  pinMode(echoPin, INPUT);
  return pulseIn(echoPin, HIGH);
}

// Función para verificar la distancia y temperatura y activar el buzzer según las condiciones
void checkDistanceAndTemperature(int distance1, int distance2,float humidity, float temperatureCelsius) {
  if (distance1 <= 10 ||distance2 <= 10 || temperatureCelsius > 24) {
    digitalWrite(buzzerPin, HIGH);
  } else {
    digitalWrite(buzzerPin, LOW);
  }
}
