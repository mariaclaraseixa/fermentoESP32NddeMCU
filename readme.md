# Projeto Fermento — Integração de Sensores (ESP8266 HW-364A)

Este documento descreve o funcionamento do programa **todosSensoresConectados.c**,  esquema completo de cabeamento dos sensores utilizados e explicação detalhada do código.  


---

# 1. Visão Geral

O projeto utiliza o módulo **HW-364A** (ESP8266 + display OLED integrado) e os seguintes sensores:

- **HC-SR04** → medição de distância ultrassônica  
- **LM393** → detecção digital (0/1), conforme o módulo utilizado  
- **OLED SSD1306** → exibição das leituras

O programa exibe três telas alternando:
1. **Splash Screen** (título e equipe)  
2. **Leitura da distância do fermento (HC-SR04)**  
3. **Ambiente**: distância + estado digital do LM393  

Também envia mensagens simples ao **Serial monitor (9600 baud)** para depuração.

---

# 2. Cabeamento Detalhado

## 2.1. Pinos usados no ESP8266 HW-364A

| Função | Pino físico | GPIO |
|--------|--------------|-------|
| TRIG do HC-SR04 | **D1** | GPIO5 |
| ECHO do HC-SR04 | **D2** | GPIO4 |
| Dados do LM393 | **D3** | GPIO0 |
| Alimentação 3,3 V | **3V** | — |
| Alimentação 5 V (USB) | **VU** | — |
| Terra | **G** | — |

OLED já está integrado à placa em I²C (SDA e SCL).

---

# 3. Conexão do HC-SR04

### Alimentação
- **VCC → VU (5 V)**  
- **GND → G (terra)**  

### Sinal TRIG
- **TRIG (pino 2 do HC-SR04) → D1 (GPIO5)**  

### Sinal ECHO — Necessário Divisor de Tensão
O ECHO fornece **5 V**, e o ESP8266 suporta apenas **3,3 V** nos GPIOs.  
Portanto, é obrigatório um **divisor resistivo de 2× 10 kΩ**.

### Esquema:



### No "nó" (●) devem estar conectados:
- Saída de **R1**  
- Entrada de **R2**  
- Fio que vai para **D2 (GPIO4)**  

### Observação crítica
- **D2 nunca deve ser ligado diretamente ao GND.**  
- O divisor reduz o sinal para aproximadamente **2,5 V**, seguro para o ESP8266.

---

#  4. Conexão do Sensor LM393 (saída digital)

O módulo LM393 possui geralmente:

- VCC  
- GND  
- DO (Digital Output)

### Conexões:

| LM393 | ESP8266 |
|--------|---------|
| VCC | 3V |
| GND | G |
| DO | D3 (GPIO0) |

Se o módulo for “open collector” sem pull-up, é permitido usar `INPUT_PULLUP` no código.  
Nesta implementação, foi configurado como entrada normal.

---

#  5. Explicação do Código

O arquivo **todosSensoresConectados.c** possui as seguintes partes principais:

---

## 5.1. Inicialização

- Configuração do display OLED com a biblioteca Adafruit SSD1306.  
- Configuração dos pinos TRIG e ECHO.  
- Configuração do pino digital do LM393.  
- Inicialização da interface I²C (SDA e SCL).  
- Exibição da splash screen.

---

## 5.2. Função `medirDistanciaCm()`

Realiza a leitura do HC-SR04:

1. Gera um pulso de 10 µs no TRIG.  
2. Mede o tempo do pulso recebido no ECHO usando `pulseIn`.  
3. Aplica a fórmula:

