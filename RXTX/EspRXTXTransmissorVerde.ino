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

#define led 25

// Inicializa o display
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RST);

// Configuração da inicialização da comunicação LoRa - Transmissor
void setup()
{
    SPI.end();
    // Inicia a porta Serial na frequencia de 9600, para que seja
    // feita a leitura no monitor Serial da arduino IDE:
    // Configurar a frequencia do monitor para a mesma frequência
    // iniciada na porta Serial
    Serial.begin(9600);

    // Verificação TX RX Arduino
    pinMode(led, OUTPUT);
    digitalWrite(led, LOW);

    SPI.begin(LORA_SCK, LORA_MISO, LORA_MOSI, LORA_SS);

    // Reseta o display OLED via software
    pinMode(OLED_RST, OUTPUT);
    // Configura a tensão para LOW
    digitalWrite(OLED_RST, LOW);
    // Delay em ms
    delay(20);
    // Configura a tensão para HIGH
    digitalWrite(OLED_RST, HIGH);

    display.setTextColor(WHITE);
    display.setTextSize(1);
    while (!Serial)
        ;

    // Inicializa o OLED
    Wire.begin(OLED_SDA, OLED_SCL);
    if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3c, false, false))
    { // Endereço 0x3C for 128x32
        Serial.println(F("SSD1306 falha na alocação"));
        for (;;)
            ; // Se erro, não prossegue, loop infinito
    }

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
        for (;;)
            ;
    }
}

void use_lora()
{

    if (Serial.available() > 0)
    {
        char c = Serial.read();
        if (c == 'A')
        {
            digitalWrite(led, HIGH);
            delay(2000);
            digitalWrite(led, LOW);
            LoRa.beginPacket();

            // Imprime no Monitor Serial da Arduino IDE
            // a mensagem "ola pacote"
            LoRa.print("Ola pacote: ");

            // Imprime no Monitor Serial da Arduino IDE
            // a mensagem "ola pacote"
            LoRa.print(counter);

            // Termina o pacote codificado
            LoRa.endPacket();
        }
    }
}

// Loop de envio dos dados pelo protocolo LoRa
void loop()
{
    use_lora();
    Serial.println("Transmissor LoRa");
    // Imprime no Monitor Serial da Arduino IDE
    // a mensagem de envio "enviando pacote:"
    Serial.print("Enviando pacote: ");

    // Imprime no Monitor Serial da Arduino IDE
    // o número do contador
    Serial.println(counter);

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
    display.setCursor(60, 30);
    // Imprime no Display OLED
    display.print(counter);
    // Envia as informações do display para o hardware
    display.display();

    // Acresce +1 ao contador
    counter++;

    // Delay em ms
    delay(1000);
}