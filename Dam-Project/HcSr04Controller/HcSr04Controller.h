#ifndef HcSr04Controller_h
#define HcSr04Controller_h

#include "Arduino.h"

class HcSr04Controller {
  public:
    HcSr04Controller(int trigPin, int echoPin);
    void initialize();
    float getDistance();
  private:
    int _trigPin, _echoPin;
};

#endif
