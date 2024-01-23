#include "Arduino.h"
#include "SpeakerController.h"

SpeakerController::SpeakerController(int pin) {
  _pin = pin;
}

void SpeakerController::initialize() {
  pinMode(_pin, OUTPUT);
}

void SpeakerController::playTone(int frequency) {
  tone(_pin, frequency);
}

void SpeakerController::stopTone() {
  noTone(_pin);
}
