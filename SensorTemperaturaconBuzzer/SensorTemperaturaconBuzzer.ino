#include <DHT.h>

// Escrito ORIGINAL por ladyada, public domain
// Traducido por Konrad Peschka @konredus
// Incluimos la libreria DHT
#include <DHT.h>

// Este es el pin donde vamos a conectar el sensor (data)
#define DHTPIN 2

// La misma libreria se puede utilizar para los otros 2 sensores
// que existen en el mercado, para habilitar el sensor que estás
// usando tú, simplemente comenta y descomenta según lo necesites.
#define DHTTYPE DHT11 // DHT 11
//#define DHTTYPE DHT22 // DHT 22 (AM2302), AM2321
//#define DHTTYPE DHT21 // DHT 21 (AM2301)

// Se inicializa la CLASE DHT, que va a ser el "nombre"
// que tendrá de ahora en adelante nuestro sensor.
DHT dht(DHTPIN, DHTTYPE);

// Pin del zumbador
#define BUZZER_PIN 3

void setup() {
  Serial.begin(9600);
  Serial.println("DHTxx test!");

  // Función que inicializa el sensor
  dht.begin();

  // Configuración del zumbador
  pinMode(BUZZER_PIN, OUTPUT);
}

void loop() {
  // Espero 1 segundo para hacer una medición
  // Esto es porque el sensor no puede medir más rápido
  delay(1000);

  // Leo la humedad y lo guardo en una variable flotante
  float h = dht.readHumidity();

  // Leo la temperatura y lo guardo en una variable flotante
  float t = dht.readTemperature();

  // En caso de necesitar hacer la lectura en Fahrenheit
  // Debo colocar dentro (true)
  float f = dht.readTemperature(true);

  // Chequeo si se leyeron correctamente los valores
  // En caso de que alguno llegó mal, mando mensaje de error
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println("Error en la lectura del sensor DHTxx");
    return;
  }

  Serial.print("Hum: ");
  Serial.print(h);
  Serial.print(" ");
  Serial.print("Temp: ");
  Serial.print(t);
  Serial.print(" *C ");
  Serial.print(" / ");
  Serial.print(f);
  Serial.println(" *F");

  // Activar zumbador si la temperatura es mayor a 30 grados Celsius
  if (t > 24) {
    digitalWrite(BUZZER_PIN, HIGH);
  } else {
    digitalWrite(BUZZER_PIN, LOW);
  }
}
