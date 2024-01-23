#ifndef LedController_h
#define LedController_h

#include "Arduino.h"

class LedController {
  public:
    LedController(int pin);
    void initialize();
    void turnOn();
    void turnOff();
    void turnOnOff(bool state); // Bu satýrý ekleyin
  private:
    int _pin;
};

#endif

