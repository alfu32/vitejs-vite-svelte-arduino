#include <ESP8266WiFi.h>
#include "aWOT.h"
#include "secret-wifi.h"
#include "StaticFiles.h"

uint8_t pins[10]={
  D0,D1,D2,D3,D4,
  D5,D6,D7,D8,
  LED_BUILTIN,
};
uint8_t values[10]={
  10,20,30,40,50,
  60,70,80,90,
  5,
};
static const uint8_t minPinIdx = 0;
static const uint8_t maxPinIdx = 8;
String host="esp8266-generic";
int ultrasonicDistance=0;
double adcVoltage=0.0;



void setPin(Request &req,Response &res){
  char pinIdxString[2];
  req.query("pinIdx", pinIdxString, 2);
  char valString[4];
  req.query("val", valString, 4);
  int pinIdx=String(pinIdxString).toInt();
  int val=String(valString).toInt();
  values[pinIdx]=val;
  int actual = (val)*255/100;
  analogWrite(pins[pinIdx],values[pinIdx]);
  res.print(getStatusJson());
}

void getPins(Request &req,Response &res){
  res.print(getStatusJson());
}

String getStatusJson(){
    char buffer[256];
    sprintf(
        buffer,
        "{\n\"host\":\"%s\",\n\
        \"ultrasonicDistance\":%d,\n\
        \"pinA0Voltage\":%d,\n\
        \"pins\":[\n",
        host,ultrasonicDistance,adcVoltage
    );
    String ptr = "";
    ptr+=buffer;
    for (uint8_t idx = minPinIdx; idx <= maxPinIdx; idx++) {
        int currentPinValue = values[idx];
        uint8_t currentPin = pins[idx];
        int actual = (currentPinValue)*255/100;
        if(idx!=minPinIdx){
            ptr+=",";
        }
        sprintf(buffer,"\n{\"name\":\"\D%d\",\
        \"pinId\":%d,\
        \"pwm\":%d,\
        \"actualValue\":%d\
        }",idx,currentPin,currentPinValue,actual);
        ptr+=buffer;
    }
    ptr+="\n]\n}";
    return ptr;
}


WiFiServer server(80);
Application app;

void setup() {
  for (uint8_t idx = minPinIdx; idx <= maxPinIdx; idx++) {
    Serial.printf("enabling Pin \D%d[%d] for output with initial value = %d\n",idx,pins[idx],values[idx]);
    pinMode(pins[idx], OUTPUT);
  }
  Serial.begin(115200);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println(WiFi.localIP());
  app.get("/pin", &setPin);
  app.get("/pins", &getPins);
  app.use(staticFiles());

  server.begin();
}

void loop() {
  WiFiClient client = server.available();

  if (client.connected()) {
    app.process(&client);
  }

  readUltrasonic();
  readAnalogIn();
}

void readUltrasonic(){
    // todo
    ultrasonicDistance=random(5000,400000);
}
void readAnalogIn(){
    adcVoltage=analogRead(A0)*3.3/1024;
}
