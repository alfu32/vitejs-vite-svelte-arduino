#ifndef IO_STATE_H_
#define IO_STATE_H_
#include "Arduino.h"
#include "ArduinoJson.h"
#include "pin.h"

class Pins{
  public:
    Pins(){}
    void registerPin(Pin* pin){
      pins[last_pin]=pin;
      last_pin++;
    }
    void registerPins(Pin* pin){
      pins[last_pin]=pin;
      last_pin++;
    }
    char* toJson(){
      char* json = (char*)malloc(256*sizeof(char));
      DynamicJsonDocument doc(256);
      doc["id"] = this->id;
      doc["name"] = this->name;
      doc["type"]   = _typeString;
      doc["mode"]   = _modeString;
      doc["timestamp"] = this->timestamp;
      doc["value"] = this->value;
      size_t len=serializeJson(doc,json,256);
      free(_typeString);
      free(_modeString);
      return json;
    }
  private:
    Pin* pins=new Pin[48];
    int pins_size=48;
    int last_pin=0;
};