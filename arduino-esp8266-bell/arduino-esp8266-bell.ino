/*
  Door Bell

  Tested on NodeMCU V3

  by Ivan Seniv <https://github.com/seniv>
*/

#include <ESP8266WiFi.h>

// Wi-Fi settings
const char* ssid = "name"; // wi-fi name
const char* password = "password"; // wi-fi password

// host and url of telegram bot
const char* host = "example.com";
const char* url = "/api/bell";
const int port = 443; // https port

const int buttonPin = D1;
const int ledPin = D4;

int buttonState = 1;
int prevButtonState = 1;

void blinkLED (int times) {
  for (uint8_t t = times; t > 0; t--) {
    digitalWrite(ledPin, LOW);
    delay(200);
    digitalWrite(ledPin, HIGH);
    delay(200);
  }
}

void setup()
{
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);
  digitalWrite(ledPin, HIGH);


  Serial.begin(115200);
  Serial.println();

  Serial.printf("Connecting to %s ", ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  // blink built-in LED 3 times on connect
  blinkLED(3);

  Serial.println("");
  Serial.print("Connected, IP address: ");
  Serial.println(WiFi.localIP());
}

void bell() {
  WiFiClientSecure client;

  client.setInsecure();

  Serial.printf("\n[Connecting to %s ... ", host);
  if (client.connect(host, port))
  {
    Serial.println("connected]");

    Serial.println("[Sending a request]");
    client.print(String("GET ") + url + " HTTP/1.1\r\n" +
                 "Host: " + host + "\r\n" +
                 "Connection: close\r\n" +
                 "\r\n"
                );

    Serial.println("[Response:]");
    while (client.connected() || client.available())
    {
      if (client.available())
      {
        String line = client.readStringUntil('\n');
        Serial.println(line);
      }
    }
    client.stop();
    Serial.println("\n[Disconnected]");
  }
  else
  {
    Serial.println("connection failed!]");
    client.stop();
  }
  delay(5000);
}


void loop()
{
  buttonState = digitalRead(buttonPin);
  if (buttonState != prevButtonState) {
    prevButtonState = buttonState;
    if (buttonState == LOW) {
      bell();
    }
  }

  delay(50);
}
