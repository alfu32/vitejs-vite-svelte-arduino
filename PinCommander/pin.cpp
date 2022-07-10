#ifndef PIN_CPP_
#define PIN_CPP_
#include "pin.h"


Pin* pin(
  int id,
  char* name,
  PinType type,
  PinMode mode,
  int value
){
  Pin* pin=new Pin(id,name,type,mode);
    return pin;
}

Pin* Pin::setId(int _id){
    this->id=_id;
    return this;
}
int Pin::getId(){
    return this->id;
}
Pin* Pin::setName(char* _name){
    free(this->name);
    int len=strlen(name);
    this->name=(char*)malloc(len*sizeof(char));
    for(int i=0; i<len;i++)this->name[i]=name[i];
    return this;
}
char* Pin::getName(){
    return this->name;
}
Pin* Pin::setType(PinType _type){
    switch(_type){
        case A:
        case D:
            break;
        default:
            break;
    }
    this->type=_type;
    return this;
}
PinType Pin::getType(){
    return this->type;
}
Pin* Pin::setMode(char* _mode){
    if(strcmp("IN",_mode)==0){
        this->mode=IN;
    }else if(strcmp("OUT",_mode)==0){
        this->mode=OUT;
    }else{
        return this;
    }
    return this;
}
Pin* Pin::setMode(PinMode _mode){
    this->mode=_mode;
    return this;
}
PinMode Pin::getMode(){
    return this->mode;
}
Pin* Pin::setValue(int _value){
    this->timestamp=micros();
    this->value=_value;
    return this;
}
int Pin::getValue(){
    return this->value;
}
void Pin::getJson(char* buffer){
    json=this->getJson();
    for(int i=0;i<256;i++){
        buffer[i]=json[i];
    }
}
char* Pin::getJson(){
    char* json = (char*)malloc(256*sizeof(char));
    char* _typeString=((char*)malloc(64*sizeof(char)));
    switch(this->type){
        case A:
            _typeString=strcpy(_typeString,"ANALOG");\
            break;
        case D:
            _typeString=strcpy(_typeString,"DIGITAL");
            break;
        default:
            _typeString=strcpy(_typeString,"UNDEFINED");
            break;
    }
    char* _modeString=((char*)malloc(64*sizeof(char)));
    switch(this->mode){
        case IN:
            _modeString=strcpy(_modeString,"INPUT");
        case OUT:
            _modeString=strcpy(_modeString,"OUTPUT");
            break;
        default:
            _modeString=strcpy(_modeString,"UNDEFINED");
            break;
    }
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

#endif