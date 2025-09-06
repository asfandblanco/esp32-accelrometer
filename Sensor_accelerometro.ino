#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_ADXL345_U.h>

int LedXmas = 4;
int LedXmenos = 17;
int LedYmas = 5;
int LedYmenos = 16;

Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified(12345);  // Corregido el nombre de la clase

void setup() {
  // Configuración inicial
  pinMode(LedXmas, OUTPUT);
  pinMode(LedXmenos, OUTPUT);
  pinMode(LedYmas, OUTPUT);
  pinMode(LedYmenos, OUTPUT);
  Serial.begin(9600);

  if (!accel.begin()) {
    Serial.println("El sensor no ha iniciado");
    while (1)
      ;  // Detener si falla el inicio del sensor
  }
  accel.setRange(ADXL345_RANGE_2_G);
}

void loop() {

  // Definir el evento
  sensors_event_t event;
  accel.getEvent(&event);  // Obtener los datos del acelerómetro

  float accelerometrox = event.acceleration.x;
  float accelerometroy = event.acceleration.y;
  float accelerometroz = event.acceleration.z;

  Serial.print("X: ");
  Serial.print(accelerometrox);
  Serial.print("  Y: ");
  Serial.print(accelerometroy);
  Serial.print("  Z: ");
  Serial.println(accelerometroz);
  delay(50);

  // Control del LED según la aceleración en el eje X
  if (event.acceleration.x < -6) {
    digitalWrite(LedXmas, HIGH);
  } else {
    digitalWrite(LedXmas, LOW);
  }

  if (event.acceleration.x > 6) {  // Ajuste para considerar aceleración negativa
    digitalWrite(LedXmenos, HIGH);
  } else {
    digitalWrite(LedXmenos, LOW);
  }

  // Control del LED según la aceleración en el eje Y
  if (event.acceleration.y < -6) {
    digitalWrite(LedYmas, HIGH);
  } else {
    digitalWrite(LedYmas, LOW);
  }

  if (event.acceleration.y > 6) {  // Ajuste para considerar aceleración negativa
    digitalWrite(LedYmenos, HIGH);
  } else {
    digitalWrite(LedYmenos, LOW);
  }
}