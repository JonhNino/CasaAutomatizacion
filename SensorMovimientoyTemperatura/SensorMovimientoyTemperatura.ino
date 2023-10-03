/*
  Proyecto: Medición de distancia, humedad y temperatura con sensor ultrasónico y sensor DHT
  Autor: [Tu nombre o información del autor]
  Fecha: [Fecha de creación o última modificación]
  Descripción: Este código utiliza un sensor ultrasónico para medir la distancia y un sensor DHT para medir la humedad y temperatura.
  Si la distancia es menor o igual a 10 cm o la temperatura es mayor a 24 grados Celsius, se activa un zumbador.
*/

#include <DHT.h>

// Definición de los pines
const int triggerPin = 2;
const int echoPin = 3;
const int buzzerPin = 4;
#define DHTPIN 5
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

// Declaración de funciones
long readUltrasonicDistance(int triggerPin, int echoPin);
void checkDistanceAndTemperature(int distance, float humidity, float temperatureCelsius, float temperatureFahrenheit);

void setup() {
  Serial.begin(9600);
  pinMode(buzzerPin, OUTPUT);
  dht.begin();
}

void loop() {
  // Medición de la distancia con el sensor ultrasónico
  long distance = 0.01723 * readUltrasonicDistance(triggerPin, echoPin);
  delay(1000);
  
  // Lectura de la humedad y temperatura con el sensor DHT
  float humidity = dht.readHumidity();
  float temperatureCelsius = dht.readTemperature();
  float temperatureFahrenheit = dht.readTemperature(true);

  // Verificación de errores en la lectura del sensor DHT
  if (isnan(humidity) || isnan(temperatureCelsius) || isnan(temperatureFahrenheit)) {
    Serial.println("Error en la lectura del sensor DHTxx");
    return;
  }

  Serial.print("Distancia: ");
  Serial.println(distance);
  Serial.print("Humedad: ");
  Serial.print(humidity);
  Serial.print(" %");
  Serial.print(" Temperatura: ");
  Serial.print(temperatureCelsius);
  Serial.print(" °C / ");
  Serial.print(temperatureFahrenheit);
  Serial.println(" °F");

  // Comprobación de la distancia y temperatura para activar el buzzer
  checkDistanceAndTemperature(distance, humidity, temperatureCelsius, temperatureFahrenheit);

  delay(1000);
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
void checkDistanceAndTemperature(int distance, float humidity, float temperatureCelsius, float temperatureFahrenheit) {
  if (distance <= 10) {
    digitalWrite(buzzerPin, HIGH);
  } else if (temperatureCelsius > 24) {
    digitalWrite(buzzerPin, HIGH);
  } else {
    digitalWrite(buzzerPin, LOW);
  }
}
