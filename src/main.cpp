#include <Arduino.h>
#include <MIDI.h>
#include "synth.h"
#include "ui.h"

MIDI_CREATE_DEFAULT_INSTANCE();
Synth fm_z;
Ui    ui;

void setup() {
  Serial.begin(9600);
  MIDI.begin(MIDI_CHANNEL_OMNI);
  fm_z.init();
  ui.init();
}

void loop() {
  MIDI.read();
  ui.update();
  fm_z.getUiData();
  fm_z.update();
}

//TODO:
//  - finish basics UI functions (pots/leds/buttons)
//  - determine UI-->SYNTH data transfer
//  - implement MIDI
//  - dynamically create voice AudioConnection
//  -
