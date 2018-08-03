#include "pot.h"

void Pot::init() {
  //set 4051 pins
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(READ_PIN, INPUT);
}

void Pot::update() {
  //read and store values, if new after op-page change
  for(int x=1; x<3; x++) {
    for(int i=1; i<9; i++) {
      digitalWrite(S0, bitRead(i, 0));                    //select 4051 input
      digitalWrite(S1, bitRead(i, 1));
      digitalWrite(S2, bitRead(i, 2));
      buffer = map(analogRead(READ_PIN), 0, 4095, 0, MAX_VAL); //read value
      int index = x * i;
      process(index, buffer);
    }
  }
}

void Pot::process(int index, int value) {
  if(!pageChange) {
    nextValue[index][activePage] = value;
  }
  else if(pageChange && value != lastValue[index][activePage]) {
    hasChanged[index] = 1;
    nextValue[index][activePage] = value;
    pageChange = 0;
  }
}

//TODO: send parameter update IF new after page change
//method :  - read value
//      - check if page changed
//        - NO  --> send data out
//        - YES --> is it fresh data?
//          - NO --> don't modify parameter
//          - YES --> hasChanged = TRUE, send data out
