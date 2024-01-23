#include "Arduino.h"
#include "MotorController.h"

MotorController::MotorController(int pin1, int pin2) {
  _pin1 = pin1;
  _pin2 = pin2;
}

void MotorController::initialize() {
  pinMode(_pin1, OUTPUT);
  pinMode(_pin2, OUTPUT);
  stopMotor(); // Baþlangýçta motoru durdur
}

void MotorController::startMotor() {
  digitalWrite(_pin1, HIGH);
  digitalWrite(_pin2, LOW);
}

void MotorController::stopMotor() {
  digitalWrite(_pin1, LOW);
  digitalWrite(_pin2, LOW);
}
