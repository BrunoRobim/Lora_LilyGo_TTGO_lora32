#include <Arduino.h>

#include <SPI.h>
#include <LoRa.h>

// Bibliotecas para o display OLED
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

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
String LoRaData; // Conteúdo para o pacote a ser encapsulado

int teste = 0;

//Função de controle dos leds, para prover reutilização
void semaforo(char red, char yellow, char green){
  //LED Vermelho
  digitalWrite(13, red);
  //LED amarelo
  digitalWrite(12, yellow);
  //LED verde
  digitalWrite(14, green);
}


// Preparação do Arduino, este código irá rodar uma única vez
void setup() 
{
  // Colocamos o pino 12 do Arduino como OUTPUT (saída)
  pinMode(13, OUTPUT);
  pinMode(14, OUTPUT);
  pinMode(12, OUTPUT);

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
    Serial.println(F("SSD1306 allocation failed"));
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
  display.print("Receptor LoRa");
  // Envia as informações do display para o hardware
  display.display();

  // Enquanto o serial estiver iniciado
  while (!Serial);

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
    // Posiciona o cursor em uma coordenada do display
    display.setCursor(0, 10);
    // Imprime no Display OLED
    display.print("Inicializacao LoRa falhou!");
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
  semaforo(HIGH,LOW,LOW);
}


// Este código é chamado automáticamente pelo Arduino, ficará em
// loop até que seu Arduino seja desligado
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
      
      if (LoRaData == "COMANDO::VERDE"){
        semaforo(LOW,HIGH,LOW);
        delay(3000);
        semaforo(LOW,LOW,HIGH);
        delay(5000);
      }

      if (LoRaData == "COMANDO::VERMELHO"){
        semaforo(LOW,HIGH,LOW);
        delay(1500);
        semaforo(HIGH,LOW,LOW);
        delay(5000);
      }

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
    display.setCursor(0, 40);
    display.print(LoRa.packetRssi());
    // Envia as informações do display para o hardware
    display.display();
  }
}