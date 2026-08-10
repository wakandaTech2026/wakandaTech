int portaMotor = 2;
int portaMotor1 = 3;
int portaMotor2 = 4;
int portaMotor3 = 5;

int sensorPin = 8;  //sensor Esquerda
int sensorPin2 = 9;
/*
int sensorPin3 = 10;
int sensorPin4 = 11;
int sensorPin5 = 12; //sensor direita*/

int estado1;
int estado2;
/*int estado3;
int estado4;
int estado5;         //variável utilizada armazenar o estado do sensor
*/

int trigPin = 6;
int echoPin = 7;
long duration, cm;
 
void setup() {
  Serial.begin (9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  pinMode(portaMotor, OUTPUT);
  pinMode(portaMotor1, OUTPUT);
  pinMode(portaMotor2, OUTPUT);
  pinMode(portaMotor3, OUTPUT);

  pinMode(sensorPin, INPUT);  //definindo o pino do sensor como entrada
  pinMode(sensorPin2, INPUT);
 /* pinMode(sensorPin3, INPUT);  //definindo o pino do sensor como entrada
  pinMode(sensorPin4, INPUT);
  pinMode(sensorPin5, INPUT);
  */
}
 
void loop() {

  //motor e sensor de distancia
  /*
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
  estado1 = digitalRead(sensorPin);  //lê o estado do sensor (alto = inativo, baixo = ativo)
  estado2 = digitalRead(sensorPin2);
 /* estado3 = digitalRead(sensorPin3);  //lê o estado do sensor (alto = inativo, baixo = ativo)
  estado4 = digitalRead(sensorPin4);
  estado5 = digitalRead(sensorPin5;
*/
  //verificando se o sensor detectou algum objeto ou não
  if (estado1 == HIGH && estado2 == HIGH) {          //nenhum objeto detectado
    analogWrite(portaMotor, 0);
    analogWrite(portaMotor1, 80);
    analogWrite(portaMotor2, 0);
    analogWrite(portaMotor3, 80);

  } else if (estado1 == LOW && estado2 == HIGH) {    //direita detectado
    analogWrite(portaMotor, 0);
    analogWrite(portaMotor1, 80);
    analogWrite(portaMotor2, 0);
    analogWrite(portaMotor3, 0);

  } else if (estado1  == HIGH && estado2 == LOW) {          //esquerda detectado
    analogWrite(portaMotor, 0);
    analogWrite(portaMotor1, 0);
    analogWrite(portaMotor2, 0);
    analogWrite(portaMotor3, 80);

} else if (estado1 == LOW && estado2 == LOW) {          //os dois detectado
    analogWrite(portaMotor, 0);
    analogWrite(portaMotor1, 0);
    analogWrite(portaMotor2, 0);
    analogWrite(portaMotor3, 0);
  } 
}