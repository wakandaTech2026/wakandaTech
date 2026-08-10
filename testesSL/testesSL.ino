int sensorPin = 7;  //sensor Esquerda
int estado1;
int ledPin = 13;
 
void setup() {
  pinMode(sensorPin, INPUT);  //definindo o pino do sensor como entrada

}
 
void loop() {
  estado1 = digitalRead(sensorPin);  //lê o estado do sensor (alto = inativo, baixo = ativo)
  

  //verificando se o sensor detectou algum objeto ou não
  if (estado1 == HIGH) {          //nenhum objeto detectado
    digitalWrite(ledPin, HIGH);

  } else if (estado1 == LOW){
    digitalWrite(ledPin, LOW);
  }
}