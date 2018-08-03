#include <Arduino.h>
#include "envelope.h"

Envelope::Envelope(void) {
  delay = 0;
  attack = 10.5;
  hold = 2.5;
  decay = 35;
  sustain = 0.7;
  release = 300;
  amp.gain(0);
  dc.amplitude(0);
}

void update() {

}

void noteOn() {

}

void noteOff() {

}
