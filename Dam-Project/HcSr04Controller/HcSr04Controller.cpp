#include "Arduino.h"
#include "HcSr04Controller.h"

HcSr04Controller::HcSr04Controller(int trigPin, int echoPin) {
  _trigPin = trigPin;
  _echoPin = echoPin;
}

void HcSr04Controller::initialize() {
  pinMode(_trigPin, OUTPUT);
  pinMode(_echoPin, INPUT);
}

float HcSr04Controller::getDistance() {
  digitalWrite(_trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(_trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(_trigPin, LOW);
  
  long duration = pulseIn(_echoPin, HIGH);
  float distance = (duration / 2) / 29.1;
  
  return distance;
}
