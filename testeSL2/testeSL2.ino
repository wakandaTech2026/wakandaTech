int sEM = 8;  //sensor Esquerda
int sE = 9;
int sC = 10;
int sD = 11;
int sDM = 12; //sensor direita*/

int eSEM;
int eSE;
int eSC;
int eSD;
int eSDM;

void setup() {
  // put your setup code here, to run once:
  Serial.begin (9600);
  
  pinMode(sEM, INPUT);  //definindo o pino do sensor como entrada
  pinMode(sE, INPUT); //definindo o pino do sensor como entrada
  pinMode(sD, INPUT);
  pinMode(sDM, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  eSEM = digitalRead(sEM);  //lê o estado do sensor (alto = inativo, baixo = ativo)
  eSE = digitalRead(sE);
  eSC = digitalRead(sC);   //lê o estado do sensor (alto = inativo, baixo = ativo)
  eSD = digitalRead(sD);
  eSDM = digitalRead(sDM);
  Serial.print(eSEM);
  Serial.print("///");
  Serial.print(eSE);
  Serial.print("///");
  Serial.print(eSD);
  Serial.print("///");
  Serial.println(eSDM);
  delay(50);

}
