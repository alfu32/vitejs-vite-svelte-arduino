#ifndef PIN_H_
#define PIN_H_
#include "Arduino.h"
#include "ArduinoJson.h"
#include <vector>

using namespace std;

enum PinType{A,D};

enum PinMode{IN,OUT};
typedef PinValue{
  PinValue(long value):value(value){
    timestamp=micros();
  }
  long timestamp;
  long value;
}PinValue;
class Pin{
    public:
        Pin(int id,char* name,PinType type,PinMode mode):
          id(id),type(type),mode(mode){
            setName(name);
            this->json=(char*)malloc(256*sizeof(char));
          };/*{
            this->json=(char*)malloc(256*sizeof(char));
            this->updateJson();
          };*/
        Pin* setId(int _id);
        int getId();
        Pin* setName(char* _name);
        char* getName();
        Pin* setType(char* _type);
        Pin* setType(PinType _type);
        PinType getType();
        Pin* setMode(char* _mode);
        Pin* setMode(PinMode _mode);
        PinMode getMode();
        Pin* setValue(int _value);
        int getValue();
        Pin* setValue(int _value);
        std::vector<PinValue> fetchValues();
        void getJson(char* buffer);
        char* getJson();
    private:
        int id;
        char* name;
        /*ANALOG or DIGITAL*/
        PinType type;
        PinMode mode;
        long timestamp;
        int value;
        std::vector<PinValue> values;
        char* json;
        void updateJson();
};

Pin* pin(
  int id,
  char* name,
  PinType type,
  PinMode mode,
  int value
);

#endif