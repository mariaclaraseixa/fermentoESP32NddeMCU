# Conexão do Sensor Ultrassônico HC-SR04 ao Módulo HW-364A (ESP8266 + OLED)

Este documento descreve a ligação elétrica entre o sensor HC-SR04 e a placa HW-364A (NodeMCU ESP8266 com OLED integrado). O objetivo é apresentar um guia claro e acadêmico sobre o esquema de cabeamento e o uso do divisor de tensão necessário para proteger o microcontrolador.

---

## 1. Considerações Gerais

O ESP8266 opera internamente em **3,3 V**, enquanto o sensor HC-SR04 é projetado para **5 V**.  
O sinal de saída **ECHO** do sensor atinge 5 V e **não pode** ser conectado diretamente ao pino do ESP8266.  
Por isso, é obrigatório o uso de um **divisor de tensão** antes da entrada digital.

A placa HW-364A possui um pino chamado **VU**, que fornece os **5 V** provenientes da porta USB e pode ser utilizado para alimentar o sensor.

---

## 2. Pinos Utilizados no ESP8266 (HW-364A)

| Função | Pino ESP8266 | GPIO Interno | Observação |
|--------|--------------|--------------|------------|
| TRIG (entrada no sensor) | **D1** | GPIO5 | Saída segura em 3,3 V |
| ECHO (saída do sensor) | **D2** | GPIO4 | Deve receber tensão reduzida |
| Alimentação 5 V | **VU** | — | Fornece 5 V via USB |
| Terra | **G** | — | Terra comum ao sensor |

---

## 3. Ligação dos Pinos do HC-SR04

| Pino HC-SR04 | Conexão na Placa | Observação |
|--------------|------------------|------------|
| **VCC** | VU (5 V) | Alimentação do sensor |
| **GND** | G (GND) | Referência comum |
| **TRIG** | D1 | Pulso enviado pelo ESP8266 |
| **ECHO** | D2 via divisor de tensão | Sinal deve ser reduzido de 5 V para ~2,5 V |

---

## 4. Divisor de Tensão para o Pino ECHO

Para adequar o sinal de 5 V ao nível seguro do ESP8266, foi utilizado um divisor formado por **dois resistores de 10 kΩ**:


### Explicação do funcionamento:

- O ponto marcado com **●** é o **nó** do divisor.  
- Este nó recebe o sinal reduzido para aproximadamente **2,5 V**, valor seguro e reconhecido como HIGH pelo ESP8266.  
- O pino **D2** é ligado diretamente ao nó.  
- O resistor **R2** é ligado entre o nó e o GND, completando o divisor.

---

## 5. Resumo do Esquema de Cabos

### Alimentação
- **HC-SR04 VCC → VU (5 V)**  
- **HC-SR04 GND → GND da placa**

### Sinais de controle
- **HC-SR04 TRIG → D1 (GPIO5)**  
- **HC-SR04 ECHO → divisor de tensão → D2 (GPIO4)**

### Divisor de tensão
- R1 (10 kΩ): entre **ECHO** e o **nó**  
- R2 (10 kΩ): entre **nó** e **GND**  
- Fio do **nó → D2**

---

## 6. Observações Importantes

- O divisor de tensão é obrigatório quando o sensor está alimentado com 5 V.  
- D2 **não deve ser ligado ao GND**, apenas ao nó entre os resistores.  
- O TRIG pode ser ligado diretamente ao pino D1, pois é ativado pelo ESP8266 em 3,3 V.  
- A alimentação VU somente fornece 5 V quando a placa está conectada via USB.  
- GND deve ser comum entre a placa e o sensor para que as medidas funcionem corretamente.




