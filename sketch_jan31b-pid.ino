#define M1 9     // PinoVelocidade 1º Motor ( 0 a 255) Porta IN2 ponte H;
#define M2 11    //PinoVelocidade 2º Motor ( 0 a 255)  Porta IN4 ponte H;
#define dir1 8   //PinoDireção do 1º Motor: Para frente / Para trás (HIGH ou LOW) porta IN1 ponte H;
#define dir2 10  //PinoDireção do 2º Motor: Para frente / Para trás (HIGH ou LOW) porta IN3 ponte H;

//Definição dos pinos dos sensores
#define pin_S1 7
#define pin_S2 6
#define pin_S3 5

// Parâmetros do PID
#define KP 2.0  // eses valores podem ser altreados 
#define KI 0.05 // eses valores podem ser altreados
#define KD 0.5  // eses valores podem ser altreados

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
  digitalWrite(dir1, LOW);
  digitalWrite(dir2, LOW);
  // Setamos os pinos dos sensores como entrada
  pinMode(pin_S1, INPUT);
  pinMode(pin_S2, INPUT);
  pinMode(pin_S3, INPUT);
}

void loop() {
  // Leitura dos sensores
  Sensor1 = digitalRead(pin_S1); 
  Sensor2 = digitalRead(pin_S2);
  Sensor3 = digitalRead(pin_S3);

  // Cálculo do erro
  int erro = (Sensor2 - Sensor1) * 255; //aqui ele vai calcular o erro com basse no valor lido pelo sensor 1 - 2 e multplicar por 255

  // Controle PID
  erroIntegral += erro * 0.02; 
  erroDerivada = (erro - erroAnterior) / 0.02;
  velocidadeCurva = KP * erro + KI * erroIntegral + KD * erroDerivada;
  erroAnterior = erro;

  // Limitação da velocidade
  if (velocidadeCurva > 255) {
    velocidadeCurva = 255;
  } else if (velocidadeCurva < 0) {
    velocidadeCurva = 0;
  }

  // Controle dos motores
  if (Sensor2 == 1) {
    analogWrite(M1, velocidadeCurva);
    analogWrite(M2, velocidadeCurva);
  } else if (Sensor1 == 1) {
    analogWrite(M1, 0);
    analogWrite(M2, velocidadeCurva);
  } else if (Sensor3 == 1) {
    analogWrite(M1, velocidadeCurva);
    analogWrite(M2, 0);
  } else {
    analogWrite(M1, 0);
    analogWrite(M2, 0);
  }
}
