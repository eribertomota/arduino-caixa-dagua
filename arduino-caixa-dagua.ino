// Sistema de controle de caixa d'água - Arduino Uno
// Copyright 2021 Joao Eriberto Mota Filho <eriberto@eriberto.pro.br>
// Source: https://github.com/eribertomota/arduino-caixa-dagua
// Licença: MIT

// ###################
// Definições iniciais
// ###################

// Caixa1, inferior, distâncias em centímetros

int percent1_100 = 3;
int percent1_50  = 4;
int percent1_20  = 5;

// Caixa2, superior, distâncias em centímetros

int percent2_100 = 17;
int percent2_50  = 19;
int percent2_20  = 21;

// Medição a cada "x" milisegundos (1000 = 1 segundo)
// 'int' vai até 32.767 (= 32 segundos)
// 'long' vai até 2.147.483.647 (= 2.147.483 segundos, = 24.8 dias)
// default = 5 minutos (300 segundos)

long intervalo = 300000;
// int intervalo = 3000; // for debug

// Habilita Caixa2, superior
// 1 habilita, 0 desabilita
int cx2 = 0;

// Habilita som
// 1 habilita, 0 desabilita
int som = 1;

// ###################
// Definições internas
// ###################

// Sensor1, caixa inferior

const int trigPin1 = 10;
const int echoPin1 = 11;

// Sensor2, caixa superior

const int trigPin2 = 12;
const int echoPin2 = 13;

// LEDs, 1-3 inferior (caixa 1) e 4-6 superior (caixa 2)

const int LED1 = A0; // Caixa 1, painel portaria
const int LED2 = A1; // Caixa 1, painel portaria
const int LED3 = A2; // Caixa 1, painel portaria
const int LED4 = A3; // Caixa 2, painel portaria
const int LED5 = A4; // Caixa 2, painel portaria
const int LED6 = A5; // Caixa 2, painel portaria
const int LED7 =  2;  // Caixa 1, painel casa bombas
const int LED8 =  3;  // Caixa 1, painel casa bombas
const int LED9 =  4;  // Caixa 1, painel casa bombas
const int LED10 = 5;  // Caixa 2, painel casa bombas
const int LED11 = 6;  // Caixa 2, painel casa bombas
const int LED12 = 7;  // Caixa 2, painel casa bombas

// Reset inicial dos controles

int control1 = 0;  // Controle do alarme de caixa cheia (caixa inferior)
int control2 = 0;  // Controle do alarme de caixa enchendo, 20% (caixa inferior)
int control3 = 0;  // Controle do alarme de caixa cheia (caixa superior)
int control4 = 0;  // Controle do alarme de caixa enchendo, 20% (caixa superior)
int duration1  = 0; // Controle sensor 1 (caixa inferior)
int duration1a = 0; // Controle sensor 1 (caixa inferior)
int distance1  = 0; // Controle sensor 1 (caixa inferior)
int distance1a = 0; // Controle sensor 1 (caixa inferior)
int duration2  = 0; // Controle sensor 2 (caixa superior)
int duration2a = 0; // Controle sensor 2 (caixa superior)
int distance2  = 0; // Controle sensor 2 (caixa superior)
int distance2a = 0; // Controle sensor 2 (caixa superior)

void setup()
{
  // Buzzer

  pinMode(8, OUTPUT); // painel portaria

  // Sensor1

  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);

  // Sensor2

  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);

  // LEDs

  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
  pinMode(LED5, OUTPUT);
  pinMode(LED6, OUTPUT);
  pinMode(LED7, OUTPUT);
  pinMode(LED8, OUTPUT);
  pinMode(LED9, OUTPUT);
  pinMode(LED10, OUTPUT);
  pinMode(LED11, OUTPUT);
  pinMode(LED12, OUTPUT);

  // Serial

  Serial.begin(9600);

  // Ativa teste inicial

  teste_inicial();
}

// Loop
void loop()
{
  medicao_caixa1();

  // Caixa2, superior, apenas se estiver habilitada
  if ( cx2 == 1 ) {
    medicao_caixa2();
  }

  // Intervalo de medição
  delay(intervalo);
}

// Teste inicial do sistema. Os LEDs ficarão acesos no final.
void teste_inicial()
{
  int ii = 6;
  int LEDTEST[12] = {LED1, LED2, LED3, LED4, LED5, LED6, LED7, LED8, LED9, LED10, LED11, LED12};

  for (int i = 0; i <= 5; i++) {
    digitalWrite(LEDTEST[i], HIGH);
    digitalWrite(LEDTEST[ii], HIGH);
    if ( som == 1 ) {
      tone(9, 400, 300);
    }
    delay(1000);
    digitalWrite(LEDTEST[i], LOW);
    digitalWrite(LEDTEST[ii], LOW);
    delay(250);
    ii++;
  }

  // Acende todos os LEDs

  for (int i = 0; i <= 2; i++) {
    digitalWrite(LEDTEST[i], HIGH);
  }
  for (int i = 6; i <= 8; i++) {
    digitalWrite(LEDTEST[i], HIGH);
  }

  if ( cx2 == 1 ) {
    for (int i = 2; i <= 5; i++) {
      digitalWrite(LEDTEST[i], HIGH);
    }
    for (int i = 9; i <= 11; i++) {
      digitalWrite(LEDTEST[i], HIGH);
    }
  }
  delay(2000);
}

// Alerta emitido cada vez que o nível da água abaixa
void alerta_baixa_nivel()
{
  if ( som == 1 ) {
    for (int i = 0; i <= 2; i++) {
      tone(9, 800, 200);
      delay(1000);
    }
  }
}

// Alerta de caixa 100% cheia
void alerta_caixa_cheia()
{
  if ( som == 1 ) {
    tone(9, 200, 300);
    delay(1000);
    tone(9, 300, 600);
    delay(1000);
    tone(9, 800, 900);
    delay(1000);
  }
}

// Alerta de caixa enchendo, 20%
void alerta_caixa_20()
{
  if ( som == 1 ) {
    for (int i = 0; i <= 9; i++) {
      tone(9, 1000, 100);
      delay(250);
    }
  }
}

// Alerta de caixa vazia
void alerta_caixa_vazia()
{
  if ( som == 1 ) {
    for (int i = 0; i <= 9; i++) {
      tone(9, 400, 300);
      delay(250);
      tone(9, 800, 300);
      delay(1000);
    }
  }
}

// Medição da Caixa1, inferior

void medicao_caixa1()
{

  // #################
  // CAIXA 1, inferior
  // #################

  // Sensor1 - dupla leitura
  digitalWrite(trigPin1, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin1, LOW);
  duration1 = pulseIn(echoPin1, HIGH);
  distance1 = duration1 / 58.2;

  delay(3000);

  digitalWrite(trigPin1, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin1, LOW);
  duration1a = pulseIn(echoPin1, HIGH);
  distance1a = duration1a / 58.2;

  Serial.print("caixa inferior: ");

  if ( distance1 == distance1a )
  {
    Serial.println(distance1);
  } else
  {
    Serial.print(distance1);
    Serial.print(" ---> INVALID (");
    Serial.print(distance1);
    Serial.print(",");
    Serial.print(distance1a);
    Serial.println(")");
    return;
  }

  // Caixa1, inferior, 100%
  if ( distance1 <= percent1_100 )
  {
    digitalWrite(LED1, HIGH);
    digitalWrite(LED7, HIGH);
    if ( control1 != 0 )
    {
      control1 = 0;
      alerta_caixa_cheia();
    }
  }
  else
  {
    digitalWrite(LED1, HIGH); // Pisca o LED a cada passagem
    digitalWrite(LED7, HIGH); // Pisca o LED a cada passagem
    delay(30);

    if ( control1 == 0 )
    {
      control1 = 1;
      alerta_baixa_nivel();
    }
    digitalWrite(LED1, LOW);
    digitalWrite(LED7, LOW);
    delay(250);
  }

  // Caixa1, inferior, 50%. Beep a cada passagem do loop.
  if ( distance1 <= percent1_50 )
  {
    digitalWrite(LED2, HIGH);
    digitalWrite(LED8, HIGH);
  }
  else
  {
    digitalWrite(LED2, HIGH); // Pisca o LED a cada passagem
    digitalWrite(LED8, HIGH); // Pisca o LED a cada passagem
    delay(30);

    if ( control1 == 1 )
    {
      control1 = 2;
      alerta_baixa_nivel();
    }
    digitalWrite(LED2, LOW);
    digitalWrite(LED8, LOW);
    delay(250);

    // Beep a cada passagem
    if ( som == 1 ) {
      tone(9, 240, 40);
    }
  }

  // Caixa1, inferior, 20%
  if ( distance1 <= percent1_20 )
  {
    if ( control2 == 1 )
    {
      control1 = 2;
      control2 = 0;
      alerta_caixa_20();
    }
    digitalWrite(LED3, HIGH);
    digitalWrite(LED9, HIGH);
  }
  else
  {
    digitalWrite(LED3, HIGH); // Pisca o LED a cada passagem
    digitalWrite(LED9, HIGH); // Pisca o LED a cada passagem
    delay(30);

    if ( control1 == 2 )
    {
      control1 = 3;
      control2 = 1;
      alerta_caixa_vazia();
    }
    digitalWrite(LED3, LOW);
    digitalWrite(LED9, LOW);
    delay(250);
  }
}

void medicao_caixa2()
{

  // #################
  // CAIXA 2, superior
  // #################

  // Sensor2 - dupla leitura
  digitalWrite(trigPin1, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin1, LOW);
  duration2 = pulseIn(echoPin1, HIGH);
  distance2 = duration2 / 58.2;

  delay(3000);

  digitalWrite(trigPin1, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin1, LOW);
  duration2a = pulseIn(echoPin1, HIGH);
  distance2a = duration2a / 58.2;

  Serial.print("caixa superior: ");

  if ( distance2 == distance2a )
  {
    Serial.println(distance2);
  } else
  {
    Serial.print(distance2);
    Serial.print(" ---> INVALID (");
    Serial.print(distance2);
    Serial.print(",");
    Serial.print(distance2a);
    Serial.println(")");
    return;
  }

  // Caixa2, superior, 100%
  if ( distance2 <= percent2_100 )
  {
    digitalWrite(LED4, HIGH);
    digitalWrite(LED10, HIGH);
    if ( control3 != 0 )
    {
      control3 = 0;
      alerta_caixa_cheia();
    }
  }
  else
  {
    digitalWrite(LED4, HIGH); // Pisca o LED a cada passagem
    digitalWrite(LED10, HIGH); // Pisca o LED a cada passagem
    delay(30);

    if ( control3 == 0 )
    {
      control3 = 1;
      alerta_baixa_nivel();
    }
    digitalWrite(LED4, LOW);
    digitalWrite(LED10, LOW);
    delay(250);
  }

  // Caixa2, superior, 50%. Beep a cada passagem do loop.
  if ( distance2 <= percent2_50 )
  {
    digitalWrite(LED5, HIGH);
    digitalWrite(LED11, HIGH);
  }
  else
  {
    digitalWrite(LED5, HIGH); // Pisca o LED a cada passagem
    digitalWrite(LED11, HIGH); // Pisca o LED a cada passagem
    delay(30);

    if ( control3 == 1 )
    {
      control3 = 2;
      alerta_baixa_nivel();
    }
    digitalWrite(LED5, LOW);
    digitalWrite(LED11, LOW);
    delay(250);

    // Beep a cada passagem
    if ( som == 1 ) {
      tone(9, 240, 40);
    }
  }

  // Caixa2, superior, 20%
  if ( distance2 <= percent2_20 )
  {
    if ( control4 == 1 )
    {
      control3 = 2;
      control4 = 0;
      alerta_caixa_20();
    }
    digitalWrite(LED6, HIGH);
    digitalWrite(LED12, HIGH);
  }
  else
  {
    digitalWrite(LED6, HIGH); // Pisca o LED a cada passagem
    digitalWrite(LED12, HIGH); // Pisca o LED a cada passagem
    delay(30);

    if ( control3 == 2 )
    {
      control3 = 3;
      control4 = 1;
      alerta_caixa_vazia();
    }
    digitalWrite(LED6, LOW);
    digitalWrite(LED12, LOW);
    delay(250);
  }
}
