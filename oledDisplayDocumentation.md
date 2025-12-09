# Documento Técnico — Configuração do Display OLED no Módulo HW-364A (ESP8266 + SSD1306)

Este documento apresenta a configuração mínima necessária para operar o display OLED integrado ao módulo HW-364A, baseado no microcontrolador ESP8266 (NodeMCU ESP-12E). Seu objetivo é oferecer uma referência clara, objetiva e apropriada ao uso acadêmico, facilitando a inicialização, teste e integração da tela em projetos experimentais.

---

## 1. Especificações do Display

- Controlador: **SSD1306**  
- Interface: **I2C**  
- Resolução: **128 × 64 pixels**  
- Endereço I2C padrão mais comum: **0x3C**  
- Tensão de operação: **3.3 V**

---

## 2. Mapeamento dos Pinos I2C no HW-364A

O módulo HW-364A possui mapeamento I2C diferente do padrão do ESP8266. Os pinos conectados ao display são:

| Função | GPIO ESP8266 | Nome no NodeMCU |
|-------|--------------|------------------|
| SDA   | GPIO14       | D6               |
| SCL   | GPIO12       | D5               |

Observação: algumas revisões podem inverter a ligação física. Caso o display não inicie corretamente, recomenda-se testar a ordem invertida no comando `Wire.begin()`.

---

## 3. Bibliotecas Necessárias

Instalar via **Arduino IDE → Ferramentas → Gerenciar Bibliotecas**:

- **Adafruit GFX Library**  
- **Adafruit SSD1306**

Essas bibliotecas são indispensáveis para o controle do display e para a renderização gráfica.

---

## 4. Configuração do Barramento I2C

O barramento I2C deve ser explicitamente configurado com os pinos corretos do módulo, antes da inicialização do display:

```cpp
Wire.begin(14, 12);  // SDA = GPIO14 (D6), SCL = GPIO12 (D5)
