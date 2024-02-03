#include <QTRSensors.h>

QTRSensors qtr;

#define M1 9   // PinoVelocidade 1º Motor (0 a 255) Porta IN2 ponte H;
#define M2 11  // PinoVelocidade 2º Motor (0 a 255) Porta IN4 ponte H;
#define dir1 8  // PinoDireção do 1º Motor: Para frente / Para trás (HIGH ou LOW) porta IN1 ponte H;
#define dir2 10 // PinoDireção do 2º Motor: Para frente / Para trás (HIGH ou LOW) porta IN3 ponte H;

// Definição dos pinos dos sensores
#define pin_S1 7
#define pin_S2 6
#define pin_S3 5

// Parâmetros do PID
float error = 0, P = 0, i = 0, D = 0, PID = 0;
float prevError = 0, prevI = 0;
uint16_t position = 0;
const byte initial_motor_speed = 180;

// Controle PID
float Kp = 4;
float Ki = 0.0015;
float Kd = 2;

// Ponte H
const byte h[] = {10, A0, A1, A2, A3, 11};

// Variáveis
bool Sensor1, Sensor2, Sensor3;
int velocidadeCurva;
float erroAnterior, erroIntegral, erroDerivada; // para armazenar os valores do erro anterior, do erro integral e do erro derivativo.

void setup() {
  // Setamos os pinos de controle dos motores como saída
  pinMode(M1, OUTPUT);
  pinMode(M2, OUTPUT);
  pinMode(dir1, OUTPUT);
  pinMode(dir2, OUTPUT);
  // Setamos a direção inicial do motor como 0, isso fará com que ambos os motores girem para frente
  analogWrite(dir1, LOW);
  analogWrite(dir2, LOW);
  // Setamos os pinos dos sensores como entrada
  pinMode(pin_S1, INPUT);
  pinMode(pin_S2, INPUT);
  pinMode(pin_S3, INPUT);
}

void loop() {
  // Leitura dos sensores
  Sensor1 = analogRead(pin_S1);
  Sensor2 = analogRead(pin_S2);
  Sensor3 = analogRead(pin_S3);

  // Leitura dos sensores
  position = qtr.readLineBlack(sensorValues);
  error = map(position, 0, 7000, -100, 100);

  // Cálculo do PID
  P = error;
  I = i + error;
  D = error - prevError;
  PID = (Kp * P) + (Ki * I) + (Kd * D);
  prevError = error;

  // Controle dos motores
  int m1 = initial_motor_speed + PID;
  int m2 = initial_motor_speed - PID;

  // Implementação da função Speed
  void Speed(int m1, int m2) {
    // Verifica os limites de velocidade (0 a 255)
    m1 = constrain(m1, 0, 255);
    m2 = constrain(m2, 0, 255);

    // Define a direção dos motores
    if (m1 > 0) {
      digitalWrite(dir1, LOW); // Motor 1 para frente
    } else {
      digitalWrite(dir1, HIGH); // Motor 1 para trás
      m1= abs(m1); // Torna o valor positivo
    }

    if (m2 > 0) {
      digitalWrite(dir2, LOW); // Motor 2 para frente
    } else {
      digitalWrite(dir2, HIGH); // Motor 2 para trás
      m2 = abs(m2); // Torna o valor positivo
    }

    // Aplica a velocidade aos motores
    analogWrite(M1, m1);
    analogWrite(M2, m2);
  }

  // Chamada da função Speed com os valores calculados
  Speed(m1, m2);

  // Lógica de controle
  if (Sensor1 == HIGH && Sensor2 == HIGH && Sensor3 == HIGH) {
  // Robô está no centro da linha preta ou branca
  // Manter velocidade normal
  Speed(initial_speed, initial_speed);
} else if (Sensor1 == HIGH && Sensor2 == LOW && Sensor3 == HIGH) {
  // Robô está à direita da linha preta ou branca
  // Girar para a esquerda
  Speed(initial_speed/2, initial_speed);
} else if (Sensor1 == LOW && Sensor2 == HIGH && Sensor3 == HIGH) {
  // Robô está à esquerda da linha preta ou branca
  // Girar para a direita
  Speed(initial_speed, initial_speed/2);
} else if (Sensor1 == LOW && Sensor2 == LOW && Sensor3 == HIGH) {
  // Robô está em cima da linha preta
  // Seguir linha preta
  // Implementar lógica para seguir linha preta
} else if (Sensor1 == HIGH && Sensor2 == HIGH && Sensor3 == LOW) {
  // Robô está em cima da linha branca
  // Seguir linha branca
  // Implementar lógica para seguir linha branca
} else {
  // Robô perdeu a linha
  // Parar e buscar a linha
  Speed(0, 0);
  // Implementar lógica para buscar a linha
}

