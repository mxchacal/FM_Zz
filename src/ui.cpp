/*  Get / Set functions
TODO : - pots:
         - set mux OK, read values OK, process values (push or not) OK
         -
       - leds:
         -
         -
       - buttons:
         -
         -
       - UI:
         - send data to SYNTH
         - manage MIDI (other class?)
*/
#include "ui.h"
#include "led.h"
#include "pot.h"
#include "button.h"

Led leds;
Pot pots;
Button buttons;

int activePage;
uint8_t nextValue[16][8];
uint8_t lastValue[16][8];
bool hasChanged[16];
bool pageChange;

void Ui::init()
{
  activePage = 0;
  pageChange = 0;
  //set all pots value to zero, TODO: init with last preset
  for(int i=0; i<16; i++) {
    hasChanged[i] = 0;
    for(int j=0; j<7; j++) {
      lastValue[i][j] = 0;
      nextValue[i][j] = 0;
    }
  }
}

void Ui::update()
{
  Serial.println("UI.update");
  pots.update();
  leds.update();
  buttons.update();
}

//void Ui::pushData(Synth& synth) {

//}

void Ui::setPage(int page) {
  for(int i=0; i<16; i++) lastValue[i][activePage] = nextValue[i][activePage];
  activePage = page;
  pageChange = 1;
}
