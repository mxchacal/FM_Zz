#ifndef ENVELOPE_H
#define ENVELOPE_H

#include <Audio.h>

class Envelope
{
public:
  Envelope();
  void update();
  void noteOn();
  void noteOff();

private:
  AudioSynthWaveformDc dc;
  AudioAmplifier       amp;
  int delay, attack, hold, decay, sustain, release;

};

#endif
