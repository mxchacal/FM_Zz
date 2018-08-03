#include "synth.h"
#include "synth_utils.h"
#include "sysex.h"
#include "cartridge.h"
#include <Arduino.h>

#define AUDIO_MEMORY 20

void Synth::init() {
  AudioMemory(AUDIO_MEMORY);
  loadPreset(lastPreset);
}

void Synth::getUiData() {
//  switch(type) {// 0-20 OP parameter
}

void Synth::update() {
  #ifdef SYNTH_DEBUG
    Serial.print("Synth.update, CPU = ");
    Serial.print(AudioProcessorUsage());
    Serial.print("%, Memory = ");
    Serial.print(AudioMemoryUsage());
    Serial.print(" / ");
    Serial.println(AUDIO_MEMORY);
  #endif
}

void Synth::loadPreset(uint8_t preset) {
  shutOff();                                    //avoid glitches
  setAlgo(sysex[(preset * 128 + 110)], preset); //110th byte

  AudioNoInterrupts();

  for(int i=0; i<NB_OPERATOR; i++) {
    setOPamplitude(i, (sysex[preset * 128 + 14] / 100));
    setOPattack(i, map(sysex[preset * 128], 0, 99, 0, 10000));
    setOPdecay(i, map(sysex[preset * 128 + 1], 0, 99, 0, 10000));
    setOPsustain(i, map(sysex[preset * 128 + 6], 0, 99, 0, 1));
    setOPrelease(i, map(sysex[preset * 128 + 3], 0, 99, 0, 10000));
  }

  AudioInterrupts();
}

void Synth::loadSysex(int sysex) {

}

void Synth::setAlgo(int algo, uint8_t preset) {
  int index;
  float gain;
  for(int i=0; i<2; i++) {
    for(int j=0; j<8; j++) {
      //read mixer bits from algomix
      index = j * 4;
      gain = 1 / (bitRead(algomix[preset], index) + bitRead(algomix[preset], (index + 1)) + bitRead(algomix[preset], (index + 2)) + bitRead(algomix[preset], (index + 3)));
      for(int k=0; k<4; k++) OP_MIXER[j][i].gain(k, (bitRead(algomix[preset], index + k) * gain));
    }
  }
}

void Synth::noteOn() {

}

void Synth::noteOff() {

}

void Synth::shutOff() {
  for(int i=0; i<POLYPHONY; i++) {
    for(int j=0; j<NB_OPERATOR; j++) {
      OP_MIXER[j][i].shut();
    }
    VOICE_MIXER[0][POLYPHONY].shut();
    VOICE_MIXER[1][POLYPHONY].shut();
    VOICE_MIXER[2][POLYPHONY].shut();
  }
}

void Synth::setOPfreq(int op, int freq) {
  for(int i=0; i<POLYPHONY; i++) OPERATOR[op][i].frequency(freq);
}

void Synth::setOPwave(int op, int waveform) {
  for(int i=0; i<POLYPHONY; i++) OPERATOR[op][i].begin(waveform);
}

void Synth::setOPamplitude(int op, float amplitude) {
  for(int i=0; i<POLYPHONY; i++) OPERATOR[op][i].amplitude(amplitude);
}

void Synth::setOPattack(int op, int attack) {
  for(int i=0; i<POLYPHONY; i++) OP_ENVLP[op][i].attack(attack);
}

void Synth::setOPdecay(int op, int decay){
  for(int i=0; i<POLYPHONY; i++) OP_ENVLP[op][i].decay(decay);
}

void Synth::setOPsustain(int op, int sustain){
  for(int i=0; i<POLYPHONY; i++) OP_ENVLP[op][i].sustain(sustain);
}

void Synth::setOPrelease(int op, int release){
  for(int i=0; i<POLYPHONY; i++) OP_ENVLP[op][i].release(release);
}
