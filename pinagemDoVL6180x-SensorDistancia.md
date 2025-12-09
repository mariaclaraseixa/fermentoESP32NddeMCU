# Pinagem do Sensor VL6180X (Time-of-Flight)

O módulo VL6180X utiliza comunicação I²C e alimentação em 3,3 V. A disposição exata pode variar conforme o fabricante, mas os pinos mais comuns são os seguintes:

## Pinagem

| Pino        | Função                                              |
|-------------|------------------------------------------------------|
| **VIN / VCC / VN** | Alimentação (3,3 V)                           |
| **GND**     | Terra (0 V)                                         |
| **SCL**     | Clock do barramento I²C                              |
| **SDA**     | Dados do barramento I²C                              |
| **SHDN / EN** | Entrada de habilitação do sensor (ativo em alto). Deve ser ligado a 3,3 V para manter o sensor ligado |
| **GPIO / INT** | Saída opcional para interrupções (não obrigatória) |

## Observações

- VIN deve ser ligado a **3,3 V** (não usar 5 V).  
- O sensor compartilha o barramento I²C com outros dispositivos, como displays SSD1306.  
- SHDN pode ser ligado diretamente ao 3,3 V caso não se deseje controle de energia via software.  
- Alguns módulos apresentam **dois furos por pino**, que são apenas duplicações eletricamente equivalentes para facilitar a soldagem.

