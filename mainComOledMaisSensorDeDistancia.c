#define TRIG_PIN 5   // D1
#define ECHO_PIN 4   // D2

void setup() {
  Serial.begin(115200);

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  digitalWrite(TRIG_PIN, LOW);
  delay(1000);
}

float medirDistanciaCm() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  unsigned long duracao = pulseIn(ECHO_PIN, HIGH, 30000); // 30 ms timeout

  if (duracao == 0) {
    return -1.0; // timeout
  }

  float distancia_cm = (duracao * 0.0343) / 2.0;
  return distancia_cm;
}

void loop() {
  float d = medirDistanciaCm();

  if (d < 0) {
    Serial.println("Timeout: sem eco");
  } else {
    Serial.print("Distancia: ");
    Serial.print(d);
    Serial.println(" cm");
  }

  delay(500);
}
