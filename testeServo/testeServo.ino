#include <Servo.h>

Servo meuServo;
const int PINO_SERVO = 13;

void setup() {
  meuServo.attach(PINO_SERVO);
  meuServo.write(0); // posição inicial
}

void loop() {
  meuServo.write(90);  // gira 90 graus
  delay(1000);         // espera 1s       // espera 1s
}