#define S0 4
#define S1 5
#define S2 6
#define S3 7
#define OUT 8

unsigned long calBrancoR = 20,   calBrancoG = 20,   calBrancoB = 20;
unsigned long calPretoR  = 1000, calPretoG  = 1000, calPretoB  = 1000;
bool calBrancoOk = false;
bool calPretoOk = false;

int refVermelho[3] = {0, 0, 0};
int refVerde[3]    = {0, 0, 0};
int refAzul[3]     = {0, 0, 0};
bool calVermelhoOk = false;
bool calVerdeOk = false;
bool calAzulOk = false;

bool leituraAtiva = false;

void setup() {
  Serial.begin(9600);
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(OUT, INPUT);
  digitalWrite(S0, HIGH);
  digitalWrite(S1, LOW);
  mostrarMenu();
}

void mostrarMenu() {
  Serial.println();
  Serial.println("=== Teste do TCS230 ===");
  Serial.println("Comandos:");
  Serial.println("  w -> calibrar BRANCO (obrigatorio)");
  Serial.println("  b -> calibrar PRETO  (obrigatorio)");
  Serial.println("  r -> calibrar VERMELHO (recomendado)");
  Serial.println("  g -> calibrar VERDE    (recomendado)");
  Serial.println("  a -> calibrar AZUL     (recomendado)");
  Serial.println("  s -> iniciar leitura continua");
  Serial.println("  p -> pausar leitura");
  Serial.println();
}

unsigned long lerCor(bool s2, bool s3) {
  digitalWrite(S2, s2);
  digitalWrite(S3, s3);
  delay(50);
  return pulseIn(OUT, LOW, 50000);
}

void lerMedia(unsigned long &r, unsigned long &g, unsigned long &b, int amostras = 8) {
  unsigned long somaR = 0, somaG = 0, somaB = 0;
  for (int i = 0; i < amostras; i++) {
    somaR += lerCor(LOW, LOW);
    somaG += lerCor(HIGH, HIGH);
    somaB += lerCor(LOW, HIGH);
  }
  r = somaR / amostras;
  g = somaG / amostras;
  b = somaB / amostras;
}

int normalizar(unsigned long valor, unsigned long branco, unsigned long preto) {
  if (preto <= branco) return 0;
  long resultado = map(valor, branco, preto, 255, 0);
  return constrain(resultado, 0, 255);
}

void lerRGBNormalizado(int &r, int &g, int &b) {
  unsigned long rb, gb, bb;
  lerMedia(rb, gb, bb);
  r = normalizar(rb, calBrancoR, calPretoR);
  g = normalizar(gb, calBrancoG, calPretoG);
  b = normalizar(bb, calBrancoB, calPretoB);
}

void calibrarBranco() {
  Serial.println("Calibrando branco... mantenha o sensor parado.");
  lerMedia(calBrancoR, calBrancoG, calBrancoB);
  Serial.print("  R="); Serial.print(calBrancoR);
  Serial.print(" G="); Serial.print(calBrancoG);
  Serial.print(" B="); Serial.println(calBrancoB);
  calBrancoOk = true;
  Serial.println("Branco calibrado!");
}

void calibrarPreto() {
  Serial.println("Calibrando preto... mantenha o sensor parado.");
  lerMedia(calPretoR, calPretoG, calPretoB);
  Serial.print("  R="); Serial.print(calPretoR);
  Serial.print(" G="); Serial.print(calPretoG);
  Serial.print(" B="); Serial.println(calPretoB);
  calPretoOk = true;
  Serial.println("Preto calibrado!");
}

bool prontoParaNormalizar() {
  if (!calBrancoOk || !calPretoOk) {
    Serial.println("Calibre o BRANCO ('w') e o PRETO ('b') antes desta cor.");
    return false;
  }
  return true;
}

void calibrarVermelho() {
  if (!prontoParaNormalizar()) return;
  Serial.println("Calibrando vermelho... mantenha o objeto parado.");
  lerRGBNormalizado(refVermelho[0], refVermelho[1], refVermelho[2]);
  Serial.print("  R="); Serial.print(refVermelho[0]);
  Serial.print(" G="); Serial.print(refVermelho[1]);
  Serial.print(" B="); Serial.println(refVermelho[2]);
  calVermelhoOk = true;
  Serial.println("Vermelho calibrado!");
}

void calibrarVerde() {
  if (!prontoParaNormalizar()) return;
  Serial.println("Calibrando verde... mantenha o objeto parado.");
  lerRGBNormalizado(refVerde[0], refVerde[1], refVerde[2]);
  Serial.print("  R="); Serial.print(refVerde[0]);
  Serial.print(" G="); Serial.print(refVerde[1]);
  Serial.print(" B="); Serial.println(refVerde[2]);
  calVerdeOk = true;
  Serial.println("Verde calibrado!");
}

void calibrarAzul() {
  if (!prontoParaNormalizar()) return;
  Serial.println("Calibrando azul... mantenha o objeto parado.");
  lerRGBNormalizado(refAzul[0], refAzul[1], refAzul[2]);
  Serial.print("  R="); Serial.print(refAzul[0]);
  Serial.print(" G="); Serial.print(refAzul[1]);
  Serial.print(" B="); Serial.println(refAzul[2]);
  calAzulOk = true;
  Serial.println("Azul calibrado!");
}

long distancia2(int r, int g, int b, int ref[3]) {
  long dr = r - ref[0];
  long dg = g - ref[1];
  long db = b - ref[2];
  return dr * dr + dg * dg + db * db;
}

String identificarCor(int r, int g, int b) {
  int refBranco[3] = {255, 255, 255};
  int refPreto[3]  = {0, 0, 0};

  String melhorNome = "Indefinida";
  long melhorDist = -1;
  long d;

  d = distancia2(r, g, b, refBranco);
  if (melhorDist < 0 || d < melhorDist) { melhorDist = d; melhorNome = "Branco"; }

  d = distancia2(r, g, b, refPreto);
  if (d < melhorDist) { melhorDist = d; melhorNome = "Preto"; }

  if (calVermelhoOk) {
    d = distancia2(r, g, b, refVermelho);
    if (d < melhorDist) { melhorDist = d; melhorNome = "Vermelho"; }
  }
  if (calVerdeOk) {
    d = distancia2(r, g, b, refVerde);
    if (d < melhorDist) { melhorDist = d; melhorNome = "Verde"; }
  }
  if (calAzulOk) {
    d = distancia2(r, g, b, refAzul);
    if (d < melhorDist) { melhorDist = d; melhorNome = "Azul"; }
  }

  if (calVermelhoOk && calVerdeOk) {
    int refAmarelo[3];
    refAmarelo[0] = (refVermelho[0] + refVerde[0]) / 2;
    refAmarelo[1] = (refVermelho[1] + refVerde[1]) / 2;
    refAmarelo[2] = (refVermelho[2] + refVerde[2]) / 2;
    d = distancia2(r, g, b, refAmarelo);
    if (d < melhorDist) { melhorDist = d; melhorNome = "Amarelo"; }
  }

  return melhorNome;
}

void tratarComandoSerial() {
  if (Serial.available()) {
    char comando = Serial.read();
    switch (comando) {
      case 'w': case 'W': calibrarBranco(); break;
      case 'b': case 'B': calibrarPreto(); break;
      case 'r': case 'R': calibrarVermelho(); break;
      case 'g': case 'G': calibrarVerde(); break;
      case 'a': case 'A': calibrarAzul(); break;
      case 's': case 'S':
        if (!calBrancoOk || !calPretoOk) {
          Serial.println("Calibre pelo menos o branco ('w') e o preto ('b') antes.");
        } else {
          leituraAtiva = true;
          Serial.println("Leitura iniciada.");
        }
        break;
      case 'p': case 'P':
        leituraAtiva = false;
        Serial.println("Leitura pausada.");
        break;
    }
  }
}

void loop() {
  tratarComandoSerial();

  if (!leituraAtiva) {
    delay(100);
    return;
  }

  int r, g, b;
  lerRGBNormalizado(r, g, b);

  String cor = identificarCor(r, g, b);

  Serial.print("RGB normalizado -> R:");
  Serial.print(r);
  Serial.print(" G:");
  Serial.print(g);
  Serial.print(" B:");
  Serial.print(b);
  Serial.print("   |   Cor detectada: ");
  Serial.println(cor);

  delay(500);
}