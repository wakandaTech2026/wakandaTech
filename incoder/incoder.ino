// ======== Pinos do Motor (DRV8833) ========
const int IN1 = 5;   // PWM
const int IN2 = 4;

// ======== Pinos do Encoder ========
const int ENC_A = 3;
const int ENC_B = 2;

volatile long pulsos = 0;
volatile int direcao = 0;

void encoderISR() {
  bool A = digitalRead(ENC_A);
  bool B = digitalRead(ENC_B);

  if (A == B) {
    pulsos++;
    direcao = 1;
  } else {
    pulsos--;
    direcao = -1;
  }
}

void setup() {

  Serial.begin(115200);

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);

  pinMode(ENC_A, INPUT_PULLUP);
  pinMode(ENC_B, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(ENC_A), encoderISR, CHANGE);

  // Motor para frente
  analogWrite(IN1, 0);
  digitalWrite(IN2, LOW);
}

void loop() {

  static long ultimo = 0;

  if (millis() - ultimo > 500) {

    ultimo = millis();

    Serial.print("Pulsos: ");
    Serial.print(pulsos);

    Serial.print("   Direcao: ");

    if (direcao == 1)
      Serial.println("Horario");
    else if (direcao == -1)
      Serial.println("Anti-horario");
    else
      Serial.println("-");

  }

}
