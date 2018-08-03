#ifndef POT_H
#define POT_H
#include <Arduino.h>
#include "ui.h"

#define S0 0
#define S1 1
#define S2 2
#define READ_PIN 3
#define POT_NB 16
#define MAX_VAL 99

class Pot
{
  public:
    Pot(){};

    void init();
    void update();
    void process(int index, int value);

  private:
    int buffer;
};

#endif
