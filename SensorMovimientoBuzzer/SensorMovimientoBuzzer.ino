const int triggerPin = 2;
const int echoPin = 3;
const int buzzerPin = 4;

void setup()
{
  Serial.begin(9600); // Inicializa la comunicación serial
  pinMode(buzzerPin, OUTPUT); // Configura el pin del buzzer como salida
}

void loop()
{
  long distancia = 0.01723 * readUltrasonicDistance(triggerPin, echoPin);

  Serial.print("Distancia=");
  Serial.println(distancia);

  if (distancia <= 10) {
    digitalWrite(buzzerPin, HIGH); // Activa el buzzer si la distancia es menor o igual a 10 cm
  } else {
    digitalWrite(buzzerPin, LOW); // Desactiva el buzzer si la distancia es mayor a 10 cm
  }

  delay(3000); // Retraso de 3 segundos (3000 milisegundos)
}

long readUltrasonicDistance(int triggerPin, int echoPin)
{
  pinMode(triggerPin, OUTPUT);
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  pinMode(echoPin, INPUT);
  return pulseIn(echoPin, HIGH);
}
