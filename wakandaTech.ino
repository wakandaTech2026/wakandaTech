int portaMotor = 8;
int portaMotor1 = 9;
int portaMotor2 = 10;
int portaMotor3 = 11;

int sEM = 24;  //sensor Esquerda
int sE = 26;
int sC = 28;
int sD = 30;
int sDM = 32; //sensor direita*/

int eSEM;
int eSE;
int eSC;
int eSD;
int eSDM;         //variável utilizada armazenar o estado do sensor


int trigPin = 6;
int echoPin = 7;
long duration, cm;

int kP = 20;
int erro;
int velBase = 100;
int correcao;
 
void setup() {
  Serial.begin (9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  pinMode(portaMotor, OUTPUT);
  pinMode(portaMotor1, OUTPUT);
  pinMode(portaMotor2, OUTPUT);
  pinMode(portaMotor3, OUTPUT);

  pinMode(sEM, INPUT);  //definindo o pino do sensor como entrada
  pinMode(sE, INPUT);
  pinMode(sC, INPUT);  //definindo o pino do sensor como entrada
  pinMode(sD, INPUT);
  pinMode(sDM, INPUT);

}
 
void loop() {
/*
  //motor e sensor de distancia
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  pinMode(echoPin, INPUT);
  duration = pulseIn(echoPin, HIGH);
 
  cm = (duration/2) / 29.1;
  
  Serial.print("in, ");
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();
  
  if(cm<=15){
    analogWrite(portaMotor, 0);
    analogWrite(portaMotor1, 0);
    analogWrite(portaMotor2, 0);
    analogWrite(portaMotor3, 0);
    delay(3000);
  }
  else{
    analogWrite(portaMotor, 128);
    analogWrite(portaMotor1, 0);
    analogWrite(portaMotor2, 0);
    analogWrite(portaMotor3, 128);
  }
  */

// motor e sensor de linha
  eSEM = digitalRead(sEM);  //lê o estado do sensor (alto = inativo, baixo = ativo)
  eSE = digitalRead(sE);
  eSC = digitalRead(sC);  //lê o estado do sensor (alto = inativo, baixo = ativo)
  eSD = digitalRead(sD);
  eSDM = digitalRead(sDM);

  //0 é linha

  //verificando se o sensor detectou algum objeto ou não
  
  if (eSEM == 0) {
    erro = -2;
  }
  else if (eSE == 0) {
    erro = -1;
  }
  else if (eSC == 0) {
    erro = 0;
  }
  else if (eSD == 0) {
    erro = 1;
  }
  else if (eSDM == 0) {
    erro = 2;
  } else{
    erro = 0;
  }
correcao = kP*erro;
Serial.println( eSEM);
if (erro == 0){
    analogWrite(portaMotor, 0);
    analogWrite(portaMotor1, velBase);
    analogWrite(portaMotor2, 0);
    analogWrite(portaMotor3, velBase);
}
else if( erro < 0) {
    analogWrite(portaMotor, 0);
    analogWrite(portaMotor1, (velBase + correcao));
    analogWrite(portaMotor2, (velBase - correcao));
    analogWrite(portaMotor3, 0);
}
else if (erro > 0) {
      analogWrite(portaMotor, (velBase - correcao));
    analogWrite(portaMotor1, 0);
    analogWrite(portaMotor2, 0);
    analogWrite(portaMotor3, (velBase + correcao));
}
/*if (estado1 == HIGH && estado2 == HIGH) {          //nenhum objeto detectado
    analogWrite(portaMotor, 128);
    analogWrite(portaMotor1, 0);
    analogWrite(portaMotor2, 0);
    analogWrite(portaMotor3, 128);

  } else if (estado1 == LOW && estado2 == HIGH) {    //direita detectado
    analogWrite(portaMotor, 0);
    analogWrite(portaMotor1, 0);
    analogWrite(portaMotor2, 128);
    analogWrite(portaMotor3, 0);

  } else if (estado1  == HIGH && estado2 == LOW) {          //esquerda detectado
    analogWrite(portaMotor, 0);
    analogWrite(portaMotor1, 128);
    analogWrite(portaMotor2, 0);
    analogWrite(portaMotor3, 0);

} else if (estado1 == LOW && estado2 == LOW) {          //os dois detectado
    analogWrite(portaMotor, 0);
    analogWrite(portaMotor1, 0);
    analogWrite(portaMotor2, 0);
    analogWrite(portaMotor3, 0);
  } 
  */
}