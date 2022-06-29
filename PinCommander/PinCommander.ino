#if defined(ESP8266)
#include <ESP8266WiFi.h>
#else
#include <WiFi.h>
#endif
#include "aWOT.h"
#include "secret-wifi.h"

// #include "ota.h"
#include "commander.h"

WiFiServer server(80);
Application app;

int retryCount = 0;

void setup() {
  Serial.begin(115200);
  Serial.print("\nRebooting...\n");
  delay(2000);

  for (uint8_t idx = minPinIdx; idx <= maxPinIdx; idx++) {
    Serial.printf("enabling Pin \D%d[%d] for output with initial value = %d\n",idx,pins[idx],values[idx]);
    delay(100);
    pinMode(pins[idx], modes[idx]);
  }
  
  delay(2000);
  Serial.println("\nConnecting to WiFi ... ");
  delay(2000);
  WiFi.mode(WIFI_STA);
  delay(2000);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  delay(2000);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print("-");
    retryCount++;
    delay(1000);
    if(retryCount > 50 ){
      Serial.println("\nTried 50 times, restarting ... ");
      retryCount=0;
      delay(5000);
      ESP.restart();
    }
  }
  Serial.print("Connected to WiFi AP with localIP:");
  Serial.println(WiFi.localIP());
    delay(1000);
  Serial.print("initialising the web api");
    delay(1000);
  commanderSetup(app);
  // updateSetup(app);
  delay(1000);
  Serial.print("starting the web server");
  delay(1000);
  server.begin();
}

void loop() {
  Serial.print(":");
  WiFiClient client = server.available();

  if (client.connected()) {
    Serial.print("{");
    app.process(&client);
    Serial.print("}");
  }
  delay(500);

  readUltrasonic();
  readAnalogIn();
  Serial.println(".");
}

/**
 * internal read sensor
*/
void readUltrasonic(){
    // todo
    Serial.print("*");
    ultrasonicDistance=random(5000,400000);
}

/**
 * internal read analog in (A0)
*/
void readAnalogIn(){
    Serial.print("<");
    adcVoltage=analogRead(A0)*3.3/1024;
}
