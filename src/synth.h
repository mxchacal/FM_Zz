#ifndef SYNTH_H
#define SYNTH_H
#include <Arduino.h>
#include "ui.h"

class Synth
{
  public:
    Synth(){}
    void init();
    void getUiData();
    void update();

    void shutOff();

    void loadPreset(uint8_t preset);
    void setAlgo(int algo, uint8_t preset);
    void loadSysex(int sysex);

    void setOPfreq(int op, int freq);
    void setOPwave(int op, int waveform);
    void setOPamplitude(int op, float amplitude);

    void setOPattack(int op, int attack);
    void setOPdecay(int op, int decay);
    void setOPsustain(int op, int sustain);
    void setOPrelease(int op, int release);

    void noteOn();
    void noteOff();

  private:
    int ratio[6];
    int lastPreset = 0;   // 1---2---3---4---5---6---V1--V2--   Alg Nb
    uint32_t algomix[32]= {0b10000000100010000010000110100000,   //1
                           0b10000000100010000010000110100000,   //2
                          };
};

#endif
