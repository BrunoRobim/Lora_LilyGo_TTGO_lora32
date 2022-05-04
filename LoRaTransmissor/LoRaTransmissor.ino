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
// Define os pinos do LoRa
#define LORA_SCK 5
#define LORA_MISO 19
#define LORA_MOSI 27
#define LORA_SS 18
#define LORA_RST 14
#define LORA_DI0 26
// Define os pinos do RC522
#define RFID_SDA 5
#define RFID_SCK 18
#define RFID_MOSI 23
#define RFID_MISO 19
#define RFID_RST 27
// Define os pinos do OLED
#define OLED_SDA 21
#define OLED_SCL 22
#define OLED_RST 16
// Define o tamanha do display em pixels
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

String uidString;
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RST); // Inicializa o display
MFRC522 mfrc522(RFID_SDA, RFID_RST);                                    // Create MFRC522 instance
int current_spi = -1;                                                   // -1 - NOT STARTED   0 - RFID   1 - LORA
int packages_sent_count = 0;

void setup()
{
  SPI.end();
  // Inicia a porta serial na frequencia de 9600, para que seja
  // feita a leitura no monitor serial da arduino IDE:
  // Configurar a frequencia do monitor para a mesma frequência
  // iniciada na porta serial
  Serial.begin(9600);
  pinMode(OLED_RST, OUTPUT); // Reseta o display OLED via software
  digitalWrite(OLED_RST, LOW);
  delay(20);
  digitalWrite(OLED_RST, HIGH);
  Wire.begin(OLED_SDA, OLED_SCL);
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3c, false, false))
  {
    // Endereço 0x3C for 128x32
    Serial.println(F("SSD1306 falha na alocação"));
    for (;;)
      ; // Se erro, não prossegue, loop infinito
  }
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.print("Transmissor LoRa");
  display.display(); // Envia as informações do display para o hardware
  Serial.println("Transmissor LoRa Teste:");
  while (!Serial);
  Serial.println("Transmissor LoRa!!");
  // Se a comunicação LoRa não for iniciada em 915Mhz,
  // frequência ajustável de operação do protocolo e
  // antenas, imprime a mensagem de erro de falha de
  // comunicação.
  
}

bool rfid_check()
{
  select_spi(0);
  // Look for new cards
  if (!mfrc522.PICC_IsNewCardPresent())
  {
    delay(100);
    return false;
  }
  if (!mfrc522.PICC_ReadCardSerial())
  {
    return false;
  }
  // Dump debug info about the card; PICC_HaltA() is automatically called
  Serial.print("My Card UID:");
  printDec(mfrc522.uid.uidByte, mfrc522.uid.size);
  uidString = String(mfrc522.uid.uidByte[0]) + " " + String(mfrc522.uid.uidByte[1]) + " " + String(mfrc522.uid.uidByte[2]) + " " + String(mfrc522.uid.uidByte[3]);
  mfrc522.PICC_DumpToSerial(&(mfrc522.uid));
  return true;
}

void printUID(String msg)
{
  display.clearDisplay();
  display.setCursor(0, 0);
  display.print(uidString); // write UID to the internal memory
  display.display();
}

void printDec(byte *buffer, byte bufferSize)
{
  for (byte i = 0; i < bufferSize; i++)
  {
    Serial.print(buffer[i] < 0x10 ? " 0" : " ");
    Serial.print(buffer[i], DEC);
  }
}

void lora_send()
{
  select_spi(1);
  if (!LoRa.begin(915E6))
  {
    Serial.println("Inicialização da comunicação LoRa falhou!");
    display.clearDisplay();
    display.setTextColor(WHITE);
    display.setTextSize(1);
    display.setCursor(0, 0);
    display.print("Inicializacao da comunicacao LoRa falhou!");
    display.display();
    while (1)
      ;
  }
  display.setCursor(0, 10);
  display.print("Inicializacao LoRa OK!");
  display.display();
  packages_sent_count++;
  LoRa.beginPacket();
  LoRa.print("Ola pacote: ");
  LoRa.print(packages_sent_count);
  LoRa.endPacket(); // Termina o pacote codificado
  printPackage();
}

void printPackage()
{
  display.clearDisplay();  // Limpa o display
  display.setCursor(0, 0); // Define a posição zero do cursor
  display.println("Transmissor LoRa!");
  display.setCursor(0, 20);
  display.setTextSize(1);
  display.print("Pacote LoRa enviado.");
  display.setCursor(0, 30);
  display.print("Contador:");
  display.setCursor(60, 30);
  display.print(packages_sent_count);
  display.display(); // Envia as informações do display para o hardware
}

void loop()
{
  bool card_present = rfid_check();
  if (card_present)
    lora_send();
  if (!card_present)
    printUID;
  Serial.print("Enviando pacote: ");
  Serial.println(packages_sent_count);
  delay(1000);
}

void select_spi(int desired_spi)
{
  if (desired_spi == current_spi)
    return;
  SPI.end();
  switch (desired_spi)
  {
  case 0:
    SPI.begin(RFID_SCK, RFID_MISO, RFID_MOSI);
    mfrc522.PCD_Init();
    break;
  case 1:
    SPI.begin(LORA_SCK, LORA_MISO, LORA_MOSI, LORA_SS);
    LoRa.setPins(LORA_SS, LORA_RST, LORA_DI0);
    break;
  }
  current_spi = desired_spi;
}
