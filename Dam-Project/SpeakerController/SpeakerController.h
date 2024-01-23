#ifndef SpeakerController_h
#define SpeakerController_h

#include "Arduino.h"

class SpeakerController {
  public:
    SpeakerController(int pin);
    void initialize();
    void playTone(int frequency);
    void stopTone();
  private:
    int _pin;
};

#endif
