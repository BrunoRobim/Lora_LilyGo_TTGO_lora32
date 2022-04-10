// bibliotecas para a comunicação Lora
#include <SPI.h>
#include <LoRa.h>

// Bibliotecas para o display OLED
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// Bibliotecas para placa de RFID (RC522)
#include <MFRC522.h>

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

// inicia um contador inteiro iguala a 0
int counter = 0;

// Define os pinos do LoRa
#define LORA_SCK     5    
#define LORA_MISO    19   
#define LORA_MOSI    27 
#define LORA_SS      18  
#define LORA_RST     23   
#define LORA_DI0     26 

// Define os pinos do OLED
#define OLED_SDA 21
#define OLED_SCL 22
#define OLED_RST 16

// Define o tamanha do display em pixels
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

// Inicializa o display
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RST); 

// Configuração da inicialização da comunicação LoRa - Transmissor
void setup()
{
  SPI.end();
  // Inicia a porta serial na frequencia de 9600, para que seja
  // feita a leitura no monitor serial da arduino IDE:
  // Configurar a frequencia do monitor para a mesma frequência
  // iniciada na porta serial
  Serial.begin(9600);
  SPI.begin(LORA_SCK,LORA_MISO,LORA_MOSI,LORA_SS);

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
    Serial.println(F("SSD1306 falha na alocação"));
    for (;;); // Se erro, não prossegue, loop infinito
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

  // Imprime no Monitor Serial da Arduino IDE
  // uma mensagem de teste
  Serial.println("Transmissor LoRa Teste:");

  // Enquanto o serial estiver iniciado
  while (!Serial);

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
    // Limpa o display
    display.clearDisplay();
    // Define a cor do texto
    display.setTextColor(WHITE);
    // Define o tamanho do texto
    display.setTextSize(1);
    // Define a posição zero do cursor
    display.setCursor(0, 0);
    // Imprime no Display OLED 
    display.print("Inicializacao da comunicacao LoRa falhou!");
    // Envia as informações do display para o hardware
    display.display();
    while (1);
  }

  // Posiciona o cursor em uma coordenada do display
  display.setCursor(0, 10);
  // Imprime no Display OLED
  display.print("Inicialização LoRa OK!");
  // Envia as informações do display para o hardware
  display.display();
}

// Loop de envio dos dados pelo protocolo LoRa
void loop()
{
  // Imprime no Monitor Serial da Arduino IDE
  // a mensagem de envio "enviando pacote:"
  Serial.print("Enviando pacote: ");

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

  // Limpa o display
  display.clearDisplay();
  // Define a posição zero do cursor
  display.setCursor(0, 0);
  // Imprime no Display OLED
  display.println("Transmissor LoRa");
  // Posiciona o cursor em uma coordenada do display
  display.setCursor(0, 20);
  // Define o tamanho do texto
  display.setTextSize(1);
  // Imprime no Display OLED
  display.print("Pacote LoRa enviado.");
  // Posiciona o cursor em uma coordenada do display
  display.setCursor(0, 30);
  // Imprime no Display OLED
  display.print("Contador:");
  // Posiciona o cursor em uma coordenada do display
  display.setCursor(50, 30);
  // Imprime no Display OLED
  display.print(counter);
  // Envia as informações do display para o hardware
  display.display();

  // Acresce +1 ao contador
  counter++;

  // Delay em ms
  delay(1000);
}