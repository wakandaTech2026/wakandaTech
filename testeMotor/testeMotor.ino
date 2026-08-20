int portaMotor = 8;
int portaMotor1 = 9;
int portaMotor2 = 10;
int portaMotor3 = 11;

void setup() {
  // put your setup code here, to run once:
  pinMode(portaMotor, OUTPUT);
  pinMode(portaMotor1, OUTPUT);
  pinMode(portaMotor2, OUTPUT);
  pinMode(portaMotor3, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
    analogWrite(portaMotor, 0);
    analogWrite(portaMotor1, 128);
    analogWrite(portaMotor2, 128);
    analogWrite(portaMotor3, 0);
    delay(500);

    analogWrite(portaMotor, 128);
    analogWrite(portaMotor1, 0);
    analogWrite(portaMotor2, 0);
    analogWrite(portaMotor3, 128);
    delay(500);
  
}
