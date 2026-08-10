#include <Servo.h>

Servo meuServo, meuServo2, meuServo3;
const int PINO_SERVO = 13;
const int PINO_SERVO2 = 13;
const int PINO_SERVO3 = 13;

void setup() {
  meuServo.attach(PINO_SERVO);
  meuServo2.attach(PINO_SERVO2);
  meuServo3.attach(PINO_SERVO3);
  meuServo.write(0);
  meuServo.write2(0);
  meuServo.write3(0); // posição inicial
}

void loop() {
  meuServo.write(90);  // gira 90 graus
  delay(1000); 
  meuServo2.write(90);  // gira 90 graus
  delay(1000);
  meuServo3.write(90);  // gira 90 graus
  delay(1000);
  meuServo.write(0);
  meuServo2.write(0);
  meuServo3.write(0);  // gira 90 graus
  delay(1000);        // espera 1s       // espera 1s
}