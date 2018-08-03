#ifndef UI_H
#define UI_H
#include <Arduino.h>
#include "synth.h"

extern int activePage;
extern uint8_t nextValue[16][8];
extern uint8_t lastValue[16][8];
extern bool hasChanged[16];
extern bool pageChange;

class Ui
{
  public:
    Ui(){};
    void init();
    void update();

//    void pushData(Synth& synth);
    void setPage(int page);

  private:
};

#endif
