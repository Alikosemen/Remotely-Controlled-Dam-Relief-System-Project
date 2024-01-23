#include "LedController.h"

LedController::LedController(int pin) {
  _pin = pin;
}

void LedController::initialize() {
  pinMode(_pin, OUTPUT);
}

void LedController::turnOn() {
  digitalWrite(_pin, HIGH);
}

void LedController::turnOff() {
  digitalWrite(_pin, LOW);
}

void LedController::turnOnOff(bool state) { // Bu metodu ekleyin
  if (state) {
    turnOn();
  } else {
    turnOff();
  }
}
