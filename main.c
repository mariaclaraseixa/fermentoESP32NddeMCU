#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// --- Config do OLED do HW-364A ---
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

#define OLED_RESET   -1
#define OLED_ADDRESS 0x3C

// Pinos I2C do HW-364A (importante!)
#define OLED_SDA 14   // D6
#define OLED_SCL 12   // D5

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// --- Protótipos ---
void showSplash();
void showFermentoDistancia();
void showAmbiente();

void setup() {
  Serial.begin(115200);

  // Inicia I2C nos pinos corretos do HW-364A
  Wire.begin(OLED_SDA, OLED_SCL);

  // Inicializa o display
  if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDRESS)) {
    Serial.println("Falha ao iniciar OLED");
    while (true) {
      // trava aqui se der erro
    }
  }

  randomSeed(analogRead(A0)); // só para gerar valores mockados

  display.clearDisplay();
  display.display();

  // Splash de boas-vindas
  showSplash();
}

void loop() {
  // Tela: distância do fermento (mock)
  showFermentoDistancia();
  delay(3000);

  // Tela: ambiente (distância + umidade + temperatura mock)
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
// Tela mockada: leitura distancia do fermento
// --------------------------------------------------------
void showFermentoDistancia() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);

  float distancia = random(50, 250) / 10.0; // 5.0 a 25.0 cm (mock)

  display.setCursor(0, 0);
  display.println("Distancia do fermento");
  display.println("---------------------");

  display.print("Distancia: ");
  display.print(distancia, 1);
  display.println(" cm");

  display.println();
  display.println("Status: OK");

  display.display();
}

// --------------------------------------------------------
// Tela mockada: distancia, umidade e temperatura
// --------------------------------------------------------
void showAmbiente() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);

  // Valores mockados (depois troca pelos sensores reais)
  float distancia = random(50, 300) / 10.0;  // 5.0 a 30.0 cm
  float umidade   = random(300, 800) / 10.0; // 30.0 a 80.0 %
  float temp      = random(200, 350) / 10.0; // 20.0 a 35.0 C

  display.setCursor(0, 0);
  display.println("Leitura Ambiente");
  display.println("----------------");

  display.print("Dist: ");
  display.print(distancia, 1);
  display.println(" cm");

  display.print("Umid: ");
  display.print(umidade, 1);
  display.println(" %");

  display.print("Temp: ");
  display.print(temp, 1);
  display.println(" C");

  display.display();
}
