#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

#define POLYPHONY 1 //Max number of voices
#define NB_OPERATOR 6

AudioSynthWaveformModulated OPERATOR[NB_OPERATOR][POLYPHONY];
AudioEffectEnvelope         OP_ENVLP[NB_OPERATOR][POLYPHONY];
AudioMixer4                 OP_MIXER[6][POLYPHONY];
AudioMixer4					        VOICE_MIXER[3][POLYPHONY];
AudioAmplifier              OP_AMP[NB_OPERATOR][POLYPHONY];
//AudioConnection             CABLE[POLYPHONY];
AudioOutputUSB              usb1;
AudioOutputAnalog		        dac1;

//Voice 1
//OP -> ENV
/*AudioConnection PatchChord1(OPERATOR[0][0], OP_ENVLP[0][0]);
AudioConnection PatchChord2(OPERATOR[1][0], OP_ENVLP[1][0]);
AudioConnection PatchChord3(OPERATOR[2][0], OP_ENVLP[2][0]);
AudioConnection PatchChord4(OPERATOR[3][0], OP_ENVLP[3][0]);
AudioConnection PatchChord5(OPERATOR[4][0], OP_ENVLP[4][0]);
AudioConnection PatchChord6(OPERATOR[5][0], OP_ENVLP[5][0]);
*/
AudioConnection PatchChord1(OPERATOR[0][0], OP_AMP[0][0]);
AudioConnection PatchChord2(OPERATOR[1][0], OP_AMP[1][0]);
AudioConnection PatchChord3(OPERATOR[2][0], OP_AMP[2][0]);
AudioConnection PatchChord4(OPERATOR[3][0], OP_AMP[3][0]);
AudioConnection PatchChord5(OPERATOR[4][0], OP_AMP[4][0]);
AudioConnection PatchChord6(OPERATOR[5][0], OP_AMP[5][0]);
//ENV -> VOICE MIXER
/*AudioConnection PatchChord7(OP_ENVLP[0][0], 0, VOICE_MIXER[0][0], 0);
AudioConnection PatchChord8(OP_ENVLP[1][0], 0, VOICE_MIXER[0][0], 1);
AudioConnection PatchChord9(OP_ENVLP[2][0], 0, VOICE_MIXER[0][0], 2);
AudioConnection PatchChord10(OP_ENVLP[3][0], 0, VOICE_MIXER[1][0], 0);
AudioConnection PatchChord11(OP_ENVLP[4][0], 0, VOICE_MIXER[1][0], 1);
AudioConnection PatchChord12(OP_ENVLP[5][0], 0, VOICE_MIXER[1][0], 2);
*/
AudioConnection PatchChord7(OP_AMP[0][0], 0, VOICE_MIXER[0][0], 0);
AudioConnection PatchChord8(OP_AMP[1][0], 0, VOICE_MIXER[0][0], 1);
AudioConnection PatchChord9(OP_AMP[2][0], 0, VOICE_MIXER[0][0], 2);
AudioConnection PatchChord10(OP_AMP[3][0], 0, VOICE_MIXER[1][0], 0);
AudioConnection PatchChord11(OP_AMP[4][0], 0, VOICE_MIXER[1][0], 1);
AudioConnection PatchChord12(OP_AMP[5][0], 0, VOICE_MIXER[1][0], 2);
//Voice mixers -> voice final mixer
AudioConnection PatchChord13(VOICE_MIXER[0][0], 0, VOICE_MIXER[2][0], 0);
AudioConnection PatchChord14(VOICE_MIXER[1][0], 0, VOICE_MIXER[2][0], 1);
//ENV -> OP Mixer
//OP1 mixer
AudioConnection PatchChord15(OP_ENVLP[1][0], 0, OP_MIXER[0][0], 0);
AudioConnection PatchChord16(OP_ENVLP[2][0], 0, OP_MIXER[0][0], 1);
AudioConnection PatchChord17(OP_ENVLP[3][0], 0, OP_MIXER[0][0], 2);
AudioConnection PatchChord18(OP_ENVLP[4][0], 0, OP_MIXER[0][0], 3);
AudioConnection PatchChord19(OP_MIXER[0][0], 0, OPERATOR[0][0], 0);
//OP2 mixer
AudioConnection PatchChord20(OP_ENVLP[1][0], 0, OP_MIXER[1][0], 0);
AudioConnection PatchChord21(OP_ENVLP[2][0], 0, OP_MIXER[1][0], 1);
AudioConnection PatchChord22(OP_MIXER[1][0], 0, OPERATOR[1][0], 0);
//OP3 mixer
AudioConnection PatchChord23(OP_ENVLP[2][0], 0, OP_MIXER[2][0], 0);
AudioConnection PatchChord24(OP_ENVLP[3][0], 0, OP_MIXER[2][0], 1);
AudioConnection PatchChord25(OP_ENVLP[4][0], 0, OP_MIXER[2][0], 2);
AudioConnection PatchChord26(OP_ENVLP[5][0], 0, OP_MIXER[2][0], 3);
AudioConnection PatchChord27(OP_MIXER[2][0], 0, OPERATOR[2][0], 0);
//OP4 mixer
AudioConnection PatchChord28(OP_ENVLP[3][0], 0, OP_MIXER[3][0], 0);
AudioConnection PatchChord29(OP_ENVLP[4][0], 0, OP_MIXER[3][0], 1);
AudioConnection PatchChord30(OP_ENVLP[5][0], 0, OP_MIXER[3][0], 2);
AudioConnection PatchChord31(OP_MIXER[3][0], 0, OPERATOR[3][0], 0);
//OP5 mixer
AudioConnection PatchChord32(OP_ENVLP[3][0], 0, OP_MIXER[4][0], 2);
AudioConnection PatchChord33(OP_ENVLP[4][0], 0, OP_MIXER[4][0], 3);
AudioConnection PatchChord34(OP_MIXER[4][0], 0, OPERATOR[4][0], 0);
//OP6 mixer
AudioConnection PatchChord35(OP_ENVLP[3][0], 0, OP_MIXER[5][0], 0);
AudioConnection PatchChord36(OP_ENVLP[5][0], 0, OP_MIXER[5][0], 1);
AudioConnection PatchChord37(OP_MIXER[5][0], 0, OPERATOR[5][0], 0);
