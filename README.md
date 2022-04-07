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

A pasta LoRa é uma biblioteca que deve ser incluida em Libraries do Arduino.