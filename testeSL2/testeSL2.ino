
int sEM = A3;  //sensor Esquerda
int sE = A4;
int sC = A5;
int sD = A6;
int sDM = A7; //sensor direita*/

int eSEM;
int eSE;
int eSC;
int eSD;
int eSDM;


int bS3 = 1000;
int bS4 = 1000;
int bS5 = 1000;
int bS6 = 1000;
int bS7 = 1000;

int pS3 = 0;
int pS4 = 0;
int pS5 = 0;
int pS6 = 0;
int pS7 = 0;

void calibracao(){

  unsigned long origem = millis();

  while(true){ 

    unsigned long agora = millis();

    if(agora - origem  >= 3000){
      Serial.println("Saindo da calibração");
      delay(1000);
      break;
    }

    else{
      Serial.println("Calibrando...");
      eSEM = analogRead(sEM); 
      eSE = analogRead(sE);
      eSC = analogRead(sC);  
      eSD = analogRead(sD);
      eSDM = analogRead(sDM);
      if(eSEM < bS3){
        bS3 = eSEM;
      }
      if(eSE < bS4){
        bS4 = eSE;
      }
      if(eSC < bS5){
        bS5 = eSC;
      }
      if(eSD < bS6){
        bS6 = eSD;
      }
      if(eSDM < bS7){
        bS7 = eSDM;
      }


      if(eSEM > pS3){
        pS3 = eSEM;
      }
      if(eSE > pS4){
        pS4 = eSE;
      }
      if(eSC > pS5){
        pS5 = eSC;
      }
      if(eSD > pS6){
        pS6 = eSD;
      }
      if(eSDM > pS7){
        pS7 = eSDM;
      }
    }
}


}


void setup() {
  // put your setup code here, to run once:
  Serial.begin (9600);
  
  pinMode(sEM, INPUT);  //definindo o pino do sensor como entrada
  pinMode(sE, INPUT); //definindo o pino do sensor como entrada
  pinMode(sC, INPUT);
  pinMode(sD, INPUT);
  pinMode(sDM, INPUT);

  calibracao();
}

void loop() {
  
  // put your main code here, to run repeatedly:
  /*
  eSEM = analogRead(sEM);  //lê o estado do sensor (alto = inativo, baixo = ativo)
  eSE = analogRead(sE);
  eSC = analogRead(sC);   //lê o estado do sensor (alto = inativo, baixo = ativo)
  eSD = analogRead(sD);
  eSDM = analogRead(sDM);
  Serial.print(eSEM);
  Serial.print("///");
  Serial.print(eSE);
  Serial.print("///");
  Serial.print(eSC);
  Serial.print("///");
  Serial.print(eSD);
  Serial.print("///");
  Serial.println(eSDM);
  delay(50);


  */

  Serial.print(bS3);
  Serial.print("|");
  Serial.print(pS3);
  Serial.print("///");
  Serial.print(bS4);
  Serial.print("|");
  Serial.print(pS4);
  Serial.print("///");
  Serial.print(bS5);
  Serial.print("|");
  Serial.print(pS5);
  Serial.print("///");
  Serial.print(bS6);
  Serial.print("|");
  Serial.print(pS6);
  Serial.print("///");
  Serial.print(bS7);
  Serial.print("|");
  Serial.print(pS7);
  Serial.println("----------");
  delay(20);
}
