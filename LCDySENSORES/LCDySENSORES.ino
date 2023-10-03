#include <Servo.h>
#include <DHT.h>
#include <LiquidCrystal.h>

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

struct LED {
  int pin;
  char onCommand;
  char offCommand;
};

struct ServoMotor {
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

int rs = 22;
int e = 24;
int d4 = 26;
int d5 = 28;
int d6 = 30;
int d7 = 32;
LiquidCrystal lcd(rs, e, d4, d5, d6, d7);

int contador = 0;

void setup() {
  Serial.begin(38400);
  pinMode(buzzerPin, OUTPUT);
  dht.begin();

  for (int i = 0; i < NUMBER_OF_LEDS; i++) {
    pinMode(leds[i].pin, OUTPUT);
  }

  for (int i = 0; i < NUMBER_OF_SERVOS; i++) {
    servos[i].servo.attach(servos[i].pin);
    pinMode(servos[i].redLedPin, OUTPUT);
    pinMode(servos[i].greenLedPin, OUTPUT);
  }

  lcd.begin(16, 2);
}

void mostrarInformacionSensoresMovimiento(long distance1, long distance2) {
  Serial.print("Distancia Sensor 1: ");
  Serial.println(distance1);
  Serial.print("Distancia Sensor 2: ");
  Serial.println(distance2);

  lcd.setCursor(0, 0);
  lcd.print("Sensor 1: ");
  lcd.print(distance1);
  lcd.print("cm");

  lcd.setCursor(0, 1);
  lcd.print("Sensor 2: ");
  lcd.print(distance2);
  lcd.print("cm");
}

void mostrarInformacionHumedadTemperatura(float humidity, float temperatureCelsius) {
  Serial.print("Humedad: ");
  Serial.print(humidity);
  Serial.print(" %");
  Serial.print(" Temperatura: ");
  Serial.print(temperatureCelsius);
  Serial.println(" °C");

  lcd.setCursor(0, 0);
  lcd.print("Humedad: ");
  lcd.print(humidity);
  lcd.print(" %");

  lcd.setCursor(0, 1);
  lcd.print("Temp: ");
  lcd.print(temperatureCelsius);
  lcd.print("C");
}

void loop() {
  long distance1 = 0.01723 * readUltrasonicDistance(triggerPin1, echoPin1);
  long distance2 = 0.01723 * readUltrasonicDistance(triggerPin2, echoPin2);
  delay(1000);

  float humidity = dht.readHumidity();
  float temperatureCelsius = dht.readTemperature();

  if (isnan(humidity) || isnan(temperatureCelsius)) {
    Serial.println("Error en la lectura del sensor DHT11");
    return;
  }

  contador++;

  if (contador % 2 == 0) {
    mostrarInformacionSensoresMovimiento(distance1, distance2);
  } else {
    mostrarInformacionHumedadTemperatura(humidity, temperatureCelsius);
  }

  checkDistanceAndTemperature(distance1, distance2, humidity, temperatureCelsius);

  delay(2000);
  lcd.clear();

  if (Serial.available()) {
    char valor = Serial.read();

    for (int i = 0; i < NUMBER_OF_LEDS; i++) {
      if (valor == leds[i].onCommand) {
        controlLED(leds[i].pin, HIGH);
      } else if (valor == leds[i].offCommand) {
        controlLED(leds[i].pin, LOW);
      }
    }

    for (int i = 0; i < NUMBER_OF_SERVOS; i++) {
      if (valor == servos[i].openCommand) {
        moverServo(&servos[i], 180);
      } else if (valor == servos[i].closeCommand) {
        moverServo(&servos[i], 0);
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

void checkDistanceAndTemperature(int distance1, int distance2, float humidity, float temperatureCelsius) {
  if (distance1 <= 10 || distance2 <= 10 || temperatureCelsius > 24) {
    digitalWrite(buzzerPin, HIGH);
  } else {
    digitalWrite(buzzerPin, LOW);
  }
}
