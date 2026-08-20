// ------------------------------------------------------------
// PINOS DO MOTOR
// ------------------------------------------------------------

const int PINO_INA = 4;
const int PINO_ENA = 5;


// ------------------------------------------------------------
// PINOS DO ENCODER
// ------------------------------------------------------------

// Canais de saída do encoder
const int PINO_CH2 = 6;
const int PINO_CH1 = 7;


// ------------------------------------------------------------
// VARIÁVEIS PARA IDENTIFICAR O SENTIDO
// ------------------------------------------------------------

volatile int estado;
volatile int ultimo_estado = LOW;
volatile boolean sentido = true;


// ------------------------------------------------------------
// CONTADORES DO ENCODER
// ------------------------------------------------------------

volatile unsigned long contador1 = 0;
volatile unsigned long contador2 = 0;

const int NUMERO_CONTADORES = 2;
const int NUMERO_LEITURAS = 2;


// ------------------------------------------------------------
// NÚMERO DE DENTES DO ENCODER
// ------------------------------------------------------------

const int NUMERO_DENTES = 10;


// ------------------------------------------------------------
// DEGRAU ATUAL DA RODA
// ------------------------------------------------------------

// Com 10 dentes:
// 0, 1, 2, 3 ... 9
volatile int degrauAtual = 0;


// ------------------------------------------------------------
// TEMPORIZAÇÃO
// ------------------------------------------------------------

unsigned long tempo_antes = 0;
const unsigned long MINUTO = 60000;


// ============================================================
// SETUP
// ============================================================

void setup() {

  // Inicialização do monitor serial
  Serial.begin(9600);

  Serial.println("Monitoramento de Motor DC");
  Serial.println("------------------------------------");


  // ----------------------------------------------------------
  // MOTOR
  // ----------------------------------------------------------

  pinMode(PINO_INA, OUTPUT);
  pinMode(PINO_ENA, OUTPUT);

  digitalWrite(PINO_INA, LOW);
  analogWrite(PINO_ENA, 0);


  // ----------------------------------------------------------
  // ENCODER
  // ----------------------------------------------------------

  pinMode(PINO_CH2, INPUT);
  pinMode(PINO_CH1, INPUT);

  ultimo_estado = digitalRead(PINO_CH2);


  // Interrupções do encoder
  attachInterrupt(
    digitalPinToInterrupt(PINO_CH2),
    contador_pulso2,
    CHANGE
  );

  attachInterrupt(
    digitalPinToInterrupt(PINO_CH1),
    contador_pulso1,
    CHANGE
  );
}


// ============================================================
// LOOP
// ============================================================

void loop() {

  // ----------------------------------------------------------
  // DEFINE O SENTIDO DO MOTOR
  // ----------------------------------------------------------

  digitalWrite(PINO_INA, HIGH);


  // ----------------------------------------------------------
  // ZERA OS CONTADORES
  // ----------------------------------------------------------

  noInterrupts();

  contador1 = 0;
  contador2 = 0;

  interrupts();

  tempo_antes = millis();


  // ----------------------------------------------------------
  // PARA O MOTOR
  // ----------------------------------------------------------

  analogWrite(PINO_ENA, 0);

  delay(1000);


  // ----------------------------------------------------------
  // RAMPA DE ACELERAÇÃO
  // ----------------------------------------------------------

  for (int i = 0; i < 255; i++) {

    analogWrite(PINO_ENA, i);

    delay(10);
  }


  // ----------------------------------------------------------
  // COPIA AS VARIÁVEIS DO ENCODER
  // ----------------------------------------------------------

  noInterrupts();

  unsigned long leitura1 = contador1;
  unsigned long leitura2 = contador2;

  int degrau = degrauAtual;
  boolean sentidoAtual = sentido;

  interrupts();


  // ----------------------------------------------------------
  // MOSTRA O SENTIDO
  // ----------------------------------------------------------

  if (sentidoAtual) {

    Serial.print("Sentido: Horario");

  } else {

    Serial.print("Sentido: Anti-Horario");
  }


  Serial.print(" | ");


  // ----------------------------------------------------------
  // CALCULA A VELOCIDADE
  // ----------------------------------------------------------

  unsigned long media =
    (leitura1 + leitura2) / NUMERO_CONTADORES;

  unsigned long velocidade =
    media / (NUMERO_DENTES * NUMERO_LEITURAS);


  Serial.print("Velocidade: ");

  Serial.print(velocidade);

  Serial.print(" RPM");


  // ----------------------------------------------------------
  // MOSTRA O DEGRAU ATUAL
  // ----------------------------------------------------------

  Serial.print(" | Degrau: ");

  Serial.print(degrau);

  Serial.print("/");

  Serial.print(NUMERO_DENTES - 1);


  // ----------------------------------------------------------
  // CALCULA A POSIÇÃO ANGULAR
  // ----------------------------------------------------------

  float angulo =
    degrau * (360.0 / NUMERO_DENTES);

  Serial.print(" | Angulo: ");

  Serial.print(angulo, 1);

  Serial.println(" graus");
}


// ============================================================
// INTERRUPÇÃO DO CANAL 2
// ============================================================

void contador_pulso2() {

  // Conta todas as mudanças de estado do canal 2
  contador2++;


  // ----------------------------------------------------------
  // VERIFICA O SENTIDO SOMENTE NA BORDA DE SUBIDA DO CH2
  // ----------------------------------------------------------

  estado = digitalRead(PINO_CH2);


  if (ultimo_estado == LOW && estado == HIGH) {


    // --------------------------------------------------------
    // SENTIDO HORÁRIO
    // --------------------------------------------------------

    if (digitalRead(PINO_CH1) == LOW) {

      sentido = true;

      degrauAtual++;


      // Depois do degrau 9 volta para 0
      if (degrauAtual >= NUMERO_DENTES) {

        degrauAtual = 0;
      }


    // --------------------------------------------------------
    // SENTIDO ANTI-HORÁRIO
    // --------------------------------------------------------

    } else {

      sentido = false;

      degrauAtual--;


      // Antes do degrau 0 volta para 9
      if (degrauAtual < 0) {

        degrauAtual = NUMERO_DENTES - 1;
      }
    }
  }


  ultimo_estado = estado;
}


// ============================================================
// INTERRUPÇÃO DO CANAL 1
// ============================================================

void contador_pulso1() {

  contador1++;
}