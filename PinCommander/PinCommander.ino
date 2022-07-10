#if defined(ESP8266)
#include <ESP8266WiFi.h>
#else
#include <WiFi.h>
#endif

#include "aWOT.h"
#include "secret-wifi.h"
#include "TaskScheduler.h"
#include "pin.h"

// #include "ota.h"
#include "commander.h"
#define EMULATED 1
#define n 0.000000001
#define u 0.000001
#define m 0.001
#define K 1000
#define M 1000000
#define G 1000000000

WiFiServer server(80);
Application app;
TaskScheduler* ts=new TaskScheduler(128);

Pin* d0=new Pin(0,(char*)"D0",A,OUT);
Pin* a0=new Pin(1,(char*)"A0",A,IN);
Pin* ultrasonic=new Pin(2,(char*)"ULTRASONIC",A,IN);
int retryCount = 0;
void lambda(){
  Serial.println("-- lambda");
}
void setup() {
  Serial.begin(115200);
  Serial.print("\nRebooting...\n");
  ts->schedule(new Task{(char*)"lambda",10*M,[]{
    Serial.println("lambda2");
    char* json=ultrasonic->getJson();
    Serial.println(json);
    free(json);
    json=a0->getJson();
    Serial.println(json);
    free(json);
  }});
  ts->schedule(new Task{(char*)"updateAnalogIn",1*M,readAnalogIn});
  ts->schedule(new Task{(char*)"updateUltrasonic",2*M,readUltrasonic});
  
  delay(2000);

  for (uint8_t idx = minPinIdx; idx <= maxPinIdx; idx++) {
    Serial.printf("enabling Pin D%d[%d] for output with initial value = %d\n",idx,pins[idx],values[idx]);
    delay(100);
    pinMode(pins[idx], OUTPUT);
  }
  
  delay(2000);
  Serial.println("\nConnecting to WiFi ... ");
  delay(2000);
  WiFi.mode(WIFI_STA);
  delay(2000);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  delay(2000);
  while (!EMULATED && WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print("-");
    retryCount++;
    delay(1000);
    if(retryCount > 10 ){
      Serial.println("\nTried 10 times, restarting ... ");
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
  //Serial.print(":");
  ts->run();
  WiFiClient client = server.available();

  if (client.connected()) {
    //Serial.print("{");
    app.process(&client);
    //Serial.print("}");
  }
  delay(500);

  //readUltrasonic();
  //readAnalogIn();
  //Serial.println(".");
}

/**
 * internal read sensor
*/
void readUltrasonic(){
    // todo
    // Serial.print("<(|");
    ultrasonicDistance=random(5000,400000);
    ultrasonic->setValue(ultrasonicDistance);
}

/**
 * internal read analog in (A0)
*/
void readAnalogIn(){
    // Serial.print("<A0");
    adcVoltage=analogRead(A0)*3.3/1024;
    a0->setValue(adcVoltage);
}
