// Ejemplo de prueba para ver el funcionamiento del DHT11
// Escrito ORIGINAL por ladyada, public domain
//Traducido por Konrad Peschka @konredus

//incluimos la libreria DHT
#include <DHT.h>

//este es el pin donde vamos a conectar el sensor (data)
#define DHTPIN 2     

//La misma libreria se puede utilizar para los otros 2 sensores
//que existen en el mercado, para habilitar el sensor que estas
//usando vos, simplemente comentar y descomentar segun lo necesites.

#define DHTTYPE DHT11   // DHT 11
//#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
//#define DHTTYPE DHT21   // DHT 21 (AM2301)

//se inicializa la CLASE dht, que va a ser el "nombre"
//que tendra de ahora en adelante nuestro sensor.
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  Serial.println("DHTxx test!");
  
  //funcion que inicializa el sensor
  dht.begin();
}

void loop() {
  //espero 1 segundos para hacer una medicion
  //esto es por que el sensor no puede medir mas rapido
  delay(1000);

  // leo la humedad y lo cargo en una variable flotante
  float h = dht.readHumidity();
  
  // leo la temperatura y lo cargo en una variable flotante
  float t = dht.readTemperature();
  
  // en caso de necesitar hacer la lectura en Fahrenheit 
  //debo colocar dentro (true)
  float f = dht.readTemperature(true);

  // Checkeo si se leyeron correctamente los valores 
  // en caso de que alguno llego mal, mando mensaje de error
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println("Error en al lectura del sensor DHTxx");
    return;
  }

  Serial.print("Hum: ");
  Serial.print(h);
  Serial.print("  ");
  Serial.print("Temp: ");
  Serial.print(t);
  Serial.print(" *C ");
  Serial.print(" / ");
  Serial.print(f);
  Serial.println(" *F");
}
