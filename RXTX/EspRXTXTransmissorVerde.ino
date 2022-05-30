#define led 25

void setup()
{
    Serial.begin(9600);
    pinMode(led, OUTPUT);
    digitalWrite(led, LOW);
}

void loop()
{
    if (Serial.available() > 0)
    {
        char c = Serial.read();
        Serial.println(c);
        if (c == 'A')
        {
            digitalWrite(led, HIGH);
            delay(2000);
            digitalWrite(led, LOW);
        }
    }
}