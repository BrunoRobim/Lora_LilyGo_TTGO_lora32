#include <SPI.h>
#include <LoRa.h>

/*
IMPORTS / INCLUDES
__________
SPI.h   = Interface Serial de Periféricos, permite a comunicação entre
o microcontrolador e outros dipostivos via Serial Port (USB COM do computador)
LoRa.h  = Biblioteca de configurações de firmware para o uso do protocolo de
comunicação LoRa. Configuração de pinagens das placas estão neste documento.

*/

// inicia um contador inteiro iguala a 0
int counter = 0;

// Configuração da inicialização da comunicação LoRa Transmissora
void setup_lora_transmissor()
{
  // Inicia a porta serial na frequencia de 9600, para que seja
  // feita a leitura no monitor serial da arduino IDE:
  // Configurar a frequencia do monitor para a mesma frequência
  // iniciada na porta serial
  Serial.begin(9600);

  // Enquanto o serial estiver iniciado
  while (!Serial)
    ;

  // imprime a mensagem "Transmissor LoRa" no monitor serial
  // da arduino IDE
  Serial.println("Transmissor LoRa");

  // Se a comunicação LoRa não for iniciada em 915Mhz,
  // frequência ajustável de operação do protocolo e
  // antenas, imprime a mensagem de erro de falha de
  // comunicação.
  if (!LoRa.begin(915E6))
  {
    Serial.println("Inicialização da comunicação LoRa falhou!");
    while (1)
      ;
  }
}

// Loop de envio dos dados pelo protocolo LoRa
void loop_envio()
{
  // Imprime no Monitor Serial da Arduino IDE 
  // a mensagem de envio "enviando pacote:"
  Serial.print("Enviando packet: ");

  // Imprime no Monitor Serial da Arduino IDE
  // o número do contador
  Serial.println(counter);

  // A partir daqui será preparado o pacote 
  // a ser enviado pelo protocolo LoRa
  // Inicia o pacote codificado
  LoRa.beginPacket();

  // Imprime no Monitor Serial da Arduino IDE
  // a mensagem "ola pacote"
  LoRa.print("Ola pacote: ");

  // Imprime no Monitor Serial da Arduino IDE
  // a mensagem "ola pacote"
  LoRa.print(counter);

  // Termina o pacote codificado
  LoRa.endPacket();

  // Acresce +1 ao contador
  counter++;

  // Delay de 5000ms
  delay(5000);
}
