#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// --- Config do OLED do HW-364A ---
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

#define OLED_RESET   -1
#define OLED_ADDRESS 0x3C

// Pinos I2C do HW-364A (importante!)
#define OLED_SDA 14   // SDA em GPIO14 (ajustar conforme sua ligacao real)
#define OLED_SCL 12   // SCL em GPIO12

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// --- Pinos do HC-SR04 ---
#define TRIG_PIN 5    // D1 = GPIO5
#define ECHO_PIN 4    // D2 = GPIO4 (via divisor de tensão)

// --- Pino do sensor LM393 (saida digital DO) ---
#define LM393_PIN 0   // D3 = GPIO0

// --- Protótipos ---
void showSplash();
void showFermentoDistancia();
void showAmbiente();
float medirDistanciaCm();

void setup() {
  Serial.begin(9600);

  // Inicia I2C nos pinos corretos do HW-364A
  Wire.begin(OLED_SDA, OLED_SCL);

  // Inicializa o display
  if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDRESS)) {
    Serial.println("Erro OLED");
    while (true) {
      // trava aqui se der erro
    }
  }

  display.clearDisplay();
  display.display();

  // Configura pinos do HC-SR04
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  digitalWrite(TRIG_PIN, LOW);
  delay(50);

  // Configura pino do LM393
  pinMode(LM393_PIN, INPUT); 
  // Se o módulo tiver saída open-collector sem pull-up interno, usar:
  // pinMode(LM393_PIN, INPUT_PULLUP);

  // Splash de boas-vindas
  showSplash();
}

void loop() {
  // Tela: distância do fermento (REAL, via HC-SR04)
  showFermentoDistancia();
  delay(3000);

  // Tela: ambiente (distancia REAL + estado LM393)
  showAmbiente();
  delay(3000);
}

// --------------------------------------------------------
// Splash: Projeto Fermento / Professor / Equipe
// --------------------------------------------------------
void showSplash() {
  // Tela 1: título
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("Projeto");
  display.println("Fermento");
  display.display();
  delay(2000);

  // Tela 2: professor e equipe
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.println("Professor Camargo");
  display.println();
  display.println("Equipe:");
  display.println(" Maria Clara");
  display.println(" Pamela");
  display.println(" Dereck");
  display.display();
  delay(3000);
}

// --------------------------------------------------------
// Funcao: medir distancia com HC-SR04 (em cm)
// --------------------------------------------------------
float medirDistanciaCm() {
  // Garante TRIG em LOW
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);

  // Pulso de 10 us em TRIG
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // Le o tempo do pulso em ECHO (em microsegundos)
  // Timeout de 30.000 us (~5 m) para nao travar
  unsigned long duracao = pulseIn(ECHO_PIN, HIGH, 30000);

  if (duracao == 0) {
    // Sem resposta (timeout)
    return -1.0;
  }

  // Velocidade do som ~343 m/s = 0.0343 cm/us
  // Distancia = (tempo * velocidade) / 2 (ida e volta)
  float distancia_cm = (duracao * 0.0343f) / 2.0f;

  return distancia_cm;
}

// --------------------------------------------------------
// Tela: leitura distancia do fermento (HC-SR04 REAL)
// --------------------------------------------------------
void showFermentoDistancia() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);

  float dist_cm = medirDistanciaCm();

  display.setCursor(0, 0);
  display.println("Distancia do fermento");
  display.println("---------------------");

  if (dist_cm > 0) {
    display.print("Distancia: ");
    display.print(dist_cm, 1);
    display.println(" cm");

    display.println();
    display.println("Status: OK");

    // Mensagem simples no Serial
    Serial.print("Dist: ");
    Serial.print(dist_cm, 1);
    Serial.println(" cm");
  } else {
    display.println("Erro de leitura");
    display.println("Verificar HC-SR04");

    Serial.println("Erro leitura HC-SR04");
  }

  display.display();
}

// --------------------------------------------------------
// Tela: ambiente (distancia REAL + estado LM393)
// --------------------------------------------------------
void showAmbiente() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);

  float dist_cm = medirDistanciaCm();
  int lm = digitalRead(LM393_PIN);  // 0 ou 1

  display.setCursor(0, 0);
  display.println("Leitura Ambiente");
  display.println("----------------");

  // Distancia
  display.print("Dist: ");
  if (dist_cm > 0) {
    display.print(dist_cm, 1);
    display.println(" cm");
  } else {
    display.println(" ERRO");
  }

  // Estado do LM393 (interpretacao generica)
  display.print("LM393: ");
  if (lm == HIGH) {
    display.println("ALTO");
  } else {
    display.println("BAIXO");
  }

  display.display();

  // Mensagem curta no Serial
  Serial.print("A: D=");
  if (dist_cm > 0) {
    Serial.print(dist_cm, 1);
  } else {
    Serial.print(-1);
  }
  Serial.print(" LM=");
  Serial.println(lm);
}
