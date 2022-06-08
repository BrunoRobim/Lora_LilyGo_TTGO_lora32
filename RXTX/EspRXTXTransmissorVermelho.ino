// bibliotecas para a comunicação Lora
#include <SPI.h>
#include <LoRa.h>

// Bibliotecas para o display OLED
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// Bibliotecas para placa de RFID (RC522)
#include <MFRC522.h>

// Define os pinos do LoRa
#define LORA_SCK 5
#define LORA_MISO 19
#define LORA_MOSI 27
#define LORA_SS 18
#define LORA_RST 14
#define LORA_DI0 26

#define led 25

void setup()
{
    SPI.end();
    Serial.begin(9600);
    pinMode(led, OUTPUT);   // define saida digial led
    digitalWrite(led, LOW); // seta o led em low
    SPI.begin(LORA_SCK, LORA_MISO, LORA_MOSI, LORA_SS);
    while (!Serial)
        ;

    // CONFIGURAÇÃO INICIAL DO LORA
    if (!LoRa.begin(915E6))
    {
        Serial.println("Inicialização da comunicação LoRa: falha!");
        for (;;)
            ;
    }
    else
    {
        Serial.println("Inicialização da comunicação LoRa: sucesso!");
    }
}

void use_lora()
{

    // A partir daqui será preparado o pacote
    // a ser enviado pelo protocolo LoRa
    // Inicia o pacote codificado
    LoRa.beginPacket();

    // Imprime no Monitor Serial da Arduino IDE
    // a mensagem "ola pacote"
    LoRa.print("COMANDO::VERMELHO");

    // Imprime no Monitor Serial da Arduino IDE
    // a mensagem "ola pacote"
    // LoRa.print(counter);

    // Termina o pacote codificado
    LoRa.endPacket();
    Serial.println("Pacote Enviado");
}

void loop()
{
    if (Serial.available() > 0)
    {
        char c = Serial.read();
        Serial.println(c);
        if (c == 'A')
        {
            use_lora();
            digitalWrite(led, HIGH);
            Serial.println("Pós função");
            delay(2000);
            digitalWrite(led, LOW);
        }
    }
}