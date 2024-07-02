#include <Wire.h>
#include <MPU6050.h>

MPU6050 mpu;

void setup() {
  Serial.begin(115200);
  Wire.begin();
  mpu.initialize();

  if (mpu.testConnection()) {
    Serial.println("MPU6050 conectado correctamente.");
  } else {
    Serial.println("Error al conectar el MPU6050.");
  }
}

void loop() {
  int16_t ax, ay, az;
  int16_t gx, gy, gz;
  
  // Leer los valores del sensor
  mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

  // Calcular la magnitud del vector de aceleración en el plano XY
  float ax_f = ax / 16384.0; // Convertir a g
  float ay_f = ay / 16384.0; // Convertir a g

  float gx_f = gx / 131.0; // Convertir a grados/segundo
  float gy_f = gy / 131.0; // Convertir a grados/segundo

  // Calcular la magnitud de la aceleración en el plano XY
  float magnitudeXY = sqrt(ax_f * ax_f + ay_f * ay_f);

  Serial.print("aX = "); Serial.print(ax_f);
  Serial.print(" | aY = "); Serial.print(ay_f);
  Serial.print(" | gX = "); Serial.print(gx_f);
  Serial.print(" | gY = "); Serial.print(gy_f);
  Serial.print(" | Magnitude XY = "); Serial.println(magnitudeXY);

  // Verificar si los valores corresponden a un círculo
  // Esto es un ejemplo simple, puedes mejorar el algoritmo según sea necesario
  if (magnitudeXY > 1.0 && abs(gx_f) > 20 && abs(gy_f) > 20) {
    Serial.println("Movimiento circular detectado");
  }

  delay(100);
}
