# Lora_LilyGo_TTGO_lora32
Repositório criado para a manutenção e gestão das principais bibliotecas LoRa para o projeto de TCC: "Apoio a Ambulâncias em Ocorrência por Meio da Utilização de RFID", desenvolvido pelo grupo de estudantes de Engenharia da Computação pela Universidade de Sorocaba:

Nome  | Github
----- | -------
Ana Beatriz | https://github.com/Anabaac
Bruno Robim | https://github.com/BrunoRobim
Kaique Fonseca | https://github.com/onezerus
Luiz Humberto | https://github.com/llaurenti


## Encapsulando os Dados para Envio por Pacote
Os pacotes são encapsulados de dados que serão enviados com o protocolo LoRa, para adicionar ou remover dados a este encapsulado, todo o dado desejado deve estar entre os métodos: ``` LoRa.beginPacket(); ``` e ``` LoRa.endPacket(); ```.

## Ambiente
- LoRa é uma biblioteca que deve ser incluida em Libraries do Arduino.
```C:\Program Files (x86)\Arduino\libraries```
- Instalar pelo ***gerenciador de bibliotecas*** as libs:
  - ```Adafruit_GFX``` **V1.10.14**
  - ```Adafruit_SSD1306``` **V2.5.7**
  - ```MFRC522``` **V1.4.10**

- As libs ```Wire.h``` e ```SPI.h``` comumente já acompanham a arduino IDE. Instalar manualmente se necessário.
- Caso a Arduino IDE não reconhecer a instalação pelo gerenciador, fazer a importação manual:
  - Ir até o diretório raiz do projeto. 
  - Copiar a biblioteca inteira
  - Colar no caminho: ```C:\Program Files (x86)\Arduino\libraries```