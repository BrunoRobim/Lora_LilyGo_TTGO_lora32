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
  Serial.begin(9600);
  while (!Serial)
    ;

  Serial.println("LoRa Sender");

  if (!LoRa.begin(915E6))
  {
    Serial.println("Starting LoRa failed!");
    while (1)
      ;
  }
}

void loop()
{
  Serial.print("Sending packet: ");
  Serial.println(counter);

  // send packet
  LoRa.beginPacket();
  LoRa.print("hello ");
  LoRa.print(counter);
  LoRa.endPacket();

  counter++;

  delay(5000);
}
