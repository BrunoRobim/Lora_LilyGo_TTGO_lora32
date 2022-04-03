// bibliotecas para a comunicação Lora
#include <SPI.h>
#include <LoRa.h>

// Bibliotecas para o display OLED
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

/*
IMPORTS / INCLUDES
__________
SPI.h   = Interface Serial de Periféricos, permite a comunicação entre
o microcontrolador e outros dipostivos via Serial Port (USB COM do computador)

LoRa.h  = Biblioteca de configurações de firmware para o uso do protocolo de
comunicação LoRa. Configuração de pinagens das placas estão neste documento.

Wire.h  = IO para os pinos do display embutido

Adafruit_GFX.h  = Biblioteca para  geração gráfica no display

Adafruit_SSD1306.h  = Biblioteca para a geração gráfica no display

*/

// Define os pinos do OLED
#define OLED_SDA 21
#define OLED_SCL 22
#define OLED_RST 16

// Define o tamanha do display em pixels
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

// Inicializa o display
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RST);

// Variável String para o conteúdo encapsulado do pacote recebido
String LoRaData;

// Configuração da inicialização da comunicação LoRa Receptora
void setup()
{
  // Inicia a porta serial na frequencia de 9600, para que seja
  // feita a leitura no monitor serial da arduino IDE:
  // Configurar a frequencia do monitor para a mesma frequência
  // iniciada na porta serial
  Serial.begin(9600);

  // Reseta o display OLED via software
  pinMode(OLED_RST, OUTPUT);
  // Configura a tensão para LOW
  digitalWrite(OLED_RST, LOW);
  // Delay em ms
  delay(20);
  // Configura a tensão para HIGH
  digitalWrite(OLED_RST, HIGH);

  // Inicializa o OLED
  Wire.begin(OLED_SDA, OLED_SCL);
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3c, false, false))
  { // Endereço 0x3C for 128x32
    Serial.println(F("SSD1306 allocation failed"));
    for (;;)
      ; // Se erro, não prossegue, loop infinito
  }

  // Limpa o display
  display.clearDisplay();
  // Define a cor do texto
  display.setTextColor(WHITE);
  // Define o tamanho do texto
  display.setTextSize(1);
  // Define a posição zero do cursor
  display.setCursor(0, 0);
  // Imprime no Display OLED
  display.print("Transmissor LoRa");
  // Envia as informações do display para o hardware
  display.display();

  // Enquanto o serial estiver iniciado
  while (!Serial)
    ;

  // imprime a mensagem "Receptor LoRa" no monitor serial
  // da arduino IDE
  Serial.println("Receptor LoRa");

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

  // Posiciona o cursor em uma coordenada do display
  display.setCursor(0, 10);
  // Imprime no Display OLED
  display.print("Inicialização LoRa OK!");
  // Envia as informações do display para o hardware
  display.display();
}

// Loop de leitura dos dados recebidos pelo protocolo LoRa
void loop()
{

  // Converte o pacote recebido via LoRa Connection
  int packetSize = LoRa.parsePacket();
  // se a conversão for bem sucedida
  if (packetSize)
  {

    // Imprime no Monitor Serial da Arduino IDE a mensagem de pacote recebido
    Serial.print("Pacote Recebido '");

    // Faz a leitura do pacote
    while (LoRa.available())
    {
      LoRaData = LoRa.readString();
      Serial.print(LoRaData);
    }

    // Imprime no Monitor Serial da Arduino IDE o RSSI,
    // Indicador da força do sinal recebido pelo pacote,
    // medido em dBm e em números negativos.
    Serial.print("' com RSSI ");
    Serial.println(LoRa.packetRssi());

    // Limpa o display
    display.clearDisplay();
    // Define a posição zero do cursor
    display.setCursor(0, 0);
    // Imprime no Display OLED
    display.println("Receptor LoRa");
    // Posiciona o cursor em uma coordenada do display
    display.setCursor(0, 20);
    // Define o tamanho do texto
    display.setTextSize(1);
    // Imprime no Display OLED
    display.print("Pacote LoRa Recebido.");
    // Posiciona o cursor em uma coordenada do display
    display.setCursor(0, 30);
    // Imprime no Display OLED
    display.print(LoRaData);
    // Envia as informações do display para o hardware
    display.display();
  }
}