#include <SPI.h>
#include <LoRa.h>

// Configuração da inicialização da comunicação LoRa
void setup_lora() {
  // Inicia a porta serial na frequencia de 9600, para que seja
  // feita a leitura no monitor serial da arduino IDE:
  // Configurar a frequencia do monitor para a mesma frequência 
  // iniciada na porta serial
  Serial.begin(9600);
  
  // Enquanto o serial estiver iniciado
  while (!Serial);

  // printar a mensagem "lora receiver" no monitor serial
  // da arduino IDE
  Serial.println("Receptor LoRa")

  // Se a comunicação LoRa não for iniciada em 915Mhz,
  // frequência ajustável de operação do protocolo e 
  // antenas. Imprime a mensagem de erro de falha de 
  // comunicação.
  if (!LoRa.begin(915E6)) {
    Serial.println("Inicialização da comunicação LoRa falhou!");
    while (1);
  }
}

// Loop de leitura dos dados recebidos pelo protocolo LoRa
void loop_leitura() {

  // Tenrta converter o pacote recebido via LoRa Connection
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    // Printa a mensagem de pacote recebido
    Serial.print("Pacote Recebido '");

    // Faz a leitura do pacote
    while (LoRa.available()) {
      // Imprime no Monitor Serial da Arduino IDE o pacote lido
      Serial.print((char)LoRa.read());
    }

    // Imprime no Monitor Serial da Arduino IDE o RSSI,
    // Indicador da força do sinal recebido pelo pacote,
    // medido em dBm.
    Serial.print("' com RSSI ");
    Serial.println(LoRa.packetRssi());
  }
}