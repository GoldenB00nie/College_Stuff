
// ---------- PINOS DOS SENSORES ----------
const int S1 = A0;  // mais à esquerda
const int S2 = A1;
const int S3 = A2;  // central
const int S4 = A3;
const int S5 = A4;  // mais à direita

// ---------- L293D / MOTORES ----------
const int ENA = A7;  // PWM motor esquerdo
const int IN1 = 3;
const int IN2 = 2;

const int IN3 = 5;
const int IN4 = 4;
const int ENB = A6;  // PWM motor direito

// ---------- HC-SR04 ----------
const int TRIG = 9;
const int ECHO = 10;

// velocidade base (0–255)
int baseSpeed = 150;

// distância mínima para parar/desviar (cm)
const int OBSTACLE_DIST = 15;

// --------------- FUNÇÕES AUXILIARES ---------------

void setMotors(int leftSpeed, int rightSpeed) {
  // leftSpeed/rightSpeed: -255 (ré) até +255 (frente)

  // Motor esquerdo
  if (leftSpeed > 0) {
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
  } else if (leftSpeed < 0) {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    leftSpeed = -leftSpeed;
  } else {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
  }

  leftSpeed = constrain(leftSpeed, 0, 255);
  analogWrite(ENA, leftSpeed);

  // Motor direito
  if (rightSpeed > 0) {
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
  } else if (rightSpeed < 0) {
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
    rightSpeed = -rightSpeed;
  } else {
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
  }

  rightSpeed = constrain(rightSpeed, 0, 255);
  analogWrite(ENB, rightSpeed);
}

void stopMotors() {
  setMotors(0, 0);
}

long measureDistanceCM() {
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);

  long duration = pulseIn(ECHO, HIGH, 30000);  // timeout ~30 ms
  if (duration == 0) return 999;               // sem eco
  return duration / 58;                        // µs -> cm
}

// Lê sensores e devolve um “padrão” de 5 bits: bS5S4S3S2S1
byte readSensors() {
  int v1 = digitalRead(S1);
  int v2 = digitalRead(S2);
  int v3 = digitalRead(S3);
  int v4 = digitalRead(S4);
  int v5 = digitalRead(S5);

  // Se o módulo devolver 0 na linha e 1 fora, e você quiser o contrário,
  // basta inverter: v1 = !digitalRead(S1); etc.
  byte pattern = (v5 << 4) | (v4 << 3) | (v3 << 2) | (v2 << 1) | v1;
  return pattern;
}

// --------------- SETUP ---------------

void setup() {
  pinMode(S1, INPUT);
  pinMode(S2, INPUT);
  pinMode(S3, INPUT);
  pinMode(S4, INPUT);
  pinMode(S5, INPUT);

  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENB, OUTPUT);

  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);

  stopMotors();
  Serial.begin(9600);
}

// --------------- LOOP PRINCIPAL ---------------

void loop() {
  // 1) Verifica obstáculo à frente
  long dist = measureDistanceCM();
  if (dist < OBSTACLE_DIST) {
    // Obstáculo perto: para e dá ré/curva (simples)
    stopMotors();
    delay(200);

    // dá uma ré curtinha
    setMotors(-baseSpeed, -baseSpeed);
    delay(300);

    // gira um pouco para a direita
    setMotors(baseSpeed, -baseSpeed);
    delay(300);

    stopMotors();
    return;  // volta pro início do loop
  }

  // 2) Segue a linha com base nos sensores
  byte s = readSensors();
  // Exemplo considerando que “1” = sensor em cima da linha:
  bool b1 = s & 0b00001;
  bool b2 = s & 0b00010;
  bool b3 = s & 0b00100;
  bool b4 = s & 0b01000;
  bool b5 = s & 0b10000;

  // Casos simples de controle:
  if (b3 && !b2 && !b4) {
    // Linha no centro → vai reto
    setMotors(baseSpeed, baseSpeed);
  } else if (b2 || (b1 && !b5)) {
    // Mais linha do lado esquerdo → vira à esquerda
    setMotors(baseSpeed * 0.5, baseSpeed);
  } else if (b4 || (b5 && !b1)) {
    // Mais linha do lado direito → vira à direita
    setMotors(baseSpeed, baseSpeed * 0.5);
  } else if (b1 && !b2 && !b3 && !b4 && !b5) {
    // só extremo esquerdo → curva bem fechada à esquerda
    setMotors(0, baseSpeed);
  } else if (b5 && !b4 && !b3 && !b2 && !b1) {
    // só extremo direito → curva bem fechada à direita
    setMotors(baseSpeed, 0);
  } else {
    // Linha perdida (todos 0 ou todos 1, depende do seu módulo)
    stopMotors();
  }

  delay(10);  // suaviza leitura
}