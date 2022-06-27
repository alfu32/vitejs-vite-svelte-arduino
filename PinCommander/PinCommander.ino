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

WiFiServer server(80);
Application app;

int retryCount = 0;
int ultrasonicDistance=0;
double adcVoltage=0.0;

/**
 * api setPin
*/
void setPin(Request &req,Response &res){
  Serial.print("[setPin]");
  char pinIdxString[2];
  req.query("pinIdx", pinIdxString, 2);
  char valString[4];
  req.query("val", valString, 4);
  int pinIdx=String(pinIdxString).toInt();
  int val=String(valString).toInt();
  values[pinIdx]=val;
  int actual = (val)*255/100;
  analogWrite(pins[pinIdx],values[pinIdx]);
  sendStatus(req,res);
}

/**
 * api sendStatus
*/
void sendStatus(Request &req,Response &res){
  Serial.print("[sendStatus]");
  char buffLength[16];
  String status=getStatusJson();
  Sprintf(buffLength,"%d",status.length());

  res.set("Content-Type", "application/json; charset=utf-8");
  // res.set("Content-Encoding", "gzip");
  res.set("Cache-Control", "no-cache");
  res.set("Content-Length", buffLength);
  /// res.set("Last-Modified", "Mon, 27 Jun 2022 14:59:25 GMT");
  res.set("Vary", "Accept-Encoding");
  res.print(status);
}

/**
 * api getStatus
*/
void getPins(Request &req,Response &res){
  Serial.print("[getPins]");
  sendStatus(req,res);
}

String getStatusJson(){
    char buffer[256];
    sprintf(
        buffer,
        "{\n\"host\":\"%s\",\n\
        \"ultrasonicDistance\":%d,\n\
        \"pinA0Voltage\":%d,\n\
        \"pins\":[\n",
        HOST_NAME,ultrasonicDistance,adcVoltage
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

void setup() {
  Serial.begin(115200);
  Serial.print("\nRebooting...\n");
  delay(2000);

  for (uint8_t idx = minPinIdx; idx <= maxPinIdx; idx++) {
    Serial.printf("enabling Pin \D%d[%d] for output with initial value = %d\n",idx,pins[idx],values[idx]);
    delay(100);
    pinMode(pins[idx], OUTPUT);
  }
  
  delay(2000);
  Serial.println("\nConnecting to WiFi ... ");
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print("-");
    retryCount++;
    if(retryCount > 50 ){
      Serial.println("\nTried 50 times, restarting ... ");
      retryCount=0;
      delay(5000);
      ESP.restart();
    }
  }
  Serial.print("Connected to WiFi AP with localIP:");
  Serial.println(WiFi.localIP());
  Serial.print("initialising the web api");
  app.get("/pin", &setPin);
  app.get("/pins", &getPins);
  app.use(staticFiles());

  Serial.print("starting the web server");
  server.begin();
}

void loop() {
  Serial.print(".");
  WiFiClient client = server.available();

  if (client.connected()) {
    Serial.print("{");
    app.process(&client);
    Serial.print("}");
  }

  readUltrasonic();
  readAnalogIn();
  Serial.print(":");
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
