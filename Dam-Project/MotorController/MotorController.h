#ifndef MotorController_h
#define MotorController_h

#include "Arduino.h"

class MotorController {
  public:
    MotorController(int pin1, int pin2);
    void initialize();
    void startMotor();
    void stopMotor();
  private:
    int _pin1, _pin2;
};

#endif
