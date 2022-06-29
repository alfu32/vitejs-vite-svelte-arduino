#include "StaticFiles.h"
#define PWM_MULTIPLIER 1024/100

#if defined(ESP8266)
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
uint8_t modes[10]={
  OUTPUT,OUTPUT,OUTPUT,OUTPUT,OUTPUT,
  OUTPUT,OUTPUT,OUTPUT,OUTPUT,
};
#define PLATFORM_ID "ESP_8266 "
static const uint8_t minPinIdx = 0;
static const uint8_t maxPinIdx = 8;
#elif defined(ESP32)
#include "esp32_analogWrite.h"
#define PLATFORM_ID "ESP_32 "
uint8_t pins[10]={
  T0,T1,T2,T3,T4,
  T5,T6,T7,T8,T9
};
uint8_t values[10]={
  10,20,30,40,50,
  60,70,80,90,
};
uint8_t modes[10]={
  OUTPUT,OUTPUT,OUTPUT,OUTPUT,OUTPUT,
  OUTPUT,OUTPUT,OUTPUT,OUTPUT,
};
static const uint8_t minPinIdx = 0;
static const uint8_t maxPinIdx = 8;
#endif
int ultrasonicDistance=0;
double adcVoltage=0.0;


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
        uint8_t mode = modes[idx];
        int actual = (currentPinValue)*1024/100;
        if(idx!=minPinIdx){
            ptr+=",";
        }
        sprintf(buffer,"\n{\"name\":\"\D%d\",\
        \"pinId\":%d,\
        \"pwm\":%d,\
        \"mode\":%d,\
        \"pinState\":%d,\n\
        \"actualValue\":%d\
        }",idx,currentPin,currentPinValue,mode,1,actual);
        ptr+=buffer;
    }
    ptr+="\n]\n}";
    return ptr;
}
/**
 * api sendStatus
*/
void sendStatus(Request &req,Response &res){
  Serial.print("[sendStatus]");
  char buffLength[16];
  String status=getStatusJson();
  sprintf(buffLength,"%d",status.length());

  res.set("Content-Type", "application/json; charset=utf-8");
  // res.set("Content-Encoding", "gzip");
  res.set("Cache-Control", "no-cache");
  res.set("Content-Length", buffLength);
  /// res.set("Last-Modified", "Mon, 27 Jun 2022 14:59:25 GMT");
  res.set("Vary", "Accept-Encoding");
  res.print(status);
}

/**
 * api setPin
*/
void setPin(Request &req,Response &res){
  char pinIdxString[2];
  req.query("pinIdx", pinIdxString, 2);
  char valString[12];
  req.query("val", valString, 12);
  char modeString[12];
  req.query("mode", modeString, 12);
  int pinIdx=String(pinIdxString).toInt();
  int val=String(valString).toInt();
  int mode=String(modeString).toInt();
  values[pinIdx]=val;
  int actual = (val)*1024/100;
  Serial.printf("[setPin,%d,%d,%d]",pinIdx,val,actual);
  // pinMode(pins[idx], modes[idx]);
  analogWrite(pins[pinIdx],actual);
  sendStatus(req,res);
}


/**
 * api getStatus
*/
void getPins(Request &req,Response &res){
  Serial.print("[getPins]");
  sendStatus(req,res);
}


void commanderSetup(Application &app){
  app.get("/pin", &setPin);
  app.get("/pins", &getPins);
  app.use(staticFiles());
}
